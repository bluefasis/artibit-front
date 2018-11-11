open DataFetcher;
open ReasonReactUtils;

type action =
  | LoadData
  | LoadedData(overall)
  | LoadDataFailed;

type status =
  | Idle
  | Loading
  | Failure
  | Success;

type state = {
  status,
  overall,
};

let loadData = send =>
  Js.Promise.(
    DataFetcher.fetchOverall()
    |> then_(result =>
         switch (result) {
         | Some(overall) => resolve(send(LoadedData(overall)))
         | None => resolve(send(LoadDataFailed))
         }
       )
    |> ignore
  );

let component = ReasonReact.reducerComponent("HomePage");

let make = _children => {
  ...component,
  initialState: () => {
    status: Idle,
    overall: {
      exhibition: {
        id: 0,
        name: "",
        image: "",
        body: "",
      },
      arts: [],
    },
  },
  didMount: self => self.send(LoadData),
  reducer: (action, state) =>
    switch (action) {
    | LoadData => UpdateWithSideEffects({...state, status: Loading}, (({send}) => loadData(send)))
    | LoadedData(overall) => Update({status: Success, overall})
    | LoadDataFailed => Update({...state, status: Failure})
    },
  render: self =>
    <div className="App">
      <div className="App-main" onClick={_event => goToUrl("/artist/1")}>
        <img src={self.state.overall.exhibition.image} className="img-main" alt={self.state.overall.exhibition.name} />
      </div>
      <div className="App-preview row">
        {
          matchListToArray(
            Belt.List.mapWithIndex(self.state.overall.arts, (i, art) =>
              <div className="col-6"> <ArtLinkImg key={string_of_int(i)} art /> </div>
            ),
          )
        }
      </div>
    </div>,
};

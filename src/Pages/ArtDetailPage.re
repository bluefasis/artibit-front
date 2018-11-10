[@bs.module] external logo: string = "../logo.svg";

open DataFetcher;
open ReasonReactUtils;

type action =
  | LoadData
  | LoadedData(art)
  | LoadDataFailed;

type status =
  | Idle
  | Loading
  | Failure
  | Success;

type state = {
  status,
  art,
};

let loadData = (send, artId) =>
  Js.Promise.(
    DataFetcher.fetchArtDetail(artId)
    |> then_(result =>
         switch (result) {
         | Some(art) => resolve(send(LoadedData(art)))
         | None => resolve(send(LoadDataFailed))
         }
       )
    |> ignore
  );

let component = ReasonReact.reducerComponent("ArtDetailPage");

let make = (~artId, _children) => {
  ...component,
  initialState: () => {
    status: Idle,
    art: {
      id: 0,
      name: "",
      image: "",
      subtitle: "",
      body: "",
      artist: {
        id: 0,
        name: "",
      },
    },
  },
  didMount: self => self.send(LoadData),
  reducer: (action, state) =>
    switch (action) {
    | LoadData => UpdateWithSideEffects({...state, status: Loading}, (({send}) => loadData(send, artId)))
    | LoadedData(art) => Update({status: Success, art})
    | LoadDataFailed => Update({...state, status: Failure})
    },
  render: self =>
    <div className="App">
      <div className="App-header"> {ReasonReact.string("<")} </div>
      <div className="App-body">
        <img src={self.state.art.image} className="Img-main" alt={self.state.art.name} />
        <h4> {ReasonReact.string(self.state.art.name)} </h4>
        <h5> {ReasonReact.string(self.state.art.subtitle)} </h5>
        <div dangerouslySetInnerHTML={dangerousHtml(self.state.art.body)} />
      </div>
    </div>,
};

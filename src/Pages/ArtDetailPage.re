[@bs.module] external logo: string = "../logo.svg";

open DataFetcher;

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
  render: _self =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> {ReasonReact.string({j|ArtDetailPage$artId|j})} </h2>
      </div>
      <p className="App-intro">
        {ReasonReact.string("To get started, edit")}
        <code> {ReasonReact.string(" src/ArtDetailPage.re ")} </code>
        {ReasonReact.string("and save to reload.")}
      </p>
    </div>,
};

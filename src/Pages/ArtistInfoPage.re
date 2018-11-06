[@bs.module] external logo: string = "../logo.svg";

open DataFetcher;

type action =
  | LoadData
  | LoadedData(artistInfo)
  | LoadDataFailed;

type status =
  | Idle
  | Loading
  | Failure
  | Success;

type state = {
  status,
  artistInfo,
};

let loadData = (send, artistId) =>
  Js.Promise.(
    DataFetcher.fetchArtistInfo(artistId)
    |> then_(result =>
         switch (result) {
         | Some(artistInfo) => resolve(send(LoadedData(artistInfo)))
         | None => resolve(send(LoadDataFailed))
         }
       )
    |> ignore
  );

let component = ReasonReact.reducerComponent("ArtistInfoPage");

let make = (~artistId, _children) => {
  ...component,
  initialState: () => {
    status: Idle,
    artistInfo: {
      id: 0,
      name: "",
      body: "",
    },
  },
  didMount: self => self.send(LoadData),
  reducer: (action, state) =>
    switch (action) {
    | LoadData => UpdateWithSideEffects({...state, status: Loading}, (({send}) => loadData(send, artistId)))
    | LoadedData(artistInfo) => Update({status: Success, artistInfo})
    | LoadDataFailed => Update({...state, status: Failure})
    },
  render: _self =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> {ReasonReact.string({j|ArtistInfoPage$artistId|j})} </h2>
      </div>
      <p className="App-intro">
        {ReasonReact.string("To get started, edit")}
        <code> {ReasonReact.string(" src/ArtistInfoPage.re ")} </code>
        {ReasonReact.string("and save to reload.")}
      </p>
    </div>,
};

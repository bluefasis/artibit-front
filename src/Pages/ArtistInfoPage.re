open DataFetcher;
open ReasonReactUtils;

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
  render: self =>
    <div className="App">
      <div className="App-header"> <HomeButton /> </div>
      <div className="App-body">
        <h5> {ReasonReact.string({j|ประวัติศิลปิน|j})} </h5>
        <h4> {ReasonReact.string(self.state.artistInfo.name)} </h4>
        <div dangerouslySetInnerHTML={dangerousHtml(self.state.artistInfo.body)} />
      </div>
    </div>,
};

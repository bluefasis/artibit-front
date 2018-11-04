open Store;
open ReasonReact;

type status =
  | Idle
  | Success;

type state = {
  data: string,
  status,
};

type action =
  | LoadAllData;

let component = reducerComponent("DataDistributor");

let make = (~route, ~url, ~prevUrl, _children) => {
  ...component,
  initialState: () => {data: "test", status: Success},
  reducer: (action, state) =>
    switch (action) {
    | LoadAllData => Update({...state, status: Success})
    },
  render: ({state, send}) =>
    switch (state.status) {
    | Success =>
      switch ((route: Store.route)) {
      | Home
      | ArtistInfo => <ArtistInfoPage />
      | PieceDetail => <PieceDetailPage />
      | Default => <HomePage />
      }
    | Idle => <HomePage />
    },
};

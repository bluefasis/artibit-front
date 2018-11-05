[@bs.module] external logo: string = "../logo.svg";

open DataFetcher;

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
  render: _self =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> {ReasonReact.string("HomePage")} </h2>
      </div>
      <p className="App-intro">
        {ReasonReact.string("To get started, edit")}
        <code> {ReasonReact.string(" src/HomePage.re ")} </code>
        {ReasonReact.string("and save to reload.")}
      </p>
    </div>,
};

[@bs.module] external logo: string = "../logo.svg";

let component = ReasonReact.statelessComponent("HomePage");

let make = _children => {
  ...component,
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

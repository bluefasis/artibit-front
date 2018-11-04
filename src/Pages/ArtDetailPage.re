[@bs.module] external logo: string = "../logo.svg";

let component = ReasonReact.statelessComponent("ArtDetailPage");

let make = (~artId, _children) => {
  ...component,
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

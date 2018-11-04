[@bs.module] external logo: string = "../logo.svg";

let component = ReasonReact.statelessComponent("ArtistInfoPage");

let make = (~artistId, _children) => {
  ...component,
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

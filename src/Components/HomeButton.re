open ReasonReactUtils;

let component = ReasonReact.statelessComponent("HomeButtonRe");

let make = _children => {
  ...component,
  render: _self =>
    <button className="btn" onClick={_event => goToUrl("/")}> <i className="fa fa-chevron-left" /> </button>,
};

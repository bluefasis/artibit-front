open ReasonReactUtils;

let component = ReasonReact.statelessComponent("ArtLinkImgRe");

let make = (~art: DataFetcher.art, _children) => {
  ...component,
  render: _self =>
    <div onClick={_event => goToUrl("/art/" ++ string_of_int(art.id))}>
      <img src={art.image} className="img-preview" />
      <div className="img-name"> {ReasonReact.string(art.name)} </div>
    </div>,
};

open Store;
open ReasonReact;

let component = statelessComponent("PageDistributor");

let make = (~route, ~url as _, _children) => {
  ...component,
  render: _self =>
    switch ((route: Store.route)) {
    | Default
    | Home => <HomePage />
    | ArtistInfo(artistId) => <ArtistInfoPage artistId />
    | ArtDetail(artId) => <ArtDetailPage artId />
    },
};

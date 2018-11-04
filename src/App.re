[%bs.raw {|require('./App.scss')|}];

open Store;

type state = {
  route,
  url: ReasonReact.Router.url,
};

type action =
  | RouteTo(route)
  | GetUrl(ReasonReact.Router.url);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {
    route: Home,
    url: {
      path: [],
      hash: "",
      search: "",
    },
  },
  reducer: (action, state) =>
    switch (action) {
    | RouteTo(route) => ReasonReact.Update({...state, route})
    | GetUrl(url) => ReasonReact.Update({...state, url})
    },
  didMount: self => {
    let jumpTo = x => self.send(RouteTo(x));
    let watcherID =
      ReasonReact.Router.watchUrl(url => {
        switch (url.path) {
        | ["home"] => jumpTo(Home)
        | ["artist", artistId] => jumpTo(ArtistInfo(artistId))
        | ["art", artId] => jumpTo(ArtDetail(artId))
        | [] => jumpTo(Default)
        | _ => jumpTo(Home)
        };
        self.send(GetUrl(url));
      });
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
    ReasonReact.Router.push("");
  },

  render: ({state: {route, url}}) => <main> <PageDistributor route url /> </main>,
};

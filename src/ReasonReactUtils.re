open ReasonReact;

let goToUrl = url => Router.push(url);
let dangerousHtml: string => Js.t('a) = html => {"__html": html};

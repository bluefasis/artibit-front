open ReasonReact;
open Belt;

let goToUrl = url => Router.push(url);
let dangerousHtml: string => Js.t('a) = html => {"__html": html};
let matchListToArray = listElement => array(List.toArray(listElement));

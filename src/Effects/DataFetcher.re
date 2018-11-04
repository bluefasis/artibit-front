let exhibitionId = 1;
let baseUrl = "http://192.168.99.100:3000/download";

let overallUrl = {j|$baseUrl/overall/$exhibitionId|j};
let artistInfoUrl = {j|$baseUrl/artist/{artistId}|j};
let artDetailUrl = {j|$baseUrl/art/{artId}|j};

type id = string;
type name = string;
type image = string;
type subtitle = string;
type body = string;

type artistInfo = {
  id,
  name,
  body,
};

type artist = {
  id,
  name,
};

type art = {
  id,
  name,
  image,
  subtitle,
  body,
  artist,
};

type exhibition = {
  id,
  name,
  image,
  body,
};

type overall = {
  exhibition,
  arts: list(art),
};

module Decode = {
  let artistInfo = json =>
    Json.Decode.{
      id: json |> field("id", string),
      name: json |> field("name", string),
      body: json |> field("body", string),
    };

  let artist = json => Json.Decode.{id: json |> field("id", string), name: json |> field("name", string)};

  let art = json =>
    Json.Decode.{
      id: json |> field("id", string),
      name: json |> field("name", string),
      image: json |> field("image", string),
      subtitle: json |> field("subtitle", string),
      body: json |> field("body", string),
      artist: json |> field("artist", artist),
    };

  let arts = json: list(art) => Json.Decode.list(art, json);

  let exhibition = json =>
    Json.Decode.{
      id: json |> field("id", string),
      name: json |> field("name", string),
      image: json |> field("image", string),
      body: json |> field("body", string),
    };

  let overall = json =>
    Json.Decode.{exhibition: json |> field("exhibition", exhibition), arts: json |> field("arts", arts)};
};

let component = ReasonReact.statelessComponent("Player");

let make = (~player, _children) => {
  ...component,
  render: self =>
    <div>
      (ReasonReact.string(player))
    </div>,
};


/* module Decode = {
  let player = json =>
      Json.Decode.{
        id: json |> field("id", int),
        name: json |> field("name", string),
        position: json |> field("position", string),
        school: json |> field("school", string),
        drafted: json |> field("drafted", bool),
      }
};
then decode an array would be like
let players = json => Json.Decode.( json |> jsonArray(player) ) */

/* TODO: find out how to use env vars and make this dynamic */
let url = "http://localhost:8080";
/* let str = ReasonReact.stringToElement; */

type player = {
  id: int,
  name: string,
  position: string,
  school: string,
  drafted: bool,
};

/* type players = list(player); */

type state =
  | Error
  | Loading
  | Loaded(array(player));

type action =
  | PlayerFetch
  | PlayersFetched(array(player))
  | PlayersFailedToFetch;

/* module Decode = {
  let players = json: array(player) =>
    Json.Decode.(
      json |> Array.map(_, player => player)
    );
}; */

module Player = {
  let component = ReasonReact.statelessComponent("Player");
  let make = (~player, children) => {
    ...component,
    render: (self) =>
      <div className="player">
        (ReasonReact.string(player.name))
      </div>
  }
};


let sendQuery = (evt) => Js.log("sendQuery called");

let component = ReasonReact.reducerComponent("PlayerList");

let make = (children) => {
  ...component,
  initialState: () => {
    /* Loading, */
    players: []
  },
  reducer: ((action), state) =>
    switch action {
    | PlayerFetch => ReasonReact.NoUpdate
    | PlayersFetched(_) => ReasonReact.NoUpdate
    | PlayersFailedToFetch => ReasonReact.NoUpdate
  },
  render: ({state: {players}, _}) => {
    <div className="players">
    (
      ReasonReact.arrayToElement(Array.of_list(
        List.map((player) => <Player player />, players)
      ))
    )
    </div>
  },
}

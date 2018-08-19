/* TODO: find out how to use env vars and make this dynamic */
let rootUrl = "http://localhost:8080/";

type player = {
  id: int,
  name: string,
  position: string,
  school: string,
  drafted: bool,
};

module Decode = {
  let p = json =>
    Json.Decode.{
      id: json |> field("id", int),
      name: json |> field("name", string),
      position: json |> field("position", string),
      school: json |> field("school", string),
      drafted: json |> field("drafted", bool),
    }

    /* let players = json => Json.Decode.( json |> jsonArray(player) ) */
    let players = json : array(player) => Json.Decode.array(p, json);
};

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

/* module Input = {
  type action =
    | Change(string);
  type state = string;
  let component = ReasonReact.reducerComponent("Input");
  let make = (~onSubmit, _) => {
    ...component,
    initialState: () => "",
    /* reducer: (newQuery, _text) => ReasonReact.Update(newQuery), */
  reducer: action =>
    switch (action) {  
    | Change(text) => (
      state => ReasonReact.Update({ text })
    )
  },
  render: ({state: text, send}) =>
    <input
      value=text
      type_="text"
      placeholder="Draft a player"
      onChange=(
        event => send(Change(ReactEvent.Form.target(event)##value))
      )
    />
  };
}; */

/* PlayerList */
type state =
  | Error
  | Loading
  | Loaded(array(player));

type action =
  | PlayersFetch
  | PlayersFetched(array(player))
  | PlayersFailedToFetch;

let sendQuery = (_evt) => Js.log("sendQuery called");

let component = ReasonReact.reducerComponent("PlayerList");

let make = (_children) => {
  ...component,
  initialState: _state => Loading,
  reducer: (action, _state) =>
    switch action {
    | PlayersFetch =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
            Js.Promise.(
              Fetch.fetch(rootUrl)
              |> then_(Fetch.Response.json)
              |> then_(json =>
                  json
                  |> Decode.players
                  |> (players => self.send(PlayersFetched(players)))
                  |> resolve
                )
              |> catch(_err =>
                  Js.Promise.resolve(self.send(PlayersFailedToFetch))
                )
              |> ignore
            )
        ),
      )
    | PlayersFetched(players) => ReasonReact.Update(Loaded(players))
    | PlayersFailedToFetch => ReasonReact.Update(Error)
  },
  didMount: self => self.send(PlayersFetch),
  render: self =>
    switch (self.state) {
    | Error => <div> (ReasonReact.string("An error occurred!")) </div>
    | Loading => <div> (ReasonReact.string("Loading...")) </div>
    | Loaded(players) =>
      <div>
        <h3> (ReasonReact.string("Players")) </h3>
        <ul>
          (
            players
            |> Array.map(player =>
              <li key=string_of_int(player.id)>(
                /* ReasonReact.string(player.name) */
                <Player player />
              )</li>
            )
            |> ReasonReact.array
          )
        </ul>
      </div>
    },
}

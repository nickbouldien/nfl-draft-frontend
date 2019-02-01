open Player;

/* TODO: find out how to use env vars and make this dynamic */
let rootUrl = "http://localhost:8080/";

/* FIXME: stop using modules here! */
module Decode = {
  let p = json : Player.player =>
    Json.Decode.{
      id: json |> field("id", int),
      name: json |> field("name", string),
      school: json |> field("school", string),
      position: json |> field("position", string),
      drafted: json |> field("drafted", bool),
    }
  /* let players = json => Json.Decode.( json |> jsonArray(player) ) */
  let players = json : array(Player.player) => Json.Decode.array(p, json)
};

/* PlayerList */
/* type state = {
  error: bool,
  loading: bool,
  players: array(Player.player),
  text: string,
} */

type state =
  | Error
  | Loading
  | Loaded(array(Player.player));

type action =
  | PlayersFetch
  | PlayersFetched(array(Player.player))
  | PlayersFailedToFetch; /* Js.Promise.error */

let component = ReasonReact.reducerComponent("PlayerList");

/* let fetchPlayers = (_) =>
  Js.Promise.(
    Fetch.fetchWithInit(
      rootUrl ++ "players/",
      Fetch.RequestInit.make(
        ~mode=Fetch.NoCORS,
        (),
      ),
    )
      |> then_(Fetch.Response.json)
      |> then_(json => json |> Decode.players |> (players => Some(players) |> resolve))
      |> catch(_err => Js.Promise.resolve(None))
      /* |> ignore */
  ); */

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
            Fetch.fetchWithInit(
              rootUrl ++ "players/",
              Fetch.RequestInit.make(
                ~mode=Fetch.CORS,
                (),
              ),
            )
            |> then_(Fetch.Response.json)
            |> then_(json =>
                json
                |> Decode.players
                |> (players => self.send(PlayersFetched(players)))
                |> resolve
              )
            |> catch(err => {
                Js.log(err)
                Js.Promise.resolve(self.send(PlayersFailedToFetch))
            })
            |> ignore
          )
        ),
      )
    | PlayersFetched(players) => ReasonReact.Update(Loaded(players))
    | PlayersFailedToFetch => ReasonReact.Update(Error)
  },
  didMount: self => self.send(PlayersFetch),
  render: self => {
    switch (self.state) {
    | Error => <div> (ReasonReact.string("An error occurred!")) </div>
    | Loading => <div> (ReasonReact.string("Loading...")) </div>
    | Loaded(players) =>
      <div>
        <h3> (ReasonReact.string("Players")) </h3>

        <Button func={_evt => self.send(PlayersFetch)} message="Submit" />

        <ul>
          (
            players
            |> Array.map(player =>
              <li key=string_of_int(player.id)>(
                <Player player />
              )</li>
            )
            |> ReasonReact.array
          )
        </ul>
      </div>
    }
  }
}

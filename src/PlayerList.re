/* TODO: find out how to use env vars and make this dynamic */
let rootUrl = "http://localhost:8080";

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

module Decode = {
  let players = json: array(player) =>
    Json.Decode.(
      json |> Array.map(_, player => player)
    );
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

let valueFromEvent = (evt) : string => (
  evt
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;

module Input = {
  type state = string;
  let component = ReasonReact.reducerComponent("Input");
  let make = (~onSubmit, _) => {
    ...component,
    initialState: () => "",
    reducer: (newQuery, _text) => ReasonReact.Update(newQuery),
    render: ({state: text, reduce}) =>
      <input
        value=text
        _type="text"
        placeholder="Write something to do"
        onChange=(reduce((evt) => valueFromEvent(evt)))
        onKeyDown=((evt) =>
          if (ReactEventRe.Keyboard.key(evt) == "Enter") {
            onSubmit(text);
            (reduce(() => ""))()
          }
        )
      />
  };
};

let sendQuery = (evt) => Js.log("sendQuery called");

let component = ReasonReact.reducerComponent("PlayerList");

let make = (children) => {
  ...component,
  initialState: () => Loading,
  reducer: (action, state) =>
    switch action {
    | PlayerFetch =>
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

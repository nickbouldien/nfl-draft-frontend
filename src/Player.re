let component = ReasonReact.statelessComponent("Player");

type player = {
  drafted: bool,
  id: int,
  name: string,
  position: string,
  school: string,
};

let make = (~player, _children) => {
  ...component,
  render: (_self) =>
    <div className="player">
      <p>
        <b>(ReasonReact.string(player.name))</b>
        <br />
        (ReasonReact.string("Drafted: " ++ string_of_bool(player.drafted)))
        <br />
      </p>
        (ReasonReact.string(string_of_int(player.id)))
      <a href=("/player/" ++ string_of_int(player.id))> (ReasonReact.string("Go to profile")) </a>
      /* <Button  message="Draft player" disabled={player.drafted === true} /> */
    </div>
}

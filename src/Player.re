let component = ReasonReact.statelessComponent("Player");

type player = {
  id: int,
  name: string,
  school: string,
  position: string,
  drafted: bool,
};

let make = (~player, _children) => {
  ...component,
  render: (_self) =>
    <div className="player">
      (ReasonReact.string(player.name))
    </div>
}

let component = ReasonReact.statelessComponent("Player");

type player = {
  id: int,
  name: string,
  school: string,
  position: string,
  drafted: bool,
};

let make = (~player, children) => {
  ...component,
  render: (self) =>
    <div className="player">
      (ReasonReact.string(player.name))
    </div>
}

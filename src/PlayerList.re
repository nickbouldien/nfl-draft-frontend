
type player = {
  id: int,
  name: string,
  position: string,
  college: string,
  drafted: bool,
};

let component = ReasonReact.statelessComponent("PlayerList");

let make = (~player, _children) => {
  ...component,
  render: self =>
    <div>
      <input
        className="toggle"
        type_="text"
        onChange=(_ => sendQuery())
      />
      (ReasonReact.string(player))
    </div>,
};

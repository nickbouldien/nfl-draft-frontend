/* This is the basic component. */
let component = ReasonReact.statelessComponent("Player");

let make = (~player, _children) => {
  ...component,
  render: self =>
    <div>
      (ReasonReact.string(player))
    </div>,
};

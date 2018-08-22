let component = ReasonReact.statelessComponent("Button")

let make = (~func, ~message, _children) => {
  ...component,
  render: _self =>
    <button onClick=func>
      (ReasonReact.string(message))
    </button>
};

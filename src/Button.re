let component = ReasonReact.statelessComponent("Button")

let make = (~func, ~message, ~classNames, _children) => {
  ...component,
  render: _self =>
    <button onClick=func className=classNames>
      (ReasonReact.string(message))
    </button>
};

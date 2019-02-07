let component = ReasonReact.statelessComponent("Header");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <h2>
      (ReasonReact.string(message))
    </h2>
};

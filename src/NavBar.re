let component = ReasonReact.statelessComponent("NavBar");

let make = (_children) => {
  ...component,
  render: _self =>
    <nav>
      (ReasonReact.string("NFL Draft Reason")) 
    </nav>
};

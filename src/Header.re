let component = ReasonReact.statelessComponent("Header");

let make = (~message, ~size, _children) => {
  ...component,
  render: _self =>
    switch size {
    | "h1" => <h1>(ReasonReact.string(message))</h1>
    | "h2" => <h2>(ReasonReact.string(message))</h2>
    | "h3" => <h3>(ReasonReact.string(message))</h3>
    | "h4" => <h4>(ReasonReact.string(message))</h4>
    | "h5" => <h5>(ReasonReact.string(message))</h5>
    | "h6" => <h6>(ReasonReact.string(message))</h6>
    | "h7" => <h7>(ReasonReact.string(message))</h7>    
    | _ => <h1>(ReasonReact.string(message))</h1>
    }
};

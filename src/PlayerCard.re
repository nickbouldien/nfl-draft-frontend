let component = ReasonReact.statelessComponent("PlayerCard");

let make = (~name, ~id, ~drafted, ~draft, ~position, ~school, _children) => {
  ...component,
  render: (_self) =>
    <div className="player-card">
      <p>
        (ReasonReact.string(string_of_int(id) ++ " ")) 
        (ReasonReact.string(name))
      </p>
      <p>
        (ReasonReact.string("position: " ++ position))         
      </p>
      <p>
        (ReasonReact.string("school: " ++ school))         
      </p>
      /* <a href=("/player/" ++ string_of_int(player.id))> (ReasonReact.string("Go to profile")) </a> */
      (
        drafted
          ? ReasonReact.null
          : <button
              onClick = draft
            >
              (ReasonReact.string("Draft player"))
            </button>
      )
    </div>
}

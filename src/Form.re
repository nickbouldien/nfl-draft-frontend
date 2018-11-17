type state = {
  editText: string,
};

type action =
  | Submit
  | KeyDown(int)
  | Change(string);

let component = ReasonReact.reducerComponent("Form");

let make =
    (
      ~alertUser,
      ~draftPlayer,
      _children,
    ) => {
  let submitHelper = state =>
    switch (String.trim(state.editText)) {
    | "" => ReasonReact.SideEffects((_self => alertUser()))
    | nonEmptyValue =>
      ReasonReact.UpdateWithSideEffects(
        {editText: nonEmptyValue},
        (_self => draftPlayer(nonEmptyValue)),
      )
    };
  {
    ...component,
    initialState: () => {
      editText: "",
    },
    reducer: action =>
      switch (action) {
      | Submit => submitHelper
      | Change(text) => (
          _state =>
            ReasonReact.Update({editText: text})
        )
      | KeyDown(13) => submitHelper
      | KeyDown(_) => (_state => ReasonReact.NoUpdate)
      },
    render: ({state, send}) => {
      <li>
        <input
          className="edit"
          value=state.editText
          onBlur=(_event => send(Submit))
          onChange=(
            event => send(Change(ReactEvent.Form.target(event)##value))
          )
          onKeyDown=(
            event => send(KeyDown(ReactEvent.Keyboard.which(event)))
          )
        />
      </li>;
    },
  };
};

/* TODO: use env vars and make this dynamic */
let rootUrl = "http://localhost:8080/";

type player = {
  drafted: bool,
  id: int,
  name: string,
  position: string,
  school: string,
};

module Decode = {
  let p = json : player =>
    Json.Decode.{
      id: json |> field("id", int),
      name: json |> field("name", string),
      school: json |> field("school", string),
      position: json |> field("position", string),
      drafted: json |> field("drafted", bool),
    }
  let players = json : array(player) => Json.Decode.array(p, json)
};

type state =
  | Error
  | Loading
  | Loaded(array(player))

type action =
  | PlayersFetch
  | PlayersFetched(array(player))
  | PlayersFailedToFetch
  | DraftPlayer(string)
  | Reset;

let component = ReasonReact.reducerComponent("DraftSection");

let make = (_children) => {
  ...component,
  initialState: _state => Loading,
  reducer: (action, _state) =>
    switch action {
    | PlayersFetched(players) => ReasonReact.Update(Loaded(players))
    | PlayersFailedToFetch => ReasonReact.Update(Error)      
    | PlayersFetch =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
          Js.Promise.(
            Fetch.fetchWithInit(
              rootUrl ++ "players/",
              Fetch.RequestInit.make(
                ~mode=Fetch.CORS,
                (),
              ),
            )
            |> then_(Fetch.Response.json)
            |> then_(json =>
                json
                |> Decode.players
                |> (players => self.send(PlayersFetched(players)))
                |> resolve
              )
            |> catch(err => {
                Js.log(err)
                Js.Promise.resolve(self.send(PlayersFailedToFetch))
            })
            |> ignore
          )
        ),
      )
    | DraftPlayer(id) => ReasonReact.UpdateWithSideEffects(
      Loading,
      (
        self =>
        Js.Promise.(
          Fetch.fetchWithInit(
            rootUrl ++ "players/" ++ id,
            Fetch.RequestInit.make(
              ~mode=Fetch.CORS,
              ~method_=Fetch.Post,
              (),
            ),
          )
          |> then_(Fetch.Response.json)
          |> then_(_json =>
              Js.Promise.resolve(self.send(PlayersFetch))
            )
          |> catch(err => {
              Js.log(err)
              Js.Promise.resolve(self.send(PlayersFetch))
          })
          |> ignore
        )
      ),
    )
    | Reset => ReasonReact.UpdateWithSideEffects(
      Loading,
      (
        self =>
        Js.Promise.(
          Fetch.fetchWithInit(
            rootUrl ++ "reset",
            Fetch.RequestInit.make(
              ~mode=Fetch.CORS,
              (),
            ),
          )
          |> then_(Fetch.Response.json)
          |> then_(_json =>
              Js.Promise.resolve(self.send(PlayersFetch))
            )
          |> catch(err => {
              Js.log(err)
              Js.Promise.resolve(self.send(PlayersFetch))
          })
          |> ignore
        )
      ),
    )    
  },
  didMount: self => self.send(PlayersFetch),
  render: self => {
    switch (self.state) {
    | Error => <div> (ReasonReact.string("An error occurred!")) </div>
    | Loading => <div> (ReasonReact.string("Loading...")) </div>
    | Loaded(players) =>
      <div className="draft-section">
        <Button func={_evt => self.send(PlayersFetch)} message="Refetch players" />

        <Button func={_evt => self.send(Reset)} message="Reset all" />

        <div className="player-section">
          <div className="players undrafted-section">            
            <Header size="h3" message="undrafted players" />
            <div className="player-list">
              {
                let undraftedPlayers = players
                  |> Array.to_list
                  |> List.filter(player => player.drafted == false)
                  |> Array.of_list

                let num = Array.length(undraftedPlayers)
                  switch num {
                  | 0 => <p>(ReasonReact.string("no undrafted players"))</p>
                  | _ =>
                    undraftedPlayers
                    |> Array.map(player =>
                      <PlayerCard
                        key = string_of_int(player.id)
                        name = player.name
                        id = player.id
                        drafted = player.drafted
                        draft=(_event => self.send(DraftPlayer(string_of_int(player.id))))
                        position = player.position
                        school = player.school
                      />
                    )
                    |> ReasonReact.array
                  };                   
              }
            </div>
          </div>

          <div className="players drafted-section">
            <Header size="h3" message="drafted players" />
            <div className="player-list">
              {
                let draftedPlayers = players
                  |> Array.to_list
                  |> List.filter(player => player.drafted == true)
                  |> Array.of_list

                let num = Array.length(draftedPlayers)
                  switch num {
                  | 0 => <p>(ReasonReact.string("no drafted players"))</p>
                  | _ =>
                    draftedPlayers
                    |> Array.map(player =>
                      <PlayerCard
                        key = string_of_int(player.id)
                        name = player.name
                        id = player.id
                        drafted = player.drafted
                        draft = ((_event) => ())
                        position = player.position
                        school = player.school
                      />
                    )
                    |> ReasonReact.array
                  }; 
              }
            </div>
          </div>
        </div>
      </div>
    }
  }
}

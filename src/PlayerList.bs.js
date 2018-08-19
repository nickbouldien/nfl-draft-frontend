// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE

import * as $$Array from "bs-platform/lib/es6/array.js";
import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Json_decode from "@glennsl/bs-json/src/Json_decode.bs.js";
import * as ReasonReact from "reason-react/src/ReasonReact.js";

var rootUrl = "http://localhost:8080/";

function p(json) {
  return /* record */[
          /* id */Json_decode.field("id", Json_decode.$$int, json),
          /* name */Json_decode.field("name", Json_decode.string, json),
          /* position */Json_decode.field("position", Json_decode.string, json),
          /* school */Json_decode.field("school", Json_decode.string, json),
          /* drafted */Json_decode.field("drafted", Json_decode.bool, json)
        ];
}

function players(json) {
  return Json_decode.array(p, json);
}

var Decode = /* module */[
  /* p */p,
  /* players */players
];

var component = ReasonReact.statelessComponent("Player");

function make(player, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              return React.createElement("div", {
                          className: "player"
                        }, player[/* name */1]);
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

var Player = /* module */[
  /* component */component,
  /* make */make
];

function sendQuery() {
  console.log("sendQuery called");
  return /* () */0;
}

var component$1 = ReasonReact.reducerComponent("PlayerList");

function make$1() {
  return /* record */[
          /* debugName */component$1[/* debugName */0],
          /* reactClassInternal */component$1[/* reactClassInternal */1],
          /* handedOffState */component$1[/* handedOffState */2],
          /* willReceiveProps */component$1[/* willReceiveProps */3],
          /* didMount */(function (self) {
              return Curry._1(self[/* send */3], /* PlayersFetch */0);
            }),
          /* didUpdate */component$1[/* didUpdate */5],
          /* willUnmount */component$1[/* willUnmount */6],
          /* willUpdate */component$1[/* willUpdate */7],
          /* shouldUpdate */component$1[/* shouldUpdate */8],
          /* render */(function (self) {
              var match = self[/* state */1];
              if (typeof match === "number") {
                if (match !== 0) {
                  return React.createElement("div", undefined, "Loading...");
                } else {
                  return React.createElement("div", undefined, "An error occurred!");
                }
              } else {
                return React.createElement("div", undefined, React.createElement("h3", undefined, "Players"), React.createElement("ul", undefined, $$Array.map((function (player) {
                                      return React.createElement("li", {
                                                  key: String(player[/* id */0])
                                                }, ReasonReact.element(undefined, undefined, make(player, /* array */[])));
                                    }), match[0])));
              }
            }),
          /* initialState */(function () {
              return /* Loading */1;
            }),
          /* retainedProps */component$1[/* retainedProps */11],
          /* reducer */(function (action, _) {
              if (typeof action === "number") {
                if (action !== 0) {
                  return /* Update */Block.__(0, [/* Error */0]);
                } else {
                  return /* UpdateWithSideEffects */Block.__(2, [
                            /* Loading */1,
                            (function (self) {
                                fetch(rootUrl).then((function (prim) {
                                            return prim.json();
                                          })).then((function (json) {
                                          var players = Json_decode.array(p, json);
                                          return Promise.resolve(Curry._1(self[/* send */3], /* PlayersFetched */[players]));
                                        })).catch((function () {
                                        return Promise.resolve(Curry._1(self[/* send */3], /* PlayersFailedToFetch */1));
                                      }));
                                return /* () */0;
                              })
                          ]);
                }
              } else {
                return /* Update */Block.__(0, [/* Loaded */[action[0]]]);
              }
            }),
          /* jsElementWrapped */component$1[/* jsElementWrapped */13]
        ];
}

export {
  rootUrl ,
  Decode ,
  Player ,
  sendQuery ,
  component$1 as component,
  make$1 as make,
  
}
/* component Not a pure module */

# nfl_draft_reason

This is the super simple frontend for [https://github.com/nickbouldien/nfl_draft](https://github.com/nickbouldien/nfl_draft) made with [reason](https://reasonml.github.io/) and [reason-react](https://reasonml.github.io/reason-react/).

## Inspiration
I had read good things about reason and wanted to mess around with it a bit, so I used this small project as an introduction to reason and reason-react.  I plan to iterate on this a bit as I learn more about reason and will add more functionality, refactor, and better structure the app.

## Run Project
```sh
yarn install
yarn start
# in another tab
yarn run webpack
```

After you see the webpack compilation succeed (the `yarn run webpack` step), open up `src/index.html` (**no server needed!**). Then modify whichever `.re` file in `src` and refresh the page to see the changes.

## Sources:
- https://reasonml.github.io/reason-react/en/
- https://reasonml.github.io/en/
- https://jaredforsyth.com/posts/a-reason-react-tutorial/#3-bsconfig-json
- https://css-tricks.com/overriding-default-button-styles/

## TODOs:
- add routes (home, about, etc.)
- write tests (currently just installed jest and have a few test stubs to verify that jest works)
- have form to create a new player

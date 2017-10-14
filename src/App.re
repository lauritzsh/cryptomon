open Helpers;

let component = ReasonReact.statelessComponent "App";

let make _children => {
  ...component,
  render: fun _self => <h2> (se "Hello, World") </h2>
};

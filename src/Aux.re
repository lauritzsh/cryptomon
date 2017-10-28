open Helpers;

let component = ReasonReact.statelessComponent("Aux");

let make = (children) => {
  ...component,
  render: (_self) =>
    ae(
      Array.mapi(
        (i, child) => ReasonReact.cloneElement(child, ~props={"key": i}, [||]),
        children
      )
    )
};

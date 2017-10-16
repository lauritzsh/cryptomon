open Helpers;

let component = ReasonReact.statelessComponent "Aux";

let make children => {
  ...component,
  render: fun _self =>
    ae (
      Array.mapi
        (fun i child => ReasonReact.cloneElement child props::{"key": i} [||])
        children
    )
};

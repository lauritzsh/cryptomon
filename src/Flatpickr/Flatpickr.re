open Helpers;

loadCSS "flatpickr/dist/flatpickr.css";

loadCSS "./Flatpickr.css";

external flatpickr : ReasonReact.reactClass =
  "default" [@@bs.module "react-flatpickr"];

let make ::onChange children =>
  ReasonReact.wrapJsForReason
    reactClass::flatpickr
    props::{
      "onChange": onChange,
      "options": {
        "enableTime": Js.true_,
        "defaultDate": timestamp (),
        "time_24hr": Js.true_
      }
    }
    children;

open Helpers;

loadCSS("flatpickr/dist/flatpickr.css");

loadCSS("./Flatpickr.css");

[@bs.module "react-flatpickr"] external flatpickr : ReasonReact.reactClass = "default";

let make = (~onChange, ~className, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=flatpickr,
    ~props={
      "className": className,
      "onChange": onChange,
      "options": {"enableTime": Js.true_, "defaultDate": timestamp(), "time_24hr": Js.true_}
    },
    children
  );

open Helpers;

loadCSS("./Inputs.css");

module Button = {
  let component = ReasonReact.statelessComponent("Button");
  let make = (~value, ~onClick, ~disabled=false, _children) => {
    ...component,
    render: (_self) =>
      <button disabled=(Js.Boolean.to_js_boolean(disabled)) onClick> (se(value)) </button>
  };
};

module ActionButton = {
  let component = ReasonReact.statelessComponent("ActionButton");
  let make = (~image, ~onClick, ~squared=false, ~disabled=false, _children) => {
    ...component,
    render: (_self) =>
      <button
        className=("action" ++ (if (squared) {" squared"} else {""}))
        disabled=(Js.Boolean.to_js_boolean(disabled))
        onClick>
        <img src=image />
      </button>
  };
};

module Number = {
  let component = ReasonReact.statelessComponent("NumberInput");
  let make = (~value, ~onChange, ~placeholder="", _children) => {
    ...component,
    render: (_self) => <input _type="number" value onChange placeholder />
  };
};

type options = list((string, string));

module Select = {
  let component = ReasonReact.statelessComponent("SelectInput");
  let make = (~value, ~onChange, ~options, ~selectText="", _children) => {
    ...component,
    render: (_self) => {
      let options =
        options |> List.map(((value, text)) => <option key=value value> (se(text)) </option>) |> le;
      <select value onChange>
        (
          selectText == "" ?
            ReasonReact.nullElement :
            <option disabled=Js.true_ value=""> (se(selectText)) </option>
        )
        options
      </select>
    }
  };
};

module Date = {
  exception WrongDateSelection;
  let component = ReasonReact.statelessComponent("DateInput");
  let make = (~onChange, _children) => {
    ...component,
    render: (_self) => {
      let handleChange = (dates) =>
        switch dates {
        | [date] => onChange(timestamp_of_date(date))
        | _ => raise(WrongDateSelection)
        };
      <Flatpickr className="input" onChange=handleChange />
    }
  };
};

module CurrencyInput = {
  let component = ReasonReact.statelessComponent("CurrencyInput");
  let make = (~crypto, ~cash, _children) => {
    ...component,
    render: (_self) => <Aux> crypto <div className="divider"> (se("OR")) </div> cash </Aux>
  };
};

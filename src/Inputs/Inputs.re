open Helpers;

loadCSS "./Inputs.css";

module Button = {
  let component = ReasonReact.statelessComponent "Button";
  let make ::value ::onClick _children => {
    ...component,
    render: fun _self =>
      <div className="button"> <button onClick> (se value) </button> </div>
  };
};

module ActionButton = {
  let component = ReasonReact.statelessComponent "ActionButton";
  let make ::value ::onClick _children => {
    ...component,
    render: fun _self =>
      <div className="button action">
        <button onClick> (se value) </button>
      </div>
  };
};

module Number = {
  let component = ReasonReact.statelessComponent "NumberInput";
  let make ::value ::onChange ::placeholder="" _children => {
    ...component,
    render: fun _self =>
      <div className="input number">
        <input _type="number" value onChange placeholder />
      </div>
  };
};

type options = list (string, string);

module Select = {
  let component = ReasonReact.statelessComponent "SelectInput";
  let make ::value ::onChange ::options ::selectText="Select one" _children => {
    ...component,
    render: fun _self => {
      let options =
        options
        |> List.map (
             fun (value, text) => <option key=value value> (se text) </option>
           )
        |> le;
      <div className="input select">
        <select value onChange>
          <option disabled=Js.true_ value=""> (se selectText) </option>
          options
        </select>
      </div>
    }
  };
};
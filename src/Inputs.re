open Helpers;

module Text = {
  let component = ReasonReact.statelessComponent "TextInput";
  let make _children => {
    ...component,
    render: fun _self => <input _type="text" />
  };
};

module Number = {
  let component = ReasonReact.statelessComponent "NumberInput";
  let make ::value ::onChange ::placeholder="" _children => {
    ...component,
    render: fun _self => <input _type="number" value onChange placeholder />
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
      <select value onChange>
        <option value=""> (se selectText) </option>
        options
      </select>
    }
  };
};

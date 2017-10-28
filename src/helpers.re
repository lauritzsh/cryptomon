[@bs.val] external loadCSS : string => unit = "require";

[@bs.val] external loadResource : string => string = "require";

[@bs.send] external fixed : (float, int) => string = "toFixed";

[@bs.val] external inf : float = "Infinity";

type date;

[@bs.new] external create_date : float => date = "Date";

[@bs.send] external string_of_date : date => string = "toLocaleString";

[@bs.send] external timestamp_of_date : date => float = "getTime";

[@bs.val] external timestamp : unit => float = "Date.now";

let string_of_timestamp = (ts) => ts |> create_date |> string_of_date;

let st = string_of_timestamp;

let se = ReasonReact.stringToElement;

let ae = ReasonReact.arrayToElement;

let le = (ls) => ls |> Array.of_list |> ReasonReact.arrayToElement;

let si = string_of_int;

let is = int_of_string;

let sf = string_of_float;

let fs = float_of_string;

let sup = String.uppercase;

let slo = String.lowercase;

let valueFromEvent = (evt) => {
  let obj = evt |> ReactEventRe.Form.target |> ReactDOMRe.domElementToObj;
  obj##value
};

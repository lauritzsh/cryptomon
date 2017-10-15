external loadCSS : string => unit = "require" [@@bs.val];

type date;

external create_date : int => date = "Date" [@@bs.new];

external string_of_date : date => string = "toLocaleString" [@@bs.send];

external timestamp : unit => int = "Date.now" [@@bs.val];

let string_of_timestamp ts => ts |> create_date |> string_of_date;

let st ts => ts |> create_date |> string_of_date;

let se = ReasonReact.stringToElement;

let ae = ReasonReact.arrayToElement;

let le ls => ls |> Array.of_list |> ReasonReact.arrayToElement;

let si = string_of_int;

let is = int_of_string;

let sf = string_of_float;

let fs = float_of_string;

let sup = String.uppercase;

let valueFromEvent evt => {
  let obj = evt |> ReactEventRe.Form.target |> ReactDOMRe.domElementToObj;
  obj##value
};

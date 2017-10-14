external loadCSS : string => unit = "require" [@@bs.val];

type date;

external create_date : int => date = "Date" [@@bs.new];

external string_of_date : date => string = "toLocaleString" [@@bs.send];

let string_of_timestamp ts => ts |> create_date |> string_of_date;

let st ts => ts |> create_date |> string_of_date;

let se = ReasonReact.stringToElement;

let ae = ReasonReact.arrayToElement;

let le ls => ls |> Array.of_list |> ReasonReact.arrayToElement;

let si = string_of_int;

let sf = string_of_float;

let sup = String.uppercase;

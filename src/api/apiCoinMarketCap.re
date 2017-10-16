open Helpers;

module Decode = {
  open Currency;
  open! Json.Decode;
  let crypto json => {
    id: field "id" string json,
    name: field "name" string json,
    usd_rate: field "price_usd" string json |> fs,
    btc_rate: field "price_btc" string json |> fs
  };
};

let fetch onReceive =>
  Js.Promise.(
    Fetch.(
      fetch "https://api.coinmarketcap.com/v1/ticker/"
      |> then_ Response.text
      |> then_ (fun text => Js.Json.parseExn text |> resolve)
      |> then_ (fun json => json |> Json.Decode.list Decode.crypto |> resolve)
      |> then_ (fun cryptos => onReceive cryptos |> resolve)
      |> ignore
    )
  );

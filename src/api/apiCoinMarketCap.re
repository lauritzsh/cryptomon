open Helpers;

module Decode = {
  open Currency.Crypto;
  open! Json.Decode;
  let crypto = (json) => {
    id: field("id", string, json),
    name: field("name", string, json),
    symbol: field("symbol", string, json),
    /* Price for both might be `null` */
    usd_rate:
      try (field("price_usd", string, json) |> fs) {
      | DecodeError(_) => 0.0
      },
    btc_rate:
      try (field("price_btc", string, json) |> fs) {
      | DecodeError(_) => 0.0
      }
  };
};

let fetch = (onReceive) =>
  Js.Promise.(
    Fetch.(
      fetch("https://api.coinmarketcap.com/v1/ticker/")
      |> then_(Response.text)
      |> then_((text) => Js.Json.parseExn(text) |> resolve)
      |> then_((json) => json |> Json.Decode.list(Decode.crypto) |> resolve)
      |> then_((cryptos) => onReceive(cryptos) |> resolve)
      |> ignore
    )
  );

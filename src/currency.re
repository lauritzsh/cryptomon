/* dollar, euro etc. */
type cash = {
  id: string, /* usd, eur etc. */
  usd_rate: float
};

/* BTC, ETH etc. */
type crypto = {
  id: string, /* btc, eth etc. */
  name: string, /* Bitcoin, Ethereum etc. */
  usd_rate: float,
  btc_rate: float
};

type currency =
  | Cash cash
  | Crypto crypto;

/* Sample data for development */
module Data = {
  let usd = {id: "usd", usd_rate: 1.0};
  let cashes = [(usd.id, usd)];
  let btc = {id: "btc", name: "Bitcoin", usd_rate: 5709.4, btc_rate: 1.0};
  let ltc = {id: "ltc", name: "Litecoin", usd_rate: 60.75, btc_rate: 0.010626};
  let neo = {id: "neo", name: "NEO", usd_rate: 28.88, btc_rate: 0.00503792};
  let cryptos = [(btc.id, btc), (ltc.id, ltc), (neo.id, neo)];
};

module Encode = {
  open! Json.Encode;
  let cash (c: cash) =>
    object_ [
      ("type", string "cash"),
      ("id", string c.id),
      ("usd_rate", float c.usd_rate)
    ];
  let crypto c =>
    object_ [
      ("type", string "crypto"),
      ("id", string c.id),
      ("name", string c.name),
      ("usd_rate", float c.usd_rate),
      ("btc_rate", float c.btc_rate)
    ];
  let currency c =>
    switch c {
    | Crypto crypto' => crypto crypto'
    | Cash cash' => cash cash'
    };
};

module Decode = {
  open! Json.Decode;
  exception DecodeException string;
  let cash json => {
    id: field "id" string json,
    usd_rate: field "usd_rate" float json
  };
  let crypto json => {
    id: field "id" string json,
    name: field "name" string json,
    usd_rate: field "usd_rate" float json,
    btc_rate: field "btc_rate" float json
  };
  let currency json =>
    switch (field "type" string json) {
    | "cash" => Cash (cash json)
    | "crypto" => Crypto (crypto json)
    | currency => raise (DecodeException (currency ^ ": not found"))
    };
};

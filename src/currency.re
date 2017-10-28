module Cash = {
  /* dollar, euro etc. */
  type t = {
    id: string, /* usd, eur etc. */
    code: string, /* USD, EUR etc. */
    usd_rate: float
  };
  type id = string;
  open! Json.Encode;
  let encode = (c) =>
    object_([
      ("type", string("cash")),
      ("id", string(c.id)),
      ("code", string(c.code)),
      ("usd_rate", float(c.usd_rate))
    ]);
  open! Json.Decode;
  let decode = (json) => {
    id: field("id", string, json),
    code: field("code", string, json),
    usd_rate: field("usd_rate", float, json)
  };
};

module Crypto = {
  /* BTC, ETH etc. */
  type t = {
    id: string, /* btc, eth etc. */
    name: string, /* Bitcoin, Ethereum etc. */
    symbol: string, /* BTC, ETH etc. */
    usd_rate: float,
    btc_rate: float
  };
  type id = string;
  open! Json.Encode;
  let encode = (c) =>
    object_([
      ("type", string("crypto")),
      ("id", string(c.id)),
      ("name", string(c.name)),
      ("symbol", string(c.symbol)),
      ("usd_rate", float(c.usd_rate)),
      ("btc_rate", float(c.btc_rate))
    ]);
  open! Json.Decode;
  let decode = (json) => {
    id: field("id", string, json),
    name: field("name", string, json),
    symbol: field("symbol", string, json),
    usd_rate: field("usd_rate", float, json),
    btc_rate: field("btc_rate", float, json)
  };
};

type currency =
  | Cash(Cash.id)
  | Crypto(Crypto.id);

module Encode = {
  let currency = (c) =>
    switch c {
    | Crypto(crypto_id) => crypto_id
    | Cash(cash_id) => cash_id
    };
};

module Decode = {
  open! Json.Decode;
  exception DecodeException(string);
  let currency = (json) =>
    switch (field("type", string, json)) {
    | "cash" => Cash(field("id", string, json))
    | "crypto" => Crypto(field("id", string, json))
    | currency => raise(DecodeException(currency ++ ": not found"))
    };
};

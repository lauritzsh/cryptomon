open Currency;

type spend = float;

type received = float;

type kind =
  | Buy Cash.id spend Crypto.id received
  | Sell Crypto.id spend Cash.id received
  | Deposit currency received
  | Withdraw currency spend
  | Exchange Crypto.id spend Crypto.id received;

type t = {
  timestamp: float, /* epoch in milliseconds */
  note: string,
  kind
};

module Encode = {
  open! Json.Encode;
  let currency' =
    fun
    | Cash cash_id => string cash_id
    | Crypto crypto_id => string crypto_id;
  let kind =
    fun
    | Buy cash_id spend crypto_id received =>
      object_ [
        ("type", string "buy"),
        ("cash_id", string cash_id),
        ("crypto_id", string crypto_id),
        ("received", float received),
        ("spend", float spend)
      ]
    | Sell crypto_id spend cash_id received =>
      object_ [
        ("type", string "sell"),
        ("cash_id", string cash_id),
        ("crypto_id", string crypto_id),
        ("received", float received),
        ("spend", float spend)
      ]
    | Deposit currency received =>
      object_ [
        ("type", string "deposit"),
        ("currency", currency' currency),
        ("received", float received)
      ]
    | Withdraw currency spend =>
      object_ [
        ("type", string "withdraw"),
        ("currency", currency' currency),
        ("spend", float spend)
      ]
    | Exchange from_crypto_id spend to_crypto_id received =>
      object_ [
        ("type", string "exchange"),
        ("from_crypto_id", string from_crypto_id),
        ("to_crypto_id", string to_crypto_id),
        ("received", float received),
        ("spend", float spend)
      ];
  let transaction t =>
    object_ [
      ("timestamp", float t.timestamp),
      ("note", string t.note),
      ("kind", kind t.kind)
    ];
};

module Decode = {
  open! Json.Decode;
  open Currency.Decode;
  exception DecodeException string;
  let kind json =>
    switch (field "type" string json) {
    | "buy" =>
      Buy
        (field "cash_id" string json)
        (field "spend" float json)
        (field "crypto_id" string json)
        (field "received" float json)
    | "sell" =>
      Sell
        (field "crypto_id" string json)
        (field "spend" float json)
        (field "cash_id" string json)
        (field "received" float json)
    | "deposit" =>
      Deposit (field "currency" currency json) (field "received" float json)
    | "withdraw" =>
      Withdraw (field "currency" currency json) (field "spend" float json)
    | "exchange" =>
      Exchange
        (field "from_crypto_id" string json)
        (field "spend" float json)
        (field "to_crypto_id" string json)
        (field "received" float json)
    | kind => raise (DecodeException (kind ^ ": not found"))
    };
  let transaction json => {
    timestamp: field "timestamp" float json,
    note: field "note" string json,
    kind: field "kind" kind json
  };
};

open Currency;

type spend = float;

type received = float;

type kind =
  | Buy cash spend crypto received
  | Sell crypto spend cash received
  | Deposit currency received
  | Withdraw currency spend
  | Exchange crypto spend crypto received;

type transaction = {
  timestamp: float, /* epoch in milliseconds */
  note: string,
  kind
};

/* Sample data for development */
module Data = {
  open Currency.Data;
  let transaction = {timestamp: 3.0, note: "", kind: Buy usd 50. btc 1.0};
  let transactions = [
    {timestamp: 7.0, note: "", kind: Exchange btc 0.1 ltc 1.0},
    {timestamp: 6.0, note: "", kind: Withdraw (Cash usd) 10.0},
    {timestamp: 5.0, note: "", kind: Sell btc 0.1 usd 200.0},
    {timestamp: 4.0, note: "", kind: Withdraw (Crypto btc) 0.3},
    {timestamp: 3.0, note: "", kind: Buy usd 50. btc 1.0},
    {timestamp: 2.0, note: "", kind: Deposit (Crypto btc) 0.5},
    {timestamp: 1.0, note: "", kind: Deposit (Cash usd) 100.0}
  ];
};

module Encode = {
  open! Json.Encode;
  let la (cryptos: list (string, Currency.crypto)) cryptoId =>
    List.assoc cryptoId cryptos;
  let currency' (cryptos: list (string, Currency.crypto)) =>
    fun
    | Cash cash => Currency.Encode.cash cash
    | Crypto crypto => Currency.Encode.crypto (la cryptos crypto.id);
  let kind (cryptos: list (string, Currency.crypto)) m =>
    switch m {
    | Buy cash spend crypto received =>
      object_ [
        ("type", string "buy"),
        ("cash", Currency.Encode.cash cash),
        ("crypto", Currency.Encode.crypto (la cryptos crypto.id)),
        ("received", float received),
        ("spend", float spend)
      ]
    | Sell crypto spend cash received =>
      object_ [
        ("type", string "sell"),
        ("cash", Currency.Encode.cash cash),
        ("crypto", Currency.Encode.crypto (la cryptos crypto.id)),
        ("received", float received),
        ("spend", float spend)
      ]
    | Deposit currency received =>
      object_ [
        ("type", string "deposit"),
        ("currency", currency' cryptos currency),
        ("received", float received)
      ]
    | Withdraw currency spend =>
      object_ [
        ("type", string "withdraw"),
        ("currency", currency' cryptos currency),
        ("spend", float spend)
      ]
    | Exchange from spend _to received =>
      object_ [
        ("type", string "exchange"),
        ("from", Currency.Encode.crypto (la cryptos from.id)),
        ("to", Currency.Encode.crypto (la cryptos _to.id)),
        ("received", float received),
        ("spend", float spend)
      ]
    };
  let transaction (cryptos: list (string, Currency.crypto)) t =>
    object_ [
      ("timestamp", float t.timestamp),
      ("note", string t.note),
      ("kind", kind cryptos t.kind)
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
        (field "cash" cash json)
        (field "spend" float json)
        (field "crypto" crypto json)
        (field "received" float json)
    | "sell" =>
      Sell
        (field "crypto" crypto json)
        (field "spend" float json)
        (field "cash" cash json)
        (field "received" float json)
    | "deposit" =>
      Deposit (field "currency" currency json) (field "received" float json)
    | "withdraw" =>
      Withdraw (field "currency" currency json) (field "spend" float json)
    | "exchange" =>
      Exchange
        (field "from" crypto json)
        (field "spend" float json)
        (field "to" crypto json)
        (field "received" float json)
    | kind => raise (DecodeException (kind ^ ": not found"))
    };
  let transaction json => {
    timestamp: field "timestamp" float json,
    note: field "note" string json,
    kind: field "kind" kind json
  };
};

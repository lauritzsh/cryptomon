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
  timestamp: int, /* epoch in milliseconds */
  note: string,
  kind
};

/* Sample data for development */
module Data = {
  open Currency.Data;
  let transactions = [
    {timestamp: 7, note: "", kind: Exchange btc 0.1 ltc 1.0},
    {timestamp: 6, note: "", kind: Withdraw (Cash usd) 10.0},
    {timestamp: 5, note: "", kind: Sell btc 0.1 usd 200.0},
    {timestamp: 4, note: "", kind: Withdraw (Crypto btc) 0.3},
    {timestamp: 3, note: "", kind: Buy usd 50. btc 1.0},
    {timestamp: 2, note: "", kind: Deposit (Crypto btc) 0.5},
    {timestamp: 1, note: "", kind: Deposit (Cash usd) 100.0}
  ];
};

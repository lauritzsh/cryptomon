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

open Helpers;

loadCSS "./App.css";

type state = {
  transactions: list Transaction.transaction,
  cashes: list (string, Currency.cash),
  cryptos: list (string, Currency.crypto)
};

type action =
  | AddTransaction Transaction.transaction
  | DeleteTransaction Transaction.transaction;

let component = ReasonReact.reducerComponent "App";

let make _children => {
  ...component,
  initialState: fun () => {
    transactions: Transaction.Data.transactions,
    cashes: Currency.Data.cashes,
    cryptos: Currency.Data.cryptos
  },
  reducer: fun action state =>
    switch action {
    | AddTransaction _transaction => ReasonReact.Update state
    | DeleteTransaction _transaction => ReasonReact.Update state
    },
  render: fun {state: {transactions, cryptos}} =>
    <div className="app">
      <Portfolio cryptos transactions />
      <TransactionTable transactions />
    </div>
};

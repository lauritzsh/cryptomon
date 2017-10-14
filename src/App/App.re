open Helpers;

loadCSS "./App.css";

type state = {
  transactions: list Transaction.transaction,
  cashes: list (string, Currency.cash),
  cryptos: list (string, Currency.crypto)
};

type action =
  | Add Transaction.transaction
  | Delete Transaction.transaction;

let delete transaction _event => Delete transaction;

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
    | Add _transaction => ReasonReact.Update state
    | Delete transaction =>
      let transactions =
        List.filter (fun txn => txn !== transaction) state.transactions;
      ReasonReact.Update {...state, transactions}
    },
  render: fun {reduce, state: {transactions, cryptos}} =>
    <div className="app">
      <Portfolio cryptos transactions />
      <TransactionTable
        transactions
        onDelete=(fun transaction => reduce (delete transaction))
      />
    </div>
};

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

let add kind => Add {timestamp: timestamp (), note: "", kind};

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
    | Add transaction =>
      ReasonReact.Update {
        ...state,
        transactions: [transaction, ...state.transactions]
      }
    | Delete transaction =>
      let transactions =
        List.filter (fun txn => txn !== transaction) state.transactions;
      ReasonReact.Update {...state, transactions}
    },
  render: fun {reduce, state: {transactions, cryptos, cashes}} =>
    <div className="app">
      <TransactionForm cryptos cashes onSubmit=(reduce add) />
      <Portfolio cryptos transactions />
      <TransactionTable
        transactions
        onDelete=(fun transaction => reduce (delete transaction))
      />
    </div>
};

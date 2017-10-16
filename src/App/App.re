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

module Encode = {
  open! Json.Encode;
  let state s =>
    object_ [
      ("transactions", (list Transaction.Encode.transaction) s.transactions),
      ("cashes", array [||]),
      ("cryptos", array [||])
    ];
};

module Decode = {
  open! Json.Decode;
  let state json => {
    transactions:
      field "transactions" (list Transaction.Decode.transaction) json,
    cryptos: Currency.Data.cryptos,
    cashes: Currency.Data.cashes
  };
};

let persist ({state}: ReasonReact.self state 'a action) =>
  Dom.Storage.setItem
    "state"
    (state |> Encode.state |> Js.Json.stringify)
    Dom.Storage.localStorage;

let initialState () =>
  switch (Dom.Storage.getItem "state" Dom.Storage.localStorage) {
  | Some state => state |> Js.Json.parseExn |> Decode.state
  | None => {
      transactions: Transaction.Data.transactions,
      cashes: Currency.Data.cashes,
      cryptos: Currency.Data.cryptos
    }
  };

let add kind => Add {timestamp: timestamp (), note: "", kind};

let delete transaction _event => Delete transaction;

let component = ReasonReact.reducerComponent "App";

let make _children => {
  ...component,
  initialState,
  reducer: fun action state =>
    switch action {
    | Add transaction =>
      ReasonReact.UpdateWithSideEffects
        {...state, transactions: [transaction, ...state.transactions]} persist
    | Delete transaction =>
      let transactions =
        List.filter (fun txn => txn !== transaction) state.transactions;
      ReasonReact.UpdateWithSideEffects {...state, transactions} persist
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

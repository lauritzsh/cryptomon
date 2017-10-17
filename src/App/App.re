open Helpers;

loadCSS "./App.css";

type state = {
  transactions: list Transaction.transaction,
  cashes: list (string, Currency.cash),
  cryptos: list (string, Currency.crypto)
};

type action =
  | ReceiveCashes (list Currency.cash)
  | ReceiveCryptos (list Currency.crypto)
  | Add Transaction.transaction
  | Delete Transaction.transaction;

module Encode = {
  open! Json.Encode;
  let state s =>
    object_ [
      ("transactions", (list Transaction.Encode.transaction) s.transactions),
      (
        "cashes",
        (list Currency.Encode.cash) (List.map (fun (_, c) => c) s.cashes)
      ),
      (
        "cryptos",
        (list Currency.Encode.crypto) (List.map (fun (_, c) => c) s.cryptos)
      )
    ];
};

module Decode = {
  open! Json.Decode;
  let state json => {
    transactions:
      field "transactions" (list Transaction.Decode.transaction) json,
    cryptos:
      json
      |> field "cryptos" (list Currency.Decode.crypto)
      |> List.map Currency.(fun crypto => (crypto.id, crypto)),
    cashes:
      json
      |> field "cashes" (list Currency.Decode.cash)
      |> List.map (fun (cash: Currency.cash) => (cash.id, cash))
  };
};

let sortTransactions state => {
  ...state,
  transactions:
    List.sort
      Transaction.(fun a b => b.timestamp -. a.timestamp |> int_of_float)
      state.transactions
};

let persist ({state}: ReasonReact.self state 'a action) =>
  Dom.Storage.setItem
    "state"
    (state |> sortTransactions |> Encode.state |> Js.Json.stringify)
    Dom.Storage.localStorage;

let initialState () =>
  switch (Dom.Storage.getItem "state" Dom.Storage.localStorage) {
  | Some state => state |> Js.Json.parseExn |> Decode.state
  | None => {transactions: [], cashes: Currency.Data.cashes, cryptos: []}
  };

let receiveCashes cashes => ReceiveCashes cashes;

let receiveCryptos cryptos => ReceiveCryptos cryptos;

let add (kind, timestamp) => Add {timestamp, note: "", kind};

let delete transaction _event => Delete transaction;

let loading cryptos cashes =>
  List.length cryptos === 0 || List.length cashes === 0;

let component = ReasonReact.reducerComponent "App";

let make _children => {
  ...component,
  initialState,
  didMount: fun self => {
    persist self;
    Api.Cash.fetch (self.reduce receiveCashes);
    Api.Crypto.fetch (self.reduce receiveCryptos);
    ReasonReact.NoUpdate
  },
  reducer: fun action state =>
    switch action {
    | ReceiveCashes cashes =>
      ReasonReact.UpdateWithSideEffects
        {
          ...state,
          cashes:
            List.map (fun (cash: Currency.cash) => (cash.id, cash)) cashes
        }
        persist
    | ReceiveCryptos cryptos =>
      ReasonReact.UpdateWithSideEffects
        {
          ...state,
          cryptos:
            List.map Currency.(fun crypto => (crypto.id, crypto)) cryptos
        }
        persist
    | Add transaction =>
      ReasonReact.UpdateWithSideEffects
        {...state, transactions: [transaction, ...state.transactions]} persist
    | Delete transaction =>
      let transactions =
        List.filter (fun txn => txn !== transaction) state.transactions;
      ReasonReact.UpdateWithSideEffects {...state, transactions} persist
    },
  render: fun {reduce, state: {transactions, cryptos, cashes}} =>
    loading cryptos cashes ?
      <div className="app"> <h1> (se "Loading...") </h1> </div> :
      <div className="app">
        <TransactionForm cryptos cashes onSubmit=(reduce add) />
        <Portfolio cryptos transactions />
        <TransactionTable
          transactions
          onDelete=(fun transaction => reduce (delete transaction))
        />
      </div>
};

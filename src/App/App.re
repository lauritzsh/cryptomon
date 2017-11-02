open Helpers;

loadCSS("./App.css");

type state = {
  transactions: list(Transaction.t),
  cashes: list((Currency.Cash.id, Currency.Cash.t)),
  cryptos: list((Currency.Crypto.id, Currency.Crypto.t)),
  showTutorial: bool
};

type action =
  | Sample
  | ReceiveCashes(list(Currency.Cash.t))
  | ReceiveCryptos(list(Currency.Crypto.t))
  | Add(Transaction.t)
  | Delete(Transaction.t);

module Encode = {
  open! Json.Encode;
  let snd = ((_, c)) => c;
  let state = (s) =>
    object_([
      ("transactions", (list(Transaction.Encode.transaction))(s.transactions)),
      ("cashes", (list(Currency.Cash.encode))(List.map(snd, s.cashes))),
      ("cryptos", (list(Currency.Crypto.encode))(List.map(snd, s.cryptos))),
      ("showTutorial", Js.Boolean.to_js_boolean(s.showTutorial) |> boolean)
    ]);
};

module Decode = {
  open Currency;
  open! Json.Decode;
  let state = (json) => {
    transactions: field("transactions", list(Transaction.Decode.transaction), json),
    cryptos:
      json
      |> field("cryptos", list(Currency.Crypto.decode))
      |> List.map(Crypto.((crypto) => (crypto.id, crypto))),
    cashes:
      json
      |> field("cashes", list(Currency.Cash.decode))
      |> List.map(Cash.((cash) => (cash.id, cash))),
    showTutorial: field("showTutorial", bool, json)
  };
};

let sortTransactions = (state) => {
  ...state,
  transactions:
    List.sort(
      Transaction.((a, b) => b.timestamp -. a.timestamp |> int_of_float),
      state.transactions
    )
};

let persist = ({state}: ReasonReact.self(state, 'a, action)) =>
  Dom.Storage.setItem(
    "state",
    state |> sortTransactions |> Encode.state |> Js.Json.stringify,
    Dom.Storage.localStorage
  );

let initialState = () =>
  switch (Dom.Storage.getItem("state", Dom.Storage.localStorage)) {
  | Some(state) => state |> Js.Json.parseExn |> Decode.state
  | None => {transactions: [], cashes: [], cryptos: [], showTutorial: true}
  };

let receiveCashes = (cashes) => ReceiveCashes(cashes);

let receiveCryptos = (cryptos) => ReceiveCryptos(cryptos);

let add = ((kind, timestamp)) => Add({timestamp, note: "", kind});

let sample = (_event) => Sample;

let delete = (transaction, _event) => Delete(transaction);

let loading = (cryptos, cashes) => List.length(cryptos) === 0 || List.length(cashes) === 0;

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState,
  didMount: (self) => {
    Api.Cash.fetch(self.reduce(receiveCashes));
    Api.Crypto.fetch(self.reduce(receiveCryptos));
    ReasonReact.NoUpdate
  },
  reducer: (action, state) =>
    Currency.(
      switch action {
      | Sample =>
        ReasonReact.UpdateWithSideEffects(
          {...state, showTutorial: false, transactions: Transaction.Sample.data},
          persist
        )
      | ReceiveCashes(cashes) =>
        ReasonReact.UpdateWithSideEffects(
          {...state, cashes: List.map(Cash.((cash) => (cash.id, cash)), cashes)},
          persist
        )
      | ReceiveCryptos(cryptos) =>
        ReasonReact.UpdateWithSideEffects(
          {...state, cryptos: List.map(Crypto.((crypto) => (crypto.id, crypto)), cryptos)},
          persist
        )
      | Add(transaction) =>
        ReasonReact.UpdateWithSideEffects(
          {...state, showTutorial: false, transactions: [transaction, ...state.transactions]},
          persist
        )
      | Delete(transaction) =>
        let transactions = List.filter((txn) => txn !== transaction, state.transactions);
        ReasonReact.UpdateWithSideEffects({...state, transactions}, persist)
      }
    ),
  render: ({reduce, state: {transactions, cryptos, cashes, showTutorial}}) =>
    loading(cryptos, cashes) ?
      <Aux>
        <div className="header" />
        <div className="loader"> <h1> (se("Getting data...")) </h1> </div>
      </Aux> :
      <div className="app">
        <div className="header" />
        <div className="body">
          (
            showTutorial ?
              <Tutorial cashes cryptos onSampleClick=(reduce(sample)) onSubmit=(reduce(add)) /> :
              <Aux>
                <TransactionForm cryptos cashes onSubmit=(reduce(add)) />
                <Portfolio cryptos cashes transactions />
                <TransactionTable
                  transactions
                  cashes
                  cryptos
                  onDelete=((transaction) => reduce(delete(transaction)))
                />
              </Aux>
          )
        </div>
        <Footer />
      </div>
};

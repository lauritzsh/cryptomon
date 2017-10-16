open Helpers;

loadCSS "./TransactionForm.css";

module FormInputs = TransactionFormInputs;

type values =
  | BuyValues string string string string
  | SellValues string string string string
  | DepositValues string string string
  | WithdrawValues string string string
  | ExchangeValues string string string string;

module BuyForm = {
  let component = ReasonReact.statelessComponent "BuyForm";
  let make
      ::kindInput
      ::cashInput
      ::cryptoInput
      ::receivedInput
      ::spendInput
      ::submitButton
      _children => {
    ...component,
    render: fun _self =>
      <Aux>
        kindInput
        receivedInput
        cryptoInput
        spendInput
        cashInput
        submitButton
      </Aux>
  };
};

module SellForm = {
  let component = ReasonReact.statelessComponent "SellForm";
  let make
      ::kindInput
      ::cashInput
      ::cryptoInput
      ::receivedInput
      ::spendInput
      ::submitButton
      _children => {
    ...component,
    render: fun _self =>
      <Aux>
        kindInput
        receivedInput
        cashInput
        spendInput
        cryptoInput
        submitButton
      </Aux>
  };
};

module DepositForm = {
  let component = ReasonReact.statelessComponent "SellForm";
  let make
      ::kindInput
      ::cashInput
      ::cryptoInput
      ::receivedInput
      ::submitButton
      _children => {
    ...component,
    render: fun _self =>
      <Aux>
        kindInput
        receivedInput
        cashInput
        <div className="divider"> (se "or") </div>
        cryptoInput
        submitButton
      </Aux>
  };
};

module WithdrawForm = {
  let component = ReasonReact.statelessComponent "SellForm";
  let make
      ::kindInput
      ::cashInput
      ::cryptoInput
      ::spendInput
      ::submitButton
      _children => {
    ...component,
    render: fun _self =>
      <Aux>
        kindInput
        spendInput
        cashInput
        <div className="divider"> (se "or") </div>
        cryptoInput
        submitButton
      </Aux>
  };
};

module ExchangeForm = {
  let component = ReasonReact.statelessComponent "SellForm";
  let make
      ::kindInput
      ::spendInput
      ::fromInput
      ::receivedInput
      ::toInput
      ::submitButton
      _children => {
    ...component,
    render: fun _self =>
      <Aux>
        kindInput
        spendInput
        fromInput
        receivedInput
        toInput
        submitButton
      </Aux>
  };
};

type kind =
  | Buy
  | Sell
  | Deposit
  | Withdraw
  | Exchange;

let string_of_kind =
  fun
  | Buy => "buy"
  | Sell => "sell"
  | Deposit => "deposit"
  | Withdraw => "withdraw"
  | Exchange => "exchange";

type state = {
  kind,
  received: string,
  spend: string,
  crypto: string,
  cash: string,
  from: string, /* exchange */
  _to: string /* exchange */
};

type action =
  | ChangeKind kind
  | ChangeReceived string
  | ChangeSpend string
  | ChangeCrypto string
  | ChangeCash string
  | ChangeFrom string
  | ChangeTo string;

exception UnknownKey;

let changeKind event =>
  ChangeKind (
    switch (valueFromEvent event) {
    | "buy" => Buy
    | "sell" => Sell
    | "deposit" => Deposit
    | "withdraw" => Withdraw
    | _ /* exchange */ => Exchange
    }
  );

let changeReceived event => ChangeReceived (valueFromEvent event);

let changeCrypto event => ChangeCrypto (valueFromEvent event);

let changeSpend event => ChangeSpend (valueFromEvent event);

let changeCash event => ChangeCash (valueFromEvent event);

let changeFrom event => ChangeFrom (valueFromEvent event);

let changeTo event => ChangeTo (valueFromEvent event);

let handleSubmit onSubmit values _event => onSubmit values;

let component = ReasonReact.reducerComponent "TransactionForm";

let make ::cryptos ::cashes ::onSubmit _children => {
  ...component,
  initialState: fun () => {
    kind: Buy,
    received: "",
    spend: "",
    crypto: "",
    cash: "",
    from: "",
    _to: ""
  },
  reducer: fun action state =>
    switch action {
    | ChangeKind kind => ReasonReact.Update {...state, kind}
    | ChangeReceived received => ReasonReact.Update {...state, received}
    | ChangeSpend spend => ReasonReact.Update {...state, spend}
    | ChangeCrypto crypto => ReasonReact.Update {...state, crypto}
    | ChangeCash cash => ReasonReact.Update {...state, cash}
    | ChangeFrom from => ReasonReact.Update {...state, from}
    | ChangeTo _to => ReasonReact.Update {...state, _to}
    },
  render:
    fun {reduce, state: {kind, received, spend, crypto, cash, from, _to}} => {
    let receivedInput =
      <Inputs.Number
        value=received
        onChange=(reduce changeReceived)
        placeholder="Received"
      />;
    let spendInput =
      <Inputs.Number
        value=spend
        onChange=(reduce changeSpend)
        placeholder="Spend"
      />;
    let cryptoInput =
      <Inputs.Select
        value=crypto
        onChange=(reduce changeCrypto)
        options=(List.map Currency.(fun (id, {name}) => (id, name)) cryptos)
        selectText="Select crypto"
      />;
    let cashInput =
      <Inputs.Select
        value=cash
        onChange=(reduce changeCash)
        options=(List.map (fun (id, _) => (id, sup id)) cashes)
        selectText="Select cash"
      />;
    let fromInput =
      <Inputs.Select
        value=from
        onChange=(reduce changeFrom)
        options=(List.map Currency.(fun (id, {name}) => (id, name)) cryptos)
        selectText="Select crypto"
      />;
    let toInput =
      <Inputs.Select
        value=_to
        onChange=(reduce changeTo)
        options=(List.map Currency.(fun (id, {name}) => (id, name)) cryptos)
        selectText="Select crypto"
      />;
    let kindInput =
      <Inputs.Select
        value=(string_of_kind kind)
        onChange=(reduce changeKind)
        options=[
          ("buy", "Buy"),
          ("sell", "Sell"),
          ("deposit", "Deposit"),
          ("withdraw", "Withdraw"),
          ("exchange", "Exchange")
        ]
      />;
    let handleSubmit _event => {
      open! Transaction;
      open! Currency;
      let cash' () => List.assoc cash cashes;
      let spend' () => fs spend;
      let crypto' () => List.assoc crypto cryptos;
      let received' () => fs received;
      let from' () => List.assoc from cryptos;
      let to' () => List.assoc _to cryptos;
      let currency' () => crypto != "" ? Crypto (crypto' ()) : Cash (cash' ());
      switch kind {
      | Buy =>
        onSubmit (Buy (cash' ()) (spend' ()) (crypto' ()) (received' ()))
      | Sell =>
        onSubmit (Sell (crypto' ()) (spend' ()) (cash' ()) (received' ()))
      | Deposit => onSubmit (Deposit (currency' ()) (received' ()))
      | Withdraw => onSubmit (Withdraw (currency' ()) (spend' ()))
      | Exchange =>
        onSubmit (Exchange (from' ()) (spend' ()) (to' ()) (received' ()))
      }
    };
    let submitButton = <Inputs.Button value="+" onClick=handleSubmit />;
    <div className="transaction-form">
      (
        switch kind {
        | Buy =>
          <BuyForm
            kindInput
            cashInput
            cryptoInput
            receivedInput
            spendInput
            submitButton
          />
        | Sell =>
          <SellForm
            kindInput
            cashInput
            cryptoInput
            receivedInput
            spendInput
            submitButton
          />
        | Deposit =>
          <DepositForm
            kindInput
            cashInput
            cryptoInput
            receivedInput
            submitButton
          />
        | Withdraw =>
          <WithdrawForm
            kindInput
            cashInput
            cryptoInput
            spendInput
            submitButton
          />
        | Exchange =>
          <ExchangeForm
            kindInput
            fromInput
            receivedInput
            spendInput
            toInput
            submitButton
          />
        }
      )
    </div>
  }
};

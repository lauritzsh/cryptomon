open Helpers;

let format symbol amount => sup symbol ^ " " ^ sf amount |> se;

let actions = <td> <button> (se "x") </button> </td>;

module BuyRow = {
  open Currency;
  let component = ReasonReact.statelessComponent "BuyRow";
  let make cash::(cash: cash) ::spend ::crypto ::received ::timestamp _children => {
    ...component,
    render: fun _self =>
      <tr>
        <td> (se "B") </td>
        <td> (format cash.id spend) </td>
        <td> (format crypto.id received) </td>
        <td> (st timestamp |> se) </td>
        actions
      </tr>
  };
};

module SellRow = {
  open Currency;
  let component = ReasonReact.statelessComponent "SellRow";
  let make ::crypto ::spend cash::(cash: cash) ::received ::timestamp _children => {
    ...component,
    render: fun _self =>
      <tr>
        <td> (se "S") </td>
        <td> (format cash.id spend) </td>
        <td> (format crypto.id received) </td>
        <td> (st timestamp |> se) </td>
        actions
      </tr>
  };
};

module DepositRow = {
  open Currency;
  let component = ReasonReact.statelessComponent "DepositRow";
  let make ::currency ::received ::timestamp _children => {
    ...component,
    render: fun _self => {
      let td =
        switch currency {
        | Cash {id} => format id received
        | Crypto {id} => format id received
        };
      <tr>
        <td> (se "D") </td>
        <td />
        <td> td </td>
        <td> (st timestamp |> se) </td>
        actions
      </tr>
    }
  };
};

module WithdrawRow = {
  open Currency;
  let component = ReasonReact.statelessComponent "WithdrawRow";
  let make ::currency ::received ::timestamp _children => {
    ...component,
    render: fun _self => {
      let td =
        switch currency {
        | Cash {id} => format id received
        | Crypto {id} => format id received
        };
      <tr>
        <td> (se "W") </td>
        <td> td </td>
        <td />
        <td> (st timestamp |> se) </td>
        actions
      </tr>
    }
  };
};

module ExchangeRow = {
  open Currency;
  let component = ReasonReact.statelessComponent "ExchangeRow";
  let make ::from ::spend ::to' ::received ::timestamp _children => {
    ...component,
    render: fun _self =>
      <tr>
        <td> (se "E") </td>
        <td> (format from.id spend) </td>
        <td> (format to'.id received) </td>
        <td> (st timestamp |> se) </td>
        actions
      </tr>
  };
};

let component = ReasonReact.statelessComponent "TransactionRow";

let make transaction::(txn: Transaction.transaction) _children => {
  ...component,
  render: fun _self => {
    let timestamp = txn.timestamp;
    switch txn.kind {
    | Buy cash spend crypto received =>
      <BuyRow cash spend crypto received timestamp />
    | Sell crypto spend cash received =>
      <SellRow crypto spend cash received timestamp />
    | Deposit currency received => <DepositRow currency received timestamp />
    | Withdraw currency received => <WithdrawRow currency received timestamp />
    | Exchange from spend to' received =>
      <ExchangeRow from spend to' received timestamp />
    }
  }
};

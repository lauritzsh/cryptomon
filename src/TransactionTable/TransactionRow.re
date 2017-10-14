open Helpers;

exception UnknownTransaction;

let format symbol amount => sup symbol ^ " " ^ sf amount |> se;

module BuyRow = {
  open Currency;
  open Transaction;
  let component = ReasonReact.statelessComponent "BuyRow";
  let make ::transaction ::onDelete _children => {
    ...component,
    render: fun _self =>
      switch transaction.kind {
      | Buy cash spend crypto received =>
        <tr>
          <td> (se "B") </td>
          <td> (format cash.id spend) </td>
          <td> (format crypto.id received) </td>
          <td> (st transaction.timestamp |> se) </td>
          <td> <button onClick=onDelete> (se "x") </button> </td>
        </tr>
      | _ => raise UnknownTransaction
      }
  };
};

module SellRow = {
  open Currency;
  open Transaction;
  let component = ReasonReact.statelessComponent "SellRow";
  let make ::transaction ::onDelete _children => {
    ...component,
    render: fun _self =>
      switch transaction.kind {
      | Sell crypto spend cash received =>
        <tr>
          <td> (se "S") </td>
          <td> (format crypto.id spend) </td>
          <td> (format cash.id received) </td>
          <td> (st transaction.timestamp |> se) </td>
          <td> <button onClick=onDelete> (se "x") </button> </td>
        </tr>
      | _ => raise UnknownTransaction
      }
  };
};

module DepositRow = {
  open Currency;
  open Transaction;
  let component = ReasonReact.statelessComponent "DepositRow";
  let make ::transaction ::onDelete _children => {
    ...component,
    render: fun _self =>
      switch transaction.kind {
      | Deposit currency received =>
        let td =
          switch currency {
          | Cash {id} => format id received
          | Crypto {id} => format id received
          };
        <tr>
          <td> (se "D") </td>
          <td />
          <td> td </td>
          <td> (st transaction.timestamp |> se) </td>
          <td> <button onClick=onDelete> (se "x") </button> </td>
        </tr>
      | _ => raise UnknownTransaction
      }
  };
};

module WithdrawRow = {
  open Currency;
  open Transaction;
  let component = ReasonReact.statelessComponent "WithdrawRow";
  let make ::transaction ::onDelete _children => {
    ...component,
    render: fun _self =>
      switch transaction.kind {
      | Withdraw currency spend =>
        let td =
          switch currency {
          | Cash {id} => format id spend
          | Crypto {id} => format id spend
          };
        <tr>
          <td> (se "W") </td>
          <td> td </td>
          <td />
          <td> (st transaction.timestamp |> se) </td>
          <td> <button onClick=onDelete> (se "x") </button> </td>
        </tr>
      | _ => raise UnknownTransaction
      }
  };
};

module ExchangeRow = {
  open Currency;
  open Transaction;
  let component = ReasonReact.statelessComponent "ExchangeRow";
  let make ::transaction ::onDelete _children => {
    ...component,
    render: fun _self =>
      switch transaction.kind {
      | Exchange from spend to' received =>
        <tr>
          <td> (se "E") </td>
          <td> (format from.id spend) </td>
          <td> (format to'.id received) </td>
          <td> (st transaction.timestamp |> se) </td>
          <td> <button onClick=onDelete> (se "x") </button> </td>
        </tr>
      | _ => raise UnknownTransaction
      }
  };
};

let component = ReasonReact.statelessComponent "TransactionRow";

let make transaction::(txn: Transaction.transaction) ::onDelete _children => {
  ...component,
  render: fun _self =>
    switch txn.kind {
    | Buy _ => <BuyRow transaction=txn onDelete />
    | Sell _ => <SellRow transaction=txn onDelete />
    | Deposit _ => <DepositRow transaction=txn onDelete />
    | Withdraw _ => <WithdrawRow transaction=txn onDelete />
    | Exchange _ => <ExchangeRow transaction=txn onDelete />
    }
};

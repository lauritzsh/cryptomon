open Helpers;

loadCSS "./TransactionRow.css";

exception UnknownTransaction;

let format symbol amount => symbol ^ " " ^ sf amount |> se;

let kind letter => <td> <div className="kind"> (se letter) </div> </td>;

module BuyRow = {
  open Currency;
  open Transaction;
  let component = ReasonReact.statelessComponent "BuyRow";
  let make ::transaction _children => {
    ...component,
    render: fun _self =>
      switch transaction.kind {
      | Buy cash spend crypto received =>
        <Aux>
          (kind "B")
          <td> (format cash.id spend) </td>
          <td> (format crypto.symbol received) </td>
          <td> (st transaction.timestamp |> se) </td>
        </Aux>
      | _ => raise UnknownTransaction
      }
  };
};

module SellRow = {
  open Currency;
  open Transaction;
  let component = ReasonReact.statelessComponent "SellRow";
  let make ::transaction _children => {
    ...component,
    render: fun _self =>
      switch transaction.kind {
      | Sell crypto spend cash received =>
        <Aux>
          (kind "S")
          <td> (format crypto.symbol spend) </td>
          <td> (format cash.id received) </td>
          <td> (st transaction.timestamp |> se) </td>
        </Aux>
      | _ => raise UnknownTransaction
      }
  };
};

module DepositRow = {
  open Currency;
  open Transaction;
  let component = ReasonReact.statelessComponent "DepositRow";
  let make ::transaction _children => {
    ...component,
    render: fun _self =>
      switch transaction.kind {
      | Deposit currency received =>
        let td =
          switch currency {
          | Cash {id} => format id received
          | Crypto {id} => format id received
          };
        <Aux>
          (kind "D")
          <td />
          <td> td </td>
          <td> (st transaction.timestamp |> se) </td>
        </Aux>
      | _ => raise UnknownTransaction
      }
  };
};

module WithdrawRow = {
  open Currency;
  open Transaction;
  let component = ReasonReact.statelessComponent "WithdrawRow";
  let make ::transaction _children => {
    ...component,
    render: fun _self =>
      switch transaction.kind {
      | Withdraw currency spend =>
        let td =
          switch currency {
          | Cash {id} => format id spend
          | Crypto {id} => format id spend
          };
        <Aux>
          (kind "W")
          <td> td </td>
          <td />
          <td> (st transaction.timestamp |> se) </td>
        </Aux>
      | _ => raise UnknownTransaction
      }
  };
};

module ExchangeRow = {
  open Currency;
  open Transaction;
  let component = ReasonReact.statelessComponent "ExchangeRow";
  let make ::transaction _children => {
    ...component,
    render: fun _self =>
      switch transaction.kind {
      | Exchange from spend to' received =>
        <Aux>
          (kind "E")
          <td> (format from.symbol spend) </td>
          <td> (format to'.symbol received) </td>
          <td> (st transaction.timestamp |> se) </td>
        </Aux>
      | _ => raise UnknownTransaction
      }
  };
};

let component = ReasonReact.statelessComponent "TransactionRow";

let make transaction::(txn: Transaction.transaction) ::onDelete _children => {
  ...component,
  render: fun _self =>
    <tr>
      (
        switch txn.kind {
        | Buy _ => <BuyRow transaction=txn />
        | Sell _ => <SellRow transaction=txn />
        | Deposit _ => <DepositRow transaction=txn />
        | Withdraw _ => <WithdrawRow transaction=txn />
        | Exchange _ => <ExchangeRow transaction=txn />
        }
      )
      <td>
        <Inputs.ActionButton
          image=(loadResource "./remove.png")
          onClick=onDelete
        />
      </td>
    </tr>
};

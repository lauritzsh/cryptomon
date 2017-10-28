open Helpers;

loadCSS("./TransactionRow.css");

let format = (amount, symbol) => symbol ++ (" " ++ sf(amount)) |> se;

let kind = (letter) => <td> <div className="kind"> (se(letter)) </div> </td>;

let component = ReasonReact.statelessComponent("TransactionRow");

let make = (~transaction, ~cashes, ~cryptos, ~onDelete, _children) => {
  ...component,
  render: (_self) => {
    open Currency;
    let code = (id) => (List.assoc(id, cashes): Cash.t).code;
    let symbol = (id) => (List.assoc(id, cryptos): Crypto.t).symbol;
    let name = (id) => (List.assoc(id, cryptos): Crypto.t).name;
    <tr>
      (
        switch (transaction: Transaction.t).kind {
        | Buy(cash_id, spend, crypto_id, received) =>
          <Aux>
            (kind("B"))
            <td> (code(cash_id) |> format(spend)) </td>
            <td title=(name(crypto_id))> (symbol(crypto_id) |> format(received)) </td>
          </Aux>
        | Sell(crypto_id, spend, cash_id, received) =>
          <Aux>
            (kind("S"))
            <td title=(name(crypto_id))> (symbol(crypto_id) |> format(spend)) </td>
            <td> (code(cash_id) |> format(received)) </td>
          </Aux>
        | Deposit(currency, received) =>
          <Aux>
            (kind("D"))
            <td />
            (
              switch currency {
              | Cash(id) => <td> (code(id) |> format(received)) </td>
              | Crypto(id) => <td title=(name(id))> (symbol(id) |> format(received)) </td>
              }
            )
          </Aux>
        | Withdraw(currency, spend) =>
          <Aux>
            (kind("W"))
            (
              switch currency {
              | Cash(id) => <td> (code(id) |> format(spend)) </td>
              | Crypto(id) => <td title=(name(id))> (symbol(id) |> format(spend)) </td>
              }
            )
            <td />
          </Aux>
        | Exchange(from_id, spend, to_id, received) =>
          <Aux>
            (kind("E"))
            <td title=(name(from_id))> (symbol(from_id) |> format(spend)) </td>
            <td title=(name(to_id))> (symbol(to_id) |> format(received)) </td>
          </Aux>
        }
      )
      <td className="timestamp"> (st(transaction.timestamp) |> se) </td>
      <td className="actions">
        <Inputs.ActionButton squared=true image=(loadResource("./remove.svg")) onClick=onDelete />
      </td>
    </tr>
  }
};

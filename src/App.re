open Helpers;

type state = {
  transactions: list Transaction.transaction,
  cashes: StringMap.t Currency.cash,
  cryptos: StringMap.t Currency.crypto
};

let component = ReasonReact.statelessComponent "App";

let make _children => {
  ...component,
  render: fun _self => <h2> (se "Hello, World") </h2>
};

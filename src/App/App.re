open Helpers;

loadCSS "./App.css";

type state = {
  transactions: list Transaction.transaction,
  cashes: StringMap.t Currency.cash,
  cryptos: StringMap.t Currency.crypto
};

let component = ReasonReact.statelessComponent "App";

let make _children => {
  ...component,
  render: fun _self =>
    <div className="app"> <h2> (se "Hello, World") </h2> </div>
};

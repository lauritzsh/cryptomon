open Helpers;

loadCSS("./Tutorial.css");

let component = ReasonReact.statelessComponent("Portfolio");

let make = (~cryptos, ~cashes, ~onSampleClick, ~onSubmit, _children) => {
  ...component,
  render: (_self) =>
    <Aux>
      <div className="tutorial">
        <h1 className="title"> (se("Cryptocurrency Portfolio Monitor")) </h1>
        <p className="intro">
          (
            se(
              "Cryptomon is a simple tool that helps you keep track of cryptocurrencies and their values. "
            )
          )
        </p>
        <p className="getting-started">
          (se("Get started by adding a transaction below or click "))
          <a href="#" onClick=onSampleClick> (se("here")) </a>
          (se(" to get sample data."))
        </p>
      </div>
      <TransactionForm cryptos cashes onSubmit />
    </Aux>
};

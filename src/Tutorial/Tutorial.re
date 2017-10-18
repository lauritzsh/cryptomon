open Helpers;

loadCSS "./Tutorial.css";

let component = ReasonReact.statelessComponent "Portfolio";

let make ::cryptos ::cashes ::onSubmit _children => {
  ...component,
  render: fun _self =>
    <Aux>
      <div className="tutorial">
        <h1 className="title"> (se "Cryptocurrency Portfolio Monitor") </h1>
        <p className="intro">
          (
            se "Cryptomon is a simple tool that helps you keep track of cryptocurrencies and their values. "
          )
          (se "Get started by adding a transaction below.")
        </p>
      </div>
      <TransactionForm cryptos cashes onSubmit />
    </Aux>
};

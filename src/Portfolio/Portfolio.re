open Helpers;

loadCSS "./Portfolio.css";

type item = {
  name: string,
  amount: float,
  value: float
};

let component = ReasonReact.statelessComponent "Portfolio";

module PortfolioItem = {
  let component = ReasonReact.statelessComponent "PortfolioItem";
  let make ::item _children => {
    ...component,
    render: fun _self =>
      <div className="portfolio-item">
        <h2> (se item.name) </h2>
        <h3> ("$" ^ sf item.value |> se) </h3>
        <h3> (sf item.amount |> se) </h3>
      </div>
  };
};

let make ::cryptos ::transactions _children => {
  ...component,
  render: fun _self => {
    open StringMap;
    let addOrUpdate f key default m =>
      add key (f (mem key m ? find key m : default)) m;
    let deposit symbol amount => addOrUpdate (fun v => v +. amount) symbol 0.;
    let withdraw symbol amount => addOrUpdate (fun v => v -. amount) symbol 0.;
    let transfer fromSymbol spend toSymbol received p =>
      p
      |> addOrUpdate (fun v => v -. spend) fromSymbol 0.
      |> addOrUpdate (fun v => v +. received) toSymbol 0.;
    let updatePortfolio ({kind}: Transaction.transaction) p =>
      switch kind {
      | Buy _cash _spend crypto received => deposit crypto.id received p
      | Sell crypto spend _cash _received => withdraw crypto.id spend p
      | Deposit (Crypto crypto) received => deposit crypto.id received p
      | Deposit (Cash _cash) _received => p
      | Withdraw (Crypto crypto) spend => withdraw crypto.id spend p
      | Withdraw (Cash _cash) _spend => p
      | Exchange from spend to' received =>
        transfer from.id spend to'.id received p
      };
    let portfolio = List.fold_right updatePortfolio transactions empty;
    let item (key, amount) => {
      let crypto: Currency.crypto = List.assoc key cryptos;
      let item = {name: crypto.name, amount, value: amount *. crypto.usd_rate};
      <PortfolioItem key item />
    };
    let items = List.map item (bindings portfolio);
    <div className="portfolio"> (le items) </div>
  }
};

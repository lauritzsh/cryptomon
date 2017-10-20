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
  let make ::item ::change _children => {
    ...component,
    render: fun _self =>
      <div className="portfolio-item">
        <div className="top">
          <div className="name"> (se item.name) </div>
          (
            inf == fs change ?
              ReasonReact.nullElement :
              fs change >= 0.0 ?
                <div className="up"> ("% +" ^ change |> se) </div> :
                <div className="down"> ("% " ^ change |> se) </div>
          )
        </div>
        <h3 className="value">
          ("$" ^ fixed item.value 2 ^ " (" ^ sf item.amount ^ ")" |> se)
        </h3>
      </div>
  };
};

let make ::cryptos ::transactions _children => {
  ...component,
  render: fun _self => {
    open StringMap;
    let addOrUpdate f key default m =>
      add key (f (mem key m ? find key m : default)) m;
    let updatePortfolio ({kind}: Transaction.transaction) p =>
      switch kind {
      | Buy cash spend crypto received =>
        addOrUpdate
          (fun (v, s) => (v +. received, spend *. cash.usd_rate +. s))
          crypto.id
          (0.0, 0.0)
          p
      | Sell crypto spend cash received =>
        addOrUpdate
          (fun (v, s) => (v -. spend, received *. cash.usd_rate +. s))
          crypto.id
          (0.0, 0.0)
          p
      | Deposit (Crypto crypto) received =>
        addOrUpdate (fun (v, s) => (v +. received, s)) crypto.id (0.0, 0.0) p
      | Deposit (Cash _cash) _received => p
      | Withdraw (Crypto crypto) spend =>
        addOrUpdate (fun (v, s) => (v -. spend, s)) crypto.id (0.0, 0.0) p
      | Withdraw (Cash _cash) _spend => p
      | Exchange from spend _to received =>
        p
        |> addOrUpdate (fun (v, s) => (v -. spend, s)) from.id (0.0, 0.0)
        |> addOrUpdate (fun (v, s) => (v +. received, s)) _to.id (0.0, 0.0)
      };
    let portfolio = List.fold_right updatePortfolio transactions empty;
    let item (key, (amount, spend)) => {
      let crypto: Currency.crypto = List.assoc key cryptos;
      let item = {name: crypto.name, amount, value: amount *. crypto.usd_rate};
      let change = fixed ((item.value -. spend) /. spend *. 100.) 2;
      <PortfolioItem key item change />
    };
    let items = List.map item (bindings portfolio);
    <div className="portfolio"> (le items) </div>
  }
};

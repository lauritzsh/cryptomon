open Helpers;

loadCSS("./Portfolio.css");

type item = {
  name: string,
  amount: float,
  value: float
};

let component = ReasonReact.statelessComponent("Portfolio");

module PortfolioItem = {
  let component = ReasonReact.statelessComponent("PortfolioItem");
  let make = (~item, _children) => {
    ...component,
    render: (_self) =>
      <div className="portfolio-item">
        <div className="top"> <div className="name"> (se(item.name)) </div> </div>
        <h3 className="value">
          ("$" ++ (fixed(item.value, 2) ++ (" (" ++ (sf(item.amount) ++ ")"))) |> se)
        </h3>
      </div>
  };
};

let make = (~cryptos, ~cashes, ~transactions, _children) => {
  ...component,
  render: (_self) => {
    open Currency;
    open StringMap;
    let la = List.assoc;
    let addOrUpdate = (f, key, default, m) => add(key, f(mem(key, m) ? find(key, m) : default), m);
    let updatePortfolio = ({kind}: Transaction.t, p) =>
      switch kind {
      | Buy(cash_id, spend, crypto_id, received) =>
        addOrUpdate(
          Cash.(((v, s)) => (v +. received, spend *. la(cash_id, cashes).usd_rate +. s)),
          crypto_id,
          (0.0, 0.0),
          p
        )
      | Sell(crypto_id, spend, cash_id, received) =>
        addOrUpdate(
          Cash.(((v, s)) => (v -. spend, received *. la(cash_id, cashes).usd_rate +. s)),
          crypto_id,
          (0.0, 0.0),
          p
        )
      | Deposit(Crypto(crypto_id), received) =>
        addOrUpdate(((v, s)) => (v +. received, s), crypto_id, (0.0, 0.0), p)
      | Deposit(Cash(_cash), _received) => p
      | Withdraw(Crypto(crypto_id), spend) =>
        addOrUpdate(((v, s)) => (v -. spend, s), crypto_id, (0.0, 0.0), p)
      | Withdraw(Cash(_cash), _spend) => p
      | Exchange(from_id, spend, to_id, received) =>
        p
        |> addOrUpdate(((v, s)) => (v -. spend, s), from_id, (0.0, 0.0))
        |> addOrUpdate(((v, s)) => (v +. received, s), to_id, (0.0, 0.0))
      };
    let portfolio = List.fold_right(updatePortfolio, transactions, empty);
    let item = ((key, (amount, _))) => {
      let crypto: Crypto.t = la(key, cryptos);
      let item = {name: crypto.name, amount, value: amount *. crypto.usd_rate};
      <PortfolioItem key item />
    };
    let items = List.map(item, bindings(portfolio));
    <div className="portfolio"> (le(items)) </div>
  }
};

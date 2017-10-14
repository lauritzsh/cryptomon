/* dollar, euro etc. */
type cash = {
  id: string, /* usd, eur etc. */
  usd_rate: float
};

/* BTC, ETH etc. */
type crypto = {
  id: string, /* btc, eth etc. */
  name: string, /* Bitcoin, Ethereum etc. */
  usd_rate: float,
  btc_rate: float
};

type currency =
  | Cash cash
  | Crypto crypto;

/* Sample data for development */
module Data = {
  let usd = {id: "usd", usd_rate: 1.0};
  let cashes = [(usd.id, usd)];
  let btc = {id: "btc", name: "Bitcoin", usd_rate: 5709.4, btc_rate: 1.0};
  let ltc = {id: "ltc", name: "Litecoin", usd_rate: 60.75, btc_rate: 0.010626};
  let neo = {id: "neo", name: "NEO", usd_rate: 28.88, btc_rate: 0.00503792};
  let cryptos = [(btc.id, btc), (ltc.id, ltc), (neo.id, neo)];
};

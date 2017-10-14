/* USD, EUR etc. */
type cash = {
  id: string,
  name: string,
  usd_rate: float
};

/* BTC, ETH etc. */
type crypto = {
  id: string,
  name: string,
  usd_rate: float,
  btc_rate: float
};

type currency =
  | Cash cash
  | Crypto crypto;

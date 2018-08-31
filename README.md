# Cryptomon

> Cryptocurrency Portfolio Monitor

A simple portfolio monitor for all your cryptocurrencies that works offline.

It is built using [Reason](https://reasonml.github.io/) with
[ReasonReact](https://github.com/reasonml/reason-react). I made it because I
wanted something simple that allowed me to quickly check up on my portfolio. It
is still a WIP so minor bugs can be expected but please report any
[here](https://github.com/lauritzsh/cryptomon/issues) thanks.

The crypto data is downloaded from [CoinMarketCap](https://coinmarketcap.com/)
and cash data is downloaded from [Exchange Rates API](https://exchangeratesapi.io/).

## How to run

Install [reason-cli](https://github.com/reasonml/reason-cli) (this project runs
3). Then install dependencies with `yarn` or `npm i`.

To run a local development server do `yarn start`. A production build can be
made with `yarn build`.

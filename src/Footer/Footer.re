open Helpers;

loadCSS("./Footer.css");

let component = ReasonReact.statelessComponent("Footer");

let middot = {j|\u00B7|j};

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="footer">
      (se({j|Cryptomon $middot Made by |j}))
      <a className="home" href="http://lauritz.me"> (se("Lauritz")) </a>
      (se({j| $middot |j}))
      <a className="github" href="https://github.com/lauritzsh/cryptomon"> (se("GitHub")) </a>
    </div>
};

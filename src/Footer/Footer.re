open Helpers;

loadCSS("./Footer.css");

let component = ReasonReact.statelessComponent("Footer");

let middot = {j|\u00B7|j};

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="footer">
      <div className="inner">
        <div className="info">
          <div className="code">
            <a className="github" href="https://github.com/lauritzsh/cryptomon">
              (se("GitHub"))
            </a>
          </div>
          <div className="made-by">
            (se({j|by |j}))
            <a className="home" href="http://lauritz.me"> (se("Lauritz")) </a>
          </div>
        </div>
        <div className="addresses">
          <div className="bitcoin"> (se("1K2Adv2oEV1UFP8imoPHu2xRTFpc9dLpH3")) </div>
          <div className="ethereum"> (se("0x133069296574ae32dD703AE11FfEe8924DcF349D")) </div>
        </div>
      </div>
    </div>
};

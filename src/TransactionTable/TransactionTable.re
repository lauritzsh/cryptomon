open Helpers;

loadCSS "./TransactionTable.css";

let component = ReasonReact.statelessComponent "TransactionTable";

let make ::cashes ::cryptos ::onDelete ::transactions _children => {
  ...component,
  render: fun _self => {
    let tr i transaction =>
      <TransactionRow
        cashes
        cryptos
        key=(si i)
        onDelete=(onDelete transaction)
        transaction
      />;
    let tbody = List.mapi tr transactions;
    <div className="transaction-table">
      <table>
        <thead>
          <tr>
            <th className="kind" />
            <th> (se "Spend") </th>
            <th> (se "Received") </th>
            <th> (se "When") </th>
            <th />
            <th />
          </tr>
        </thead>
        <tbody> (le tbody) </tbody>
      </table>
    </div>
  }
};

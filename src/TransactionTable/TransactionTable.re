open Helpers;

loadCSS "./TransactionTable.css";

let component = ReasonReact.statelessComponent "TransactionTable";

let make ::transactions _children => {
  ...component,
  render: fun _self => {
    let tbody =
      List.mapi
        (fun i transaction => <TransactionRow key=(si i) transaction />)
        transactions;
    <div className="transaction-table">
      <table>
        <thead>
          <tr>
            <th />
            <th> (se "Spend") </th>
            <th> (se "Received") </th>
            <th> (se "Timestamp") </th>
            <th />
          </tr>
        </thead>
        <tbody> (le tbody) </tbody>
      </table>
    </div>
  }
};

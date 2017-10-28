[@bs.module "./fetch"] external fetch' : unit => Js.Promise.t(Js.Json.t) = "fetch";

let fetch = (onReceive) =>
  Currency.Cash.(
    Js.Promise.(
      fetch'()
      |> then_((json) => (Json.Decode.list(decode))(json) |> resolve)
      |> then_((cashes) => onReceive(cashes) |> resolve)
      |> ignore
    )
  );

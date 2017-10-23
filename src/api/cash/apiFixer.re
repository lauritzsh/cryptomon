external fetch' : unit => Js.Promise.t Js.Json.t =
  "fetch" [@@bs.module "./fetch"];

let fetch onReceive =>
  Currency.Cash.(
    Js.Promise.(
      fetch' ()
      |> then_ (fun json => (Json.Decode.list decode) json |> resolve)
      |> then_ (fun cashes => onReceive cashes |> resolve)
      |> ignore
    )
  );

let getPrice = (price:float) => {
    price |> Js.Float.toFixed(~digits=2) |> React.string;
};
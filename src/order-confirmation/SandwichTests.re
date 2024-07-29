open Fest;

test("Item.Sandwich.toEmoji", () =>
    expect
    |> deepEqual(
        [|Ham, Cheesy, Spicy, Hawai|]
        |> Js.Array.map(~f=Item.Sandwich.toEmoji),
        [|
            {js|🥪 ( 🐷 )|js},
            {js|🥪 ( 🧀 )|js},
            {js|🥪 ( 🌶️ )|js},
            {js|🥪 ( 🍍 )|js},
        |],
    )
    //|> equal(Item.Sandwich.toEmoji(Ham), {js|🥪 ( 🐷 )|js})
);


test("Item.Sandwich.toPrice", () => {
  // 22 Jul 2024 is a Monday

  let f = {
    Item.Sandwich.toPrice(~date=Js.Date.makeWithYMD(~year=2024., ~month=6., ~date=22.))
  }

  expect
  |> deepEqual(
       [|Ham, Cheesy, Spicy, Hawai|]
       |> Js.Array.map(~f),   // It will take let f as a input. It will pass array of sanwiches to ~f, generate day of week and return price
       [|4., 4.8, 4.5, 2.5|], /* expected prices */
     );
});
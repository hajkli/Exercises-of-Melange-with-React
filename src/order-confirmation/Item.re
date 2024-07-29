module Burger = {
    type t = {
        hasLettuce: bool,
        hasBacon: bool,
        onions: int,
        cheese: int,
    };

    let toEmoji = (burger:t) : string => {
        let {hasLettuce, hasBacon, onions, cheese} = burger;   // this will destruct burger to separated variables so we do not have to write burger. again and again. We can do it also like this:  let getBurgerEmoji = ({hasLettuce, hasBacon, onions, cheese}) => {...}.
        let multiple = (emoji, count) => {
            Printf.sprintf({js|%sx%d|js}, emoji, count);
        }
        Printf.sprintf(
            {js|🍔{%s}|js},
            [|
                hasLettuce ? {js|🥬|js} : "",
                hasBacon ? {js|🥓|js} : "",
                onions > 0 ? multiple({js|🧅|js},onions) : "",
                cheese > 0 ? multiple({js|🧀|js},cheese) : "",
            |]
            |> Js.Array.filter(~f=str => str != "")
            |> Js.Array.join(~sep=", "),
        );
    } ;

    let toppingCost = (amount: int, price: float) : float =>{
        float_of_int(amount) *. price 
    }

    let toPrice = ({hasLettuce: _, hasBacon, onions, cheese}) :float => {
        15. // base cost of burger
        +. float_of_int(onions) *. 0.2
        +. float_of_int(cheese) *. 0.3
        +.
        switch(hasBacon) {
            | true => 1.
            | false => 0.
        };
    }
}

module Sandwich = {
    type t =
        | Ham
        | Cheesy
        | Spicy
        | Hawai;

    let toPrice = (~date: Js.Date.t, t) => {
        let day = date |> Js.Date.getDay |> int_of_float; // 0 => Sunday ...

        switch(t) {
            | Ham => 4.
            | Cheesy => 4.8
            | Spicy => 4.5
            | Hawai when day == 1 => 2.5
            | Hawai => 5.;
        }
    };

    let toEmoji = (t) => {
        Printf.sprintf(
            {j|🥪 (%s)|j},
            switch(t) {
                | Ham => {js| 🐷 |js}
                | Cheesy => {js| 🧀 |js}
                | Spicy => {js| 🌶️ |js};
                | Hawai => {js| 🍍 |js};
            }
        )
    };
}

type t =
    | Sandwich(Sandwich.t)
    | Burger(Burger.t)
    | Pizza;

let toPrice = t =>
    switch (t) {
    | Sandwich(sandwich) => Sandwich.toPrice(~date=Js.Date.make(), sandwich)
    | Burger(burger) => Burger.toPrice(burger)
    | Pizza => 17.5
};

let toEmoji = t =>
    switch (t) {
    | Pizza => {js|🍕|js};
    | Sandwich(sandwich) => Sandwich.toEmoji(sandwich)
    | Burger(burger) => Burger.toEmoji(burger);
};





/*
* Example of using multiple types in Printf.sprintf
*
// Rewrite using Printf.sprintf 
let player: Js.t({..}) = {
  "name": "Wilbur",
  "level": 9001234,
  "immortal": false,
};
Js.log(
  Printf.sprintf(
    "Player: name=%s, level=%#d, immortal=%B",
    player##name,
    player##level,
    player##immortal,
  ),
);
*/
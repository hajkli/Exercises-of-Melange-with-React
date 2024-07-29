/**  1 burgers + 1 for free    */
let getFreeBurgers = (items: list(Item.t)) => {
  let prices =
    items
    |> List.filter_map(item => {
         switch (item) {
         | Item.Burger(burger) => Some(Item.Burger.toPrice(burger))
         | Sandwich(_)
         | Pizza => None
         }
       });

  switch (prices) {
  | [] => Error(`NeedTwoBurgers)
  | [_] => Error(`NeedOneBurger)
  | prices =>
    let result =
      prices
      |> List.sort((x, y) => - Float.compare(x, y))
      |> List.filteri((index, _) => index mod 2 == 1)
      |> List.fold_left((+.), 0.0);
    Ok(result);
  };
};

/*   Array version
     let getFreeBurger = (items: array(Item.t)) =>{
         let prices =
         items
         |> Js.Array.filter(~f=item =>
             switch (item) {
             | Item.Burger(_) => true
             | Item.Sandwich(_)
             | Item.Pizza => false
             }
         )
         |> Js.Array.map(~f=Item.toPrice)

         |> Js.Array.sortInPlaceWith(~f=(item1, item2) =>{
             - compare(Item.toPrice(item1), Item.toPrice(item2))
         })

         prices[1] //  prices[1] would call Array.get from Stdlib.Array.get. But instead of that it will call Array.get from my module Array.re which will overwrite default method.
         /*
         switch (prices[1]) {   //  prices[1] would call Array.get from Stdlib.Array.get. But instead of that it will call Array.get from my module Array.re which will overwrite default method.
         | None => None
         | Some(cheaperPrice) => Some(cheaperPrice)
         };
         */
     }
     */

// Buy 1+ burger with 1+ of every topping, get half off
let getHalfOff = (items: list(Item.t)) => {
  let meetsCondition =
    items
    |> List.exists(item => {
         switch (item) {
         | Item.Burger({hasLettuce: true, hasBacon: true, onions, cheese})
             when onions > 0 && cheese > 0 =>
           true
         | Burger(_)
         | Sandwich(_)
         | Pizza => false
         }
       });

  switch (meetsCondition) {
  | false => Error(`NeedMegaBurger)
  | true =>
    let total =
      items
      |> List.fold_left((total, item) => total +. Item.toPrice(item), 0.0);
    Ok(total /. 2.0);
  };
};

/* Array version
   let getHalfOff = (items: array(Item.t)) => {
     let meetsCondition =
       items
       |> Js.Array.some(~f=item =>   // It will check if at least one member of array "items" return true

            switch (item) {
            | Item.Burger({
               hasLettuce: true,
               hasBacon: true,
               onions,
               cheese,
              })
              when onions > 0 && cheese > 0  => true
            | Burger(_)
            | Sandwich(_)
            | Pizza => false
            }
          );

     switch (meetsCondition) {
     | false => None
     | true =>
       let total =
         items
         |> Js.Array.reduce(~init=0.0, ~f=(total, item) =>
              total +. Item.toPrice(item)
            );
       Some(total /. 2.0);
     };
   };
   */

type sandwichTracker = {
  ham: bool,
  cheesy: bool,
  spicy: bool,
  hawai: bool,
};

/** Buy 1+ of every type of sandwich, get 50% discount */
let getSandwichHalfOff = (items: list(Item.t)) => {
  let tracker: sandwichTracker =
    items
    |> List.filter_map(item => {
         switch (item) {
         | Item.Sandwich(sandwich) => Some(sandwich)
         | Burger(_)
         | Pizza => None
         }
       })
    |> ListLabels.fold_left(
         ~init={ham: false, cheesy: false, spicy: false, hawai: false},
         ~f=(tracker, sandwich: Item.Sandwich.t) =>
         switch (sandwich) {
         | Ham => {...tracker, ham: true}
         | Cheesy => {...tracker, cheesy: true}
         | Spicy => {...tracker, spicy: true}
         | Hawai => {...tracker, hawai: true}
         }
       );

  switch (tracker) {
  | {ham: true, cheesy: true, spicy: true, hawai: true} =>
    let total =
      items
      |> ListLabels.fold_left(~init=0.0, ~f=(total, item) =>
           total +. Item.toPrice(item)
         );
    Ok(total /. 2.0);
  | _ => Error(`MissingSandwichTypes)
  };
};

type error =
  | ExpiredCode
  | InvalidCode;

let getDiscountFunction = (code, date) => {
  let month = date |> Js.Date.getMonth;

  switch (code |> Js.String.toUpperCase) {
  | "FREE" when month == 4.0 => Ok(getFreeBurgers) //we use Ok/Error:Result instead of Some/None:Option bcs option None would not take any argument. With Result Error we can pass specific feedback to user.
  | "FREE" => Error(ExpiredCode)
  | "HALF" => Ok(getHalfOff)
  | _ => Error(InvalidCode)
  };
};

[@mel.module "./order.module.css"] external orderCss: Js.t({..}) = "default"; 
type t = list(Item.t);

/*  
*
*   Random number generation example 
*
Random.self_init();
let getRandomNumber = () => {
  let min = 100;
  let max = 300;
  Random.int(max - min + 1) + min;
};
*/

module OrderItem = {
    [@mel.module "./order-item.module.css"] external orderItemCss: Js.t({..}) = "default"; 

    [@react.component]
    let make = (~item:Item.t)=>{
        <tr className={orderItemCss##item}>
            <td className={orderItemCss##emoji}> {item |> Item.toEmoji |> React.string} </td>
            <td className={orderItemCss##price}>
                {item |> Item.toPrice |> Format.getPrice}
            </td>
        </tr>
    }
}


[@react.component]
let make = (~items:t) =>{
    //let total = items |> Js.Array.reduce(~init=0., ~f=(acc, order) => acc +.Item.toPrice(order));   
    let total = ListLabels.fold_left(
        ~f=(acc, order) => acc +. Item.toPrice(order),
        ~init=0.0,
        items
    );

//let itemRows: array(React.element) = items |> Js.Array.mapi(~f=(item, index)=> <OrderItem key={"item-" ++ string_of_int(index)} item />);


<table>
    <tbody>
        {items
            |> List.mapi(
                (index, item)=>{
                    <OrderItem key={"item-" ++ string_of_int(index)} item />
                }
            )
            |> Stdlib.Array.of_list   // have to change it back to array, we have to call Stdlib.Array bcs of our Array.re which overwrittes it. 
            |> React.array   // and we have to convert it to React.array type
        }
    <tr>
        <td>{React.string("Total")}</td>
        <td>{total |> Format.getPrice}</td>
    </tr>
    </tbody>
</table>;

/*
<table>
    <tbody>
        {itemRows |> React.array}
        <tr className={orderCss##total}>
            <td> {React.string("Total")}</td>
            <td> {total |> Format.getPrice} </td>
        </tr>
    </tbody>
</table>;
*/
};

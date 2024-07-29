module Styles = {
    let make = ReactDOM.Style.make;
    let root = 
        make(
            ~fontSize="16px",
            ~padding="1em",
            ~display="flex",
            ~gridGap="0.5em",
            ~alignItems="center",
            ~justifyContent="center",
            ~flexDirection="column",
        (),
    );
    let input = 
        make(
            ~borderRadius="5px",
            ~margin="0 auto",
            ~marginBottom="15px",
            ~textAlign="center",
            ~padding="9px 10px",
            (),
        )
    let inputRow = 
        make(
            ~marginBottom="15px",
            (),
        )
    let headlineH1 = 
        make(
            ~marginBottom="10px",
            ~fontSize="22px",
            ~position="relative",
            ~top="-20px",
            (),
        )
};

let convert = celsius => 9.0 /. 5.0 *. celsius +. 32.0;

let getValueFromEvent = (evt): string => React.Event.Form.target(evt)##value;

[@react.component]
let make = () =>{
    let (celsius, setCelsius) = React.useState(()=>"");

    <div style=Styles.root>
        <h1 style=Styles.headlineH1>
            {React.string("Celsius To Fahrenheit Converter")}
        </h1>
        <div>
            <input
                style=Styles.input
                value=celsius
                onChange={evt => {
                let newCelsius : string = getValueFromEvent(evt);
                setCelsius(_ => newCelsius);
                }}
            />
            {React.string({js| °C|js})}
        </div>

        {
            (
                celsius ==""
                ? {js|°F|js}
                : (
                    switch(celsius |> String.trim |> float_of_string_opt |> Option.map(convert)){
                        | None => " Input is not valid"
                        | Some(fahrenheit) when fahrenheit > 212.0 => {js|Unreasonably hot |js}
                        | Some(fahrenheit) when fahrenheit < (-128.6) => {js|Unreasonably cold|js}
                        | Some(fahrenheit) => Js.Float.toFixed(fahrenheit, ~digits=2) ++ {js|°F|js}
                    }
                )
            )
            |> React.string
        }
    </div>;
}




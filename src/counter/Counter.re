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

    let buttonContainer =
        make(
            ~display="flex",
            ~justifyContent="center",
            ~alignItems="center",
            (),
        );
    
    let button = 
        make(
            ~background="#ff8800",
            ~borderRadius="5px",
            ~color="white",
            ~padding="10px 15px",
            ~border="0",
            (),
        );

    let buttonDisabled = 
        make(
            ~background="#cccccc",
            ~borderRadius="5px",
            ~color="#888888",
            ~padding="10px 15px",
            ~border="0",
            (),
        );

    let number = 
        make(
            ~display="inline-block",
            ~margin="0 8px",
            ~textAlign="center",
            ~minWidth="80px",
            (),
        );

     let negativeMessage = 
        make(
            ~width="100%",
            ~textAlign="center",
            ~margin="0",
            ~fontSize="0.6em",
            (),
        );
    let headlineH1 = 
        make(
            ~marginBottom="10px",
            ~fontSize="22px",
            ~position="relative",
            ~top="-20px",
            (),
        )
};


let formatCounter = (counter: float) => {
  if (counter == floor(counter)) {
    Int.to_string(Float.to_int(counter))
  } else {
    Float.to_string(counter)
  }
};

let baz = 42_000_000_000L; // int64
Js.log(baz);

[@react.component]
let make = () => {
  let (counter, setCounter) = React.useState(() => 0.0);
  <div style=Styles.root>
   <h1 style=Styles.headlineH1> {React.string("Simple Counter Example")} </h1> 
    <div style=Styles.buttonContainer>

        <button 
            style={if (counter <= -3.0) { Styles.buttonDisabled } else { Styles.button }}
            disabled={counter <= -3.0}
            onClick={_evt => setCounter(v => v -. 0.5)}
        >
            {React.string("-")}
        </button>

        <span style=Styles.number>
            {React.string(formatCounter(counter))}
        </span>

        <button 
            style={if (counter >= 3.0) { Styles.buttonDisabled } else { Styles.button }}
            disabled={counter >= 3.0}
            onClick={_evt => setCounter(v => v +. 0.5)}
        >
            {React.string("+")}
        </button>
    </div>

    {counter < 0.0 ? <p style=Styles.negativeMessage> {React.string("Counter is negative!")} </p> : React.null}
    {counter > 0.0 ? <p style=Styles.negativeMessage> {React.string("Counter is positive!")} </p> : React.null}
    
  </div>;
};

module Styles = {
    let make = ReactDOM.Style.make;
    let root = 
        make(
            ~padding="1em",
            ~display="flex",
            ~gridGap="1em",
            ~alignItems="center",
            ~justifyContent="center",
            (),
        );
	let headline = 
		make(
			~fontSize="20px",
			(),
		)
};

[@react.component]
let make = ()=>{
    <div style=Styles.root>
		<h1 style=Styles.headline> {React.string("Welcome to my app!")} </h1>
	</div>
};
[@mel.module "./card.module.css"] external css: Js.t({..}) = "default"; 


module App = {

// if array type was expected us [||]
let items: Order.t = [
	Sandwich(Spicy),
	Burger({hasLettuce: true, hasBacon: true, onions: 1, cheese: 2}),
	Sandwich(Ham),
	Sandwich(Cheesy),
	Pizza,
	Sandwich(Hawai),
	Burger({hasLettuce: true, hasBacon: false, onions: 1, cheese: 0}), 
	Burger({hasLettuce: true, hasBacon: true, onions: 1, cheese: 3}) 
];



[@react.component]
let make = () =>
		<div className={css##card}>
				<h1>{React.string("Order confirmation")}</h1>
				<Order items />
		</div>;
};

let node = ReactDOM.querySelector("#root");
switch (node) {
| None =>
	Js.Console.error("Failed to start React: couldn't find the #root element")
| Some(root) =>
	let root = ReactDOM.Client.createRoot(root);
	ReactDOM.Client.render(root, <App />);
};
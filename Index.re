//[@mel.module "./order.module.css"] external orderCss: Js.t({..}) = "default"; 


module App = {
	[@react.component]
	let make = () => {

		<div>
			<Cards></Cards>
		</div>

  };
};



let node = ReactDOM.querySelector("#root");
switch (node) {
| None =>
  Js.Console.error("Failed to start React: couldn't find the #root element")
| Some(root) =>
  let root = ReactDOM.Client.createRoot(root);
  ReactDOM.Client.render(root, <App />);
};

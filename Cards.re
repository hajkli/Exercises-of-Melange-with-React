[@mel.module "./cards.module.css"] external css: Js.t({..}) = "default";

type component = {
  name: string,
  url: string,
  highlight: bool,
};

let listOfComponents = [
  {name: "Hello World", url: "/src/hello-world/index.html", highlight: false},
  {name: "Counter", url: "/src/counter/index.html", highlight: false},
  {
    name: "Celsius Conventer",
    url: "/src/celsius-converter/index.html",
    highlight: false,
  },
  {
    name: "Simple Weather App",
    url: "/src/simple-weather-app/index.html",
    highlight: false,
  },
  {
    name: "Order Confirmation",
    url: "/src/order-confirmation/index.html",
    highlight: false,
  },
  {
    name: "Better Weather App",
    url: "/src/better-weather-app/index.html",
    highlight: true,
  },
];

[@react.component]
let make = () => {
  let (visibleCards, setVisibleCards) = React.useState(() => []);

  // Effect to handle the showing of components with a delay
  React.useEffect1(
    () => {
      listOfComponents
      |> List.iteri((i, _component) => {
           let timeoutFn = () => {
             setVisibleCards(prevCard => [i, ...prevCard]);
             ();
           };
           ignore(Js.Global.setTimeout(~f=timeoutFn, i * 300));
         });
      None;
    },
    [||],
  ); // Use an empty array instead of an empty list

  <div>
    <div className="container">
      {listOfComponents
       |> List.mapi((i, component) => {
            let fadeInProcess =
              if (List.mem(i, visibleCards)) {
                css##card ++ " " ++ css##fadeIn;
              } else {
                css##card;
              };

            let highlightedClass =
              if (component.highlight) {
                css##highlited;
              } else {
                "";
              };
            let className = fadeInProcess ++ " " ++ highlightedClass;
            <a className href={component.url} key={component.name}>
              {component.highlight
                 ? <span className=css##newLabel>
                     {React.string("NEW")}
                   </span>
                 : React.null}
              {React.string(component.name)}
            </a>;
          })
       |> Array.of_list
       |> React.array}
    </div>
  </div>;
};

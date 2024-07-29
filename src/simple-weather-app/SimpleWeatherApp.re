[@mel.module "./swa.module.css"] external css: Js.t({..}) = "default";

let convert2 = (currentTemperatureAtCelsius: string) => {
  switch (currentTemperatureAtCelsius |> String.trim |> float_of_string_opt) {
  | None => 0.0
  | Some(value) => 9.0 /. 5.0 *. value +. 32.0
  };
};

let getValueFromEvent = (evt): string => React.Event.Form.target(evt)##value;

type city = {
  name: string,
  latitude: float,
  longitude: float,
};
//
let cities = [
  {name: "Bratislava", latitude: 48.1486, longitude: 17.1077},
  {name: "Singapore", latitude: 1.3521, longitude: 103.8198},
  {name: "New York", latitude: 40.7128, longitude: (-74.0060)},
  {name: "Sydney", latitude: (-33.8688), longitude: 151.2093},
  {name: "Mexico", latitude: 19.4326, longitude: (-99.1332)},
  {name: "Helsinki", latitude: 60.1695, longitude: 24.9354},
  {name: "Athens", latitude: 37.9838, longitude: 23.7275},
];

let fetchTemperature =
    (~latitude, ~longitude, ~setCurrentTemperatureAtCelsius) => {
  let url =
    "https://api.open-meteo.com/v1/forecast?latitude="
    ++ string_of_float(latitude)
    ++ "&longitude="
    ++ string_of_float(longitude)
    ++ "&current_weather=true";
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.text)
    |> then_(text => {
         // we will get text, can be skipped just for future reference
         //Js.log(text);

         let json = Js.Json.parseExn(text); // example of parsing the text to json
         let temperature =
           switch (Js.Json.decodeObject(json)) {
           // transofrming json to readable object
           | Some(obj) =>
             //do we have object?
             switch (Js.Dict.get(obj, "current_weather")) {
             // This will access value for key
             | Some(weather) =>
               switch (Js.Json.decodeObject(weather)) {
               // have to decode before acces
               | Some(weatherObj) =>
                 switch (Js.Dict.get(weatherObj, "temperature")) {
                 | Some(temp) => Js.Json.decodeNumber(temp)
                 | None => None
                 }
               | None => None
               }
             | None => None
             }
           | None => None
           };
         switch (temperature) {
         | Some(temp) =>
           setCurrentTemperatureAtCelsius(_ => Js.Float.toString(temp))
         | None => Js.log("Could not parse temperature")
         };
         Js.Promise.resolve(Js.undefined);
       })
    |> catch(_ => {
         Js.log("API error");
         Js.Promise.resolve(Js.undefined);
       })
    |> ignore
  );
  ();
};

let getTemperatureForSelectedCity =
    (
      ~selectedCity,
      ~setCurrentTemperatureAtCelsius,
      ~_setLatitude,
      ~_setLongitude,
    ) => {
  let foundCity = List.find_opt(c => c.name === selectedCity, cities);
  switch (foundCity) {
  | Some(city) =>
    let latitude = city.latitude;
    let longitude = city.longitude;
    _setLatitude(_ => Js.Float.toString(latitude));
    _setLongitude(_ => Js.Float.toString(longitude));
    fetchTemperature(~latitude, ~longitude, ~setCurrentTemperatureAtCelsius);
  | None => Js.log("City not found")
  };
};

let getFirstCity = () => {
  switch (Array.of_list(cities)) {
  | [||] => "" // v prípade, že zoznam je prázdny, vráti prázdny reťazec
  | citiesArray => citiesArray[0].name
  };
};

[@react.component]
let make = () => {
  let (selectedCity, setSelectedCity) = React.useState(() => getFirstCity());
  let (_latitude, _setLatitude) = React.useState(() => "");
  let (_longitude, _setLongitude) = React.useState(() => "");
  let (currentTemperatureAtCelsius, setCurrentTemperatureAtCelsius) =
    React.useState(() => "");

  React.useEffect0(() => {
    fetchTemperature(
      ~latitude=48.1486,
      ~longitude=17.1077,
      ~setCurrentTemperatureAtCelsius,
    );

    None;
  });

  <div className=css##card>
    <h1> {React.string("Simple Weather App")} </h1>
    <label className=css##label> {React.string("City: ")} </label>
    <select
      className=css##select
      name="selectCity"
      value=selectedCity
      onChange={evt => {
        let selectedValue: string = getValueFromEvent(evt);
        setSelectedCity(_ => selectedValue);
        getTemperatureForSelectedCity(
          ~selectedCity=selectedValue,
          ~setCurrentTemperatureAtCelsius,
          ~_setLatitude,
          ~_setLongitude,
        );
      }}>
      {cities
       |> List.map(city =>
            <option key={city.name} value={city.name}>
              {React.string(city.name)}
            </option>
          )
       |> Array.of_list
       |> React.array}
    </select>
    <div>
      <span className=css##temperatureLabel>
        {React.string("Temperature: ")}
      </span>
      <br />
      {React.string(currentTemperatureAtCelsius ++ {js| °C|js})}
      {React.string(" | ")}
      {React.string(
         Js.Float.toFixed(convert2(currentTemperatureAtCelsius), ~digits=2)
         ++ {js| °F|js},
       )}
    </div>
  </div>;
};

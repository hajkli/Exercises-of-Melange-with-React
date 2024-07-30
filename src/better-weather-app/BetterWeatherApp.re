[@mel.module "./bwa.module.css"] external css: Js.t({..}) = "default";

/* Todo: change to env variable, meybe envdot  */
[@mel.module "./apiKeys/apiNinjasApiKey.js"]
external loadedApiKey: string = "apiKey";

let emptyCity: CityOverview.t = {
  name: "",
  country: "",
  population: 0,
  latitude: 0.0,
  longitude: 0.0,
  flag: "",
  temperature: 0.0,
};

let fetchTemperatureOfCity =
    (
      latitude: float,
      longitude: float,
      newCityToShow: CityOverview.t,
      ~setCityOverviewData,
    ) => {
  let url =
    "https://api.open-meteo.com/v1/forecast?latitude="
    ++ string_of_float(latitude)
    ++ "&longitude="
    ++ string_of_float(longitude)
    ++ "&current_weather=true";

  Js.Promise.(
    Fetch.fetchWithInit(url, Fetch.RequestInit.make(~method_=Get, ()))
    |> then_(Fetch.Response.json)
    |> then_(json => {
         //Js.log(json);
         switch (Js.Json.decodeObject(json)) {
         | None => Js.log("Failed to decode the json as an object")
         | Some(obj) =>
           switch (Js.Dict.get(obj, "current_weather")) {
           | None => Js.log("Current Weather data not found in the object")
           | Some(currentWeather) =>
             switch (Js.Json.decodeObject(currentWeather)) {
             | None => Js.log("ailed to decode population as float")
             | Some(weatherTemperature) =>
               switch (Js.Dict.get(weatherTemperature, "temperature")) {
               | None => Js.log("Current temperature data not found in the object")
               | Some(temperatureObj) =>
                 switch (Js.Json.decodeNumber(temperatureObj)) {
                 | None => Js.log("Failed to decode temperature as a number")
                 | Some(weatherTemperature) =>
                   let newCityToShow: CityOverview.t = {
                     ...newCityToShow,
                     temperature: weatherTemperature,
                   };
                   setCityOverviewData(_ => newCityToShow);

                   Js.log(newCityToShow);
                 }
               }
             }
           }
         };
         Js.Promise.resolve();
       })
  )
  |> ignore;
  ();
};

let getPopulationDataFromJson =
    (
      json: Js.Json.t,
      selectedCity: Cities.city,
      ~cityOverviewData: CityOverview.t,
      ~setCityOverviewData,
    ) => {
  switch (Js.Json.decodeArray(json)) {
  | None => Js.log("Failed to decode JSON as array")
  | Some(arr) =>
    switch (arr[0]) {
    | None => Js.log("The array is empty or failed to get the first element")
    | Some(firstObj) =>
      switch (Js.Json.decodeObject(firstObj)) {
      | None => Js.log("Failed to decode the first element as an object")
      | Some(obj) =>
        switch (Js.Dict.get(obj, "population")) {
        | None => Js.log("Population data not found in the object")
        | Some(populationObj) =>
          switch (Js.Json.decodeNumber(populationObj)) {
          | None => Js.log("Failed to decode population as number")
          | Some(populationFloat) =>
            let newCityToShow: CityOverview.t = {
              name: selectedCity.name,
              country: selectedCity.country,
              population: int_of_float(populationFloat),
              latitude: selectedCity.latitude,
              longitude: selectedCity.longitude,
              flag: selectedCity.flag,
              temperature: cityOverviewData.temperature,
            };
            setCityOverviewData(_ => newCityToShow);

            fetchTemperatureOfCity(
              selectedCity.latitude,
              selectedCity.longitude,
              newCityToShow: CityOverview.t,
              ~setCityOverviewData,
            );
          }
        }
      }
    }
  };
};

let fetchPopulationDataOfCity =
    (
      selectedCity: Cities.city,
      ~cityOverviewData: CityOverview.t,
      ~setCityOverviewData,
    ) => {
  let apiUrl: string =
    "https://api.api-ninjas.com/v1/city?name=" ++ selectedCity.name;

  //let apiKey = "JOK4De6+mEUjzIzvuLIlCQ==Kd5cOVcmIklJ2TTh";
  let apiKey = loadedApiKey;
  Js.log(selectedCity.name);
  Js.Promise.(
    Fetch.fetchWithInit(
      apiUrl,
      Fetch.RequestInit.make(
        ~method_=Get,
        ~headers=Fetch.HeadersInit.make({"X-Api-Key": apiKey}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json => {
         //Js.log(json);
         getPopulationDataFromJson(
           json,
           selectedCity: Cities.city,
           ~cityOverviewData: CityOverview.t,
           ~setCityOverviewData,
         );

         Js.Promise.resolve();
       })
  )
  |> ignore;
  ();
};

[@react.component]
let make = () => {
  let dataForDropdown: array(ReactSelect.selectOption) =
    Cities.cities |> List.map(Cities.cityToOption) |> Stdlib.Array.of_list;

  let (fetchingNewCity: bool, setFetchingNewCity) =
    React.useState(() => false);

  let (cityOverviewData: CityOverview.t, setCityOverviewData) =
    React.useState(() =>
      (
        {
          name: "",
          country: "",
          population: 0,
          latitude: 0.0,
          longitude: 0.0,
          flag: "",
          temperature: 0.0,
        }: CityOverview.t
      )
    );

  React.useEffect1(
    () => {
      if (cityOverviewData.name != "" && fetchingNewCity == true) {
        setFetchingNewCity(_prev => false);
      };
      None;
    },
    [|cityOverviewData|],
  );

  let handleChange = (option: ReactSelect.selectOption, _meta) => {
    switch (_meta##action) {
    | Some("select-option") =>
      setFetchingNewCity(_prev => true);
      fetchPopulationDataOfCity(
        Cities.getSelectedCity(option.value),
        ~cityOverviewData: CityOverview.t,
        ~setCityOverviewData,
      );

    | Some("clear") => setCityOverviewData(_ => emptyCity)
    | Some(_) => ()
    | None => ()
    };
  };

  <div>
    <div className=css##card>
      <h2> {React.string("Select city to discover")} </h2>
      <ReactSelectWrapperExample
        isDisabled=false
        isLoading=false
        isClearable=true
        isSearchable=true
        name="capitalCityDropdown"
        dataForDropdown
        onChange=handleChange
      />
      {fetchingNewCity == true || cityOverviewData == emptyCity
         ? <ReactLoaderSpinner
             visible={Some(fetchingNewCity)}
             color={Some("#F80")}
           />
         : <CityOverview selectedCapitalCity=cityOverviewData />}
    </div>
  </div>;
};

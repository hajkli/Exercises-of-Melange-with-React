[@mel.module "./cityOverview.module.css"]
external css: Js.t({..}) = "default";

type t = {
  name: string,
  country: string,
  latitude: float,
  longitude: float,
  population: int,
  flag: string,
  temperature: float,
};

let getGoogleMapsUrl = (latitude: float, longitude: float) => {
  let stringLatitude = latitude |> string_of_float;
  let stringLongitude = longitude |> string_of_float;
  let url: string =
    "https://www.google.sk/maps/@"
    ++ stringLatitude
    ++ ","
    ++ stringLongitude
    ++ ",10z?hl=sk&entry=ttu";
  url;
};

let getRowWithString(label:string, value: string){
  if(value == ""){
    React.null
  } else{
    <Row label={label ++ ": "} value={value} />
  }
};

let getRowWithInt(label:string, value: int){
  if(value <= 0){
    React.null
  } else{
    <Row label={label ++ ": "} value={value |> string_of_int} />
  }
};

let getRowWithfloat(label:string, value: float){
  if(value == 0.){
    React.null
  } else{
    <Row label={label ++ ": "} value={(value |> string_of_float) ++ {js| °C|js}} />
  }
};


[@react.component]
let make = (~selectedCapitalCity: t) => {
  <div className=css##cityOverviewGrid>
    <h2 className=css##headline> {React.string("Capital City Overview")} </h2>
    <div className=css##block>
      {getRowWithString("Name", selectedCapitalCity.name)}
      {getRowWithString("Country", selectedCapitalCity.country)}
      {getRowWithInt("Population", selectedCapitalCity.population)}
      {getRowWithfloat("Temperature", selectedCapitalCity.temperature)}

      {selectedCapitalCity.latitude == 0.0
       && selectedCapitalCity.longitude == 0.0
         ? React.null
         : <a
             className=css##googleMapsLink
             href={getGoogleMapsUrl(
               selectedCapitalCity.latitude,
               selectedCapitalCity.longitude,
             )}
             target="_blank">
             {React.string("Find on google maps")}
           </a>}
    </div>
    <div className=css##block>
      {selectedCapitalCity.flag == ""
         ? React.null
         : <img className=css##countryFlag src={selectedCapitalCity.flag} />}
    </div>
  </div>;
};

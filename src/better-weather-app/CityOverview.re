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

[@react.component]
let make = (~selectedCapitalCity: t) => {
  <div className=css##cityOverviewGrid>
    <h2 className=css##headline> {React.string("Capital City Overview")} </h2>
    <div className=css##block>
      {selectedCapitalCity.name == ""
         ? React.null : <Row label="Name: " value={selectedCapitalCity.name} />}
      {selectedCapitalCity.country == ""
         ? React.null
         : <Row label="Country: " value={selectedCapitalCity.country} />}
      {selectedCapitalCity.country == ""
         ? React.null
         : <Row
             label="Population: "
             value={selectedCapitalCity.population |> string_of_int}
           />}
      {selectedCapitalCity.temperature == 0.
         ? React.null
         : <Row
             label="Temperature: "
             value={
               string_of_float(selectedCapitalCity.temperature)
               ++ {js| °C|js}
             }
           />}
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

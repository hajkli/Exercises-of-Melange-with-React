[@mel.module "./row.module.css"] external css: Js.t({..}) = "default";

[@react.component]
let make = (~label: string, ~value: string) => {
  <div className=css##row>
    <div className=css##col> {React.string(label)} </div>
    <div className=css##col> <strong> {React.string(value)} </strong> </div>
  </div>;
};

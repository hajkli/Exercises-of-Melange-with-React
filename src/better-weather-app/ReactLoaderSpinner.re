[@mel.module "react-loader-spinner"] [@react.component]
external make:
  (
    ~visible: option(bool)=?,
    ~wrapperClass: option(string)=?,
    ~color: option(string)=?,
    ~width: option(int)=?,
    ~height: option(int)=?
  ) =>
  React.element =
  "Puff";

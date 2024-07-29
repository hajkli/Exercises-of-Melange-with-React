// https://react-select.com/home#getting-started

type selectOption = {
  value: string,
  label: string,
};

[@mel.module "react-select"] [@react.component]
external make:
  (
    ~className: option(string)=?,
    ~defaultValue: option(selectOption)=?,
    ~isDisabled: bool,
    ~isLoading: bool,
    ~isClearable: bool,
    ~isSearchable: bool,
    ~name: string,
    ~options: array(selectOption),
    ~onChange: (selectOption, 'meta) => unit,
    ~styles: Js.t({..})
  ) =>
  React.element =
  "default";

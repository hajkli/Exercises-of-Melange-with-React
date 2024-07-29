let colourStyles = [%raw
  {|
  {
    container:
    (styles) => ({ ...styles,
      width: '100%',
      maxWidth: '420px',
      textAlign: 'left',
      marginBottom: '20px',
    }),
    control: (styles, {data, isSelected, isFocused}) => {
      return {
          ...styles,
          border: '1px solid rgba(0,0,0,.7)',
          boxShadow: isFocused ? '0 0 0 1px #ff8800' : '',
          borderColor: isFocused ? '0 0 0 1px #ff8800' : '',
          "&:hover": {
            ...styles,
              cursor: 'pointer',
              borderColor: '#ff8800!important',
              boxShadow: '0 0 0 1px #ff8800',
          }
    }},
    option: (styles, { data, isFocused, isSelected }) => {
      return {
        ...styles,
        backgroundColor:
          isSelected ? '#ff8800' :
          isFocused ? 'transparent' :
          'transparent',
        color:
          isSelected ? '#fff' :
          isFocused ? '#e57a00' :
          'black',
        cursor:
          isFocused ? 'pointer' :
          isSelected ? 'pointer' :
          'default',
      };
    },
  }
|}
];

[@react.component]
let make =
    (
      ~className: option(string)=?,
      ~defaultValue: option(ReactSelect.selectOption)=?,
      ~isDisabled: bool,
      ~isLoading: bool,
      ~isClearable: bool,
      ~isSearchable: bool,
      ~name: string,
      ~dataForDropdown: array(ReactSelect.selectOption),
      ~onChange: (ReactSelect.selectOption, 'meta) => unit,
      ~styles: option(Js.t({..}))=?,
    ) => {
  let options = dataForDropdown;

  let doWeHaveStylingFromParent: Js.t({..}) =
    switch (styles) {
    | Some(customStyle) => customStyle
    | None => colourStyles
    };

  <ReactSelect
    className
    defaultValue
    isDisabled
    isLoading
    isClearable
    isSearchable
    name
    options
    onChange
    styles=doWeHaveStylingFromParent
  />;
};

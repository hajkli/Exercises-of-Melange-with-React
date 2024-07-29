// Safe array access function - overwriting default behavior of Array.get from Stdlib
let get: (array('a), int) => option('a) =
  (array, index) =>
    switch (index) {
    | index when index < 0 || index >= Js.Array.length(array) => None       // out of bounds of array, return None
    | index => Some(Stdlib.Array.get(array, index))   // Return element of "array" at "index"
    };
#ifndef DEFINES_H
#define DEFINES_H

// PROVE_RESULT macro is used to check if a function returns an error code.
// If the function returns an error code, the macro returns it.

// #define PROVE_RESULT(x) if ((x) != 0) return (x);
// #define SAVE_DELETE(x) if ((x) != nullptr) { delete (x); (x) = nullptr; }
// #define FINALIZE_DELETE(x) if ((x) != nullptr) { (x)->Finalize(); delete (x); (x) = nullptr; }
// #define GET_ARRAY_LENGHT(x, y) (sizeof(x) / sizeof(y))
// #define GET_ARRAY_PTR_LENGHT(ptr, type) (sizeof(&(ptr)[0]) / sizeof(type))

#endif // !DEFINES_H
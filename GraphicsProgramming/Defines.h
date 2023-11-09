#ifndef DEFINES_H
#define DEFINES_H

// PROVE_RESULT macro is used to check if a function returns an error code.
// If the function returns an error code, the macro returns the error code.
#define PROVE_RESULT(x) if ((x) != 0) return (x);
#define SAVE_DELETE(x) if ((x) != nullptr) { delete (x); (x) = nullptr; }
#define FINALIZE_DELETE(x) if ((x) != nullptr) { (x)->Finalize(); delete (x); (x) = nullptr; }
#define INIT_VIEWPORT(x) \
if ((x) == nullptr) \
(x) = new Viewport(GLFW_MAJOR_VERSION, GLFW_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_OFFSET_X, WINDOW_OFFSET_Y, WINDOW_TITLE, TURQUOISE);

#endif // !DEFINES_H
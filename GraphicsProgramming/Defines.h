#ifndef DEFINES_H
#define DEFINES_H

// PROVE_RESULT macro is used to check if a function returns an error code.
// If the function returns an error code, the macro returns it.
#define PROVE_RESULT(x) if ((x) != 0) return (x);
#define SAVE_DELETE(x) if ((x) != nullptr) { delete (x); (x) = nullptr; }
#define FINALIZE_DELETE(x) if ((x) != nullptr) { (x)->Finalize(); delete (x); (x) = nullptr; }
#define GET_ARRAY_LENGHT(x, y) (sizeof(x) / sizeof(y))
#define GET_ARRAY_PTR_LENGHT(ptr, type) (sizeof(&(ptr)[0]) / sizeof(type))

// The macros below hasn't the best use case, but it's here for playing around and internalizing.
#define INIT_VIEWPORT(x) \
if ((x) == nullptr) \
(x) = new Viewport(GLFW_MAJOR_VERSION, GLFW_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_OFFSET_X, WINDOW_OFFSET_Y, WINDOW_TITLE, TURQUOISE);
#define INIT_CAMERA(x, y, z, w, k, n) \
if ((x) == nullptr) new Camera(y, z, w, k, n);
#define INIT_MATERIAL(x, y, z, w) \
if((x) == nullptr) (x) = new Material(y, z, w);
#define INIT_AMBIENT(x, y, z, w) \
if((x) == nullptr) (x) = new Ambient(y, z, w);
#define INIT_MESH(x, y, z) \
if((x) == nullptr) (x) = new Mesh(y, z);

#endif // !DEFINES_H
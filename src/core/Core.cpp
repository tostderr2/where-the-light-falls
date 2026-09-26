#include "Core.h"

// GLFW doesn't provide a portable sleep function
void Core::Sleep(int milliseconds) {
#ifdef _WIN32
    ::Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

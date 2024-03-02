#ifndef PETRA_ENGINE_SETUP_FILE_H
#define PETRA_ENGINE_SETUP_FILE_H

#ifdef _WIN32
    #define GLFW_DLL
#elif defined(_WIN64)
    #define GLFW_DLL
#elif defined(__APPLE__)
    #error "Apple isn't supported"
#endif  // !__APPLE__

#endif
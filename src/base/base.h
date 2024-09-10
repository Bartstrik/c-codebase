#ifndef BASE_H
#define BASE_H

#define _STRINGIFY(s) #s
#define STRINGIFY(s) _STRINGIFY(s)

//compiler detection
#if defined(__clang__)
#   define COMPILER COMPILER_CLANG
#elif defined(__GNUC__)
#   define COMPILER COMPILER_GCC
#elif defined(_MSC_VER)
#   define COMPILER COMPILER_CL
#else
#   error No compiler detected
#endif

//os detection
#if defined(_WIN32)
#   define OS OS_WINDOWS
#elif defined(__gnu_linux__)
#   define OS OS_LINUX
#else
#   error No OS detected
#endif

#endif //BASE_H
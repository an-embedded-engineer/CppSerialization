#pragma once
#define PLATFORM_MSVC                   (0)
#define PLATFORM_MAC                    (1)
#define PLATFORM_LINUX                  (2)
#define PLATFORM_UNKNOWN                (-1)

#define PLATFORM_TYPE_OVERRIDE_ENABLED  (0)
#define OVERRIDE_PLATFORM_TYPE          (PLATFORM_LINUX)

#if PLATFORM_TYPE_OVERRIDE_ENABLED == 1
#define PLATFORM_TYPE                   OVERRIDE_PLATFORM_TYPE
#else
#if defined(_MSC_VER)
#define PLATFORM_TYPE                   PLATFORM_MSVC         /* Visual Studio */
#elif defined(__MACH__)
#define PLATFORM_TYPE                   PLATFORM_MAC          /* Mac */
#elif defined(__linux__)
#define PLATFORM_TYPE                   PLATFORM_LINUX        /* Linux */
#else
#define PLATFORM_TYPE                   PLATFORM_UNKNOWN      /* Other */
#endif
#endif

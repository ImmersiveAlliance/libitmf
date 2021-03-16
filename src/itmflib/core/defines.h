#ifndef DEFINES_H_
#define DEFINES_H_

#if defined (_WIN32)
#if defined(ITMFLIBRARY_EXPORTS)
#define ITMFAPI __declspec(dllexport)
#else
#define ITMFAPI __declspec(dllimport)
#endif
#else
#define ITMFAPI
#endif

#endif // DEFINES_H_

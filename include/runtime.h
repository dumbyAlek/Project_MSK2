#ifndef RUNTIME_H
#define RUNTIME_H

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

/// putchard - writes a character to stderr, takes a double and returns 0.
DLLEXPORT double putchard(double X);

/// printd - prints a double to stderr as "%f\n", returns 0.
DLLEXPORT double printd(double X);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_H

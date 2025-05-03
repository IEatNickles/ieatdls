#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

typedef void *DLHandle;

inline DLHandle edl_open_dl(const char *path) {
  DLHandle handle = NULL;

#ifdef _WIN32
  handle = LoadLibrary(path);
#else
  handle = dlopen(path, RTLD_LAZY);
#endif

  return handle;
}

inline DLHandle edl_load_symbol(DLHandle handle, const char *name) {
  DLHandle sym = NULL;
#ifdef _WIN32
  sym = GetProcAddress(handle, name);
#else
  sym = dlsym(handle, name);
#endif

  return sym;
}

inline void edl_close_dl(DLHandle handle) {
#ifdef _WIN32
  FreeLibrary(handle);
#else
  dlclose(handle);
#endif
}

inline const char *edl_error() {
#ifdef _WIN32
  return GetLastError();
#else
  return dlerror();
#endif
}

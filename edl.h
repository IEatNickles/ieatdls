#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#elif unix
#include <dlfcn.h>
#endif

typedef void *DLHandle;

DLHandle edl_open_dl(const char *path) {
  DLHandle handle = NULL;

#ifdef _WIN32
  handle = LoadLibrary(path);
#elif unix
  handle = dlopen(path, RTLD_LAZY);
#endif

  return handle;
}

DLHandle edl_load_symbol(DLHandle handle, const char *name) {
  DLHandle sym = NULL;
#ifdef _WIN32
  sym = GetProcAddress(handle, name);
#elif unix
  sym = dlsym(handle, name);
#endif

  return sym;
}

void edl_close_dl(DLHandle handle) {
#ifdef _WIN32
  FreeLibrary(handle);
#elif unix
  dlclose(handle);
#endif
}

const char *edl_error() {
#ifdef _WIN32
  return GetLastError();
#else
  return dlerror();
#endif
}

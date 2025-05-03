#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#elif unix
#include <dlfcn.h>
#endif

typedef void *DLHandle;

DLHandle edl_load_dl(const char *path) {
  DLHandle handle = NULL;

#ifdef WIN32
  handle = OpenLibrary(path);
#elif unix
  handle = dlopen(path, RTLD_LAZY);
#endif

  return handle;
}

void *edl_load_function(DLHandle handle, const char *name) {
  void *fn = NULL;
#ifdef WIN32
  fn = LoadProcAddress(handle, name);
#else
  fn = dlsym(handle, name);
#endif

  return fn;
}

void edl_close_dl(DLHandle handle) {
#ifdef WIN32
  FreeLibrary(handle);
#else
  dlclose(handle);
#endif
}

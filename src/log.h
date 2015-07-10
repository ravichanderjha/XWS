#include "xorz.h"
#include <time.h>
#include <stdarg.h>

char *log_path;		//carefull to free it after running program using gfree

GFileOutputStream * log_open(const char *);

void log_server(const char *format, ...);

void log_close();

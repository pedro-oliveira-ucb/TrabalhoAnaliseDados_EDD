#include "debug.h"
#include <stdio.h>
#include <stdarg.h>

void Log( const char * format , ... ) {
#ifdef NDEBUG
#else
    va_list args;
    va_start( args , format );
    vprintf( format , args );
    va_end( args );
#endif
}
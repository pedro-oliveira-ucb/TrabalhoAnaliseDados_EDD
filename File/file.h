#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>


char * file_read_all( FILE * file );
int file_write( const char * filename , const char * content );
int file_append( const char * filename , const char * content );
void file_close( FILE * file );

#endif

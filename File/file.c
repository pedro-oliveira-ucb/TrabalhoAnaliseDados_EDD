#include "file.h"
#include "../Debug/debug.h"

FILE * file_open( const char * filename , const char * mode ) {
    Log( "[DEBUG] Called file_open to: %s, using '%s' mode\n" , filename, mode );

    FILE * file = fopen( filename , mode );
    if ( !file ) {
        printf( "Erro ao abrir o arquivo: %s\n" , filename );
    }

    return file;
}

char * file_read_all( FILE* file ) {
    Log( "[DEBUG] Called file_read_all to: %p\n" , file );

    if ( !file ) {
        Log( "[DEBUG] file_read_all: %p was null\n", file  );
        return NULL;
    }

    fseek( file , 0 , SEEK_END );
    long size = ftell( file );
    rewind( file );

    char * content = ( char * ) malloc( size + 1 );
    if ( !content ) {
        Log( "[DEBUG] file_read_all: erro ao alocar memória!\n" );
        fclose( file );
        return NULL;
    }

    fread( content , 1 , size , file );
    content[ size ] = '\0';

    fclose( file );
    return content;
}

int file_write( const char * filename , const char * content ) {
    Log( "[DEBUG] Called file_write to: %s, writing: %s\n" , filename, content );

    FILE * file = file_open( filename , "w" );
    if ( !file ) return 0;

    fprintf( file , "%s" , content );
    fclose( file );
    return 1;
}

int file_append( const char * filename , const char * content ) {
    Log( "[DEBUG] Called file_append to: %s, appending: %s\n" , filename , content );

    FILE * file = file_open( filename , "a" );
    if ( !file ) return 0;

    fprintf( file , "%s" , content );
    fclose( file );
    return 1;
}

void file_close( FILE * file ) {
    Log( "[DEBUG] Called file_close to: %p\n", file );



    if ( file ) fclose( file );
}

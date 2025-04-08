#include <stdio.h>
#include "Processo/processo.h"
#include "File/file.h"

int main( int argc , char * argv[ ] ) {
    Log( "[DEBUG] Argc: %d\n" , argc );
    for ( int i = 0; i < argc; i++ ) {
        Log( "[DEBUG] Argv[%d]: %s\n" , argc , argv[i ] );
    }

    if ( argc != 2 ) {
        printf( "Uso: %s <nome_do_arquivo>\n" , argv[ 0 ] );
        return 1;
    }

    FILE * TextFile = file_open( argv[ 1 ] , "r" );
    if ( !TextFile ) {
        printf( "Arquivo inexistente!\n" );
        return 1;
    }

    char * filecontent = file_read_all( TextFile );
    if ( !strlen( filecontent ) ) {
        printf( "Arquivo vazio!\n" );
        return 1;
    }
    
    Log( "[DEBUG] File content: %s\n" , filecontent );

    if ( !validateProcesso( filecontent ) ) {
        printf( "Sintaxe errada presente no arquivo!\n" );
        return 1;
    }

    createProcesso( filecontent );
    return 0;
}

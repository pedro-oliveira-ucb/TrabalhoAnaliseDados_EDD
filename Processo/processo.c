#include <stdio.h>
#include "processo.h"
#include "../Debug/debug.h"

void createProcesso( char * data_string ) {
	Log( "[DEBUG] CreateProcess called to: %s\n" , data_string );

}

int validateProcesso( char * processo_str ) {
	for ( int i = 0; i < strlen( processo_str ); i++ ) {
		printf( "[%d]:%c" , i , processo_str[ i ] );
	}

	return 0;
}

void DataToInt( char * data_string ) {

}

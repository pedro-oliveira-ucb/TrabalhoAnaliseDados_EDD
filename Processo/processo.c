#include <stdio.h>      // printf, fprintf, fopen, fgets, sscanf, etc.
#include <string.h>     // strcpy, strncpy, strtok, strcmp, strlen, memset
#include <time.h>       // struct tm, time_t, time, mktime, difftime
#include <ctype.h>      // isdigit
#include <math.h>       // round

#include "processo.h"

#ifdef _WIN32
#include <string.h>

char * strptime( const char * buf , const char * fmt , struct tm * tm ) {
	memset( tm , 0 , sizeof( struct tm ) );

	if ( strcmp( fmt , "%Y-%m-%d %H:%M:%S" ) == 0 ) {
		if ( sscanf( buf , "%d-%d-%d %d:%d:%d" ,
			&tm->tm_year , &tm->tm_mon , &tm->tm_mday ,
			&tm->tm_hour , &tm->tm_min , &tm->tm_sec ) == 6 ) {
			tm->tm_year -= 1900;
			tm->tm_mon -= 1;
			return ( char * ) ( buf + strlen( buf ) );
		}
	}
	return NULL;
}
#endif

Processo * buscarProcessoPorId( Processo * processos , int quantidade , int id_alvo ) {
	ordenarPorId( processos , quantidade );

	int esquerda = 0;
	int direita = quantidade - 1;

	while ( esquerda <= direita ) {
		int meio = esquerda + ( direita - esquerda ) / 2;

		// Processo encontrado
		if ( processos[ meio ].id == id_alvo ) {
			return &processos[ meio ];
		}

		// Se o ID alvo é maior, ignora metade esquerda
		if ( processos[ meio ].id < id_alvo ) {
			esquerda = meio + 1;
		}
		// Se o ID alvo é menor, ignora metade direita
		else {
			direita = meio - 1;
		}
	}

	// Processo não encontrado
	return NULL;
}

void ordenarPorData( Processo processos[ ] , int quantidade ) {
	for ( int i = 0; i < quantidade - 1; i++ ) {
		for ( int j = i + 1; j < quantidade; j++ ) {
			struct tm data1 = { 0 } , data2 = { 0 };
			sscanf( processos[ i ].data_ajuizamento , "%d-%d-%d" , &data1.tm_year , &data1.tm_mon , &data1.tm_mday );
			sscanf( processos[ j ].data_ajuizamento , "%d-%d-%d" , &data2.tm_year , &data2.tm_mon , &data2.tm_mday );
			data1.tm_year -= 1900; data1.tm_mon -= 1;
			data2.tm_year -= 1900; data2.tm_mon -= 1;

			if ( difftime( mktime( &data1 ) , mktime( &data2 ) ) > 0 ) {
				Processo temp = processos[ i ];
				processos[ i ] = processos[ j ];
				processos[ j ] = temp;
			}
		}
	}
}

int calcularDiasTramitacao( const char * data_ajuizamento ) {
	struct tm tm_data = { 0 };
	if ( !strptime( data_ajuizamento , "%Y-%m-%d %H:%M:%S" , &tm_data ) ) {
		return -1; // Data inválida
	}

	time_t time_data = mktime( &tm_data );
	if ( time_data == -1 ) {
		return -1; // Conversão falhou
	}

	time_t agora;
	time( &agora );

	double diferenca = difftime( agora , time_data );
	return ( int ) round( diferenca / ( 60 * 60 * 24 ) );
}

void mostrarDiasTramitacao( Processo * processos , int quantidade ) {
	for ( int i = 0; i < quantidade; i++ ) {
		int dias = calcularDiasTramitacao( processos[ i ].data_ajuizamento );
		printf( "Processo %d (%s): %d dias em tramitação\n" ,
			processos[ i ].id , processos[ i ].numero , dias );
	}
}

void listarMultiplosAssuntos( Processo processos[ ] , int quantidade ) {
	for ( int i = 0; i < quantidade; i++ ) {
		if ( processos[ i ].id_assunto > 1 ) {
			printf( "ID: %d - Número: %s - Assunto: %d\n" , processos[ i ].id , processos[ i ].numero , processos[ i ].id_assunto );
		}
	}
}

int compararPorId( const void * a , const void * b ) {
	const Processo * pa = ( const Processo * ) a;
	const Processo * pb = ( const Processo * ) b;
	return ( pa->id > pb->id ) - ( pa->id < pb->id );
}

void ordenarPorId( Processo * processos , int quantidade ) {
	qsort( processos , quantidade , sizeof( Processo ) , compararPorId );
}

int compararPorData( const void * a , const void * b ) {
	const Processo * pa = ( const Processo * ) a;
	const Processo * pb = ( const Processo * ) b;

	struct tm tm_a = { 0 } , tm_b = { 0 };

	if ( !strptime( pa->data_ajuizamento , "%Y-%m-%d %H:%M:%S" , &tm_a ) ||
		!strptime( pb->data_ajuizamento , "%Y-%m-%d %H:%M:%S" , &tm_b ) ) {
		return 0;
	}

	time_t time_a = mktime( &tm_a );
	time_t time_b = mktime( &tm_b );

	return ( time_a < time_b ) - ( time_a > time_b ); // Decrescente
}

void ordenarPorDataDecrescente( Processo * processos , int quantidade ) {
	qsort( processos , quantidade , sizeof( Processo ) , compararPorData );
}

int contarPorClasse( Processo * processos , int quantidade , int id_classe ) {
	int count = 0;
	for ( int i = 0; i < quantidade; i++ ) {
		for ( int j = 0; j < MAX_ARRAY && processos[ i ].id_classe[ j ] != 0; j++ ) {
			if ( processos[ i ].id_classe[ j ] == id_classe ) {
				count++;
				break;
				// Evita contar múltiplas ocorrências no mesmo processo
			}
		}
	}
	return count;
}

int contarAssuntosDistintos( Processo * processos , int quantidade ) {
	int assuntos[ 1000 ] = { 0 }; // Ajuste o tamanho conforme necessário
	int count = 0;

	for ( int i = 0; i < quantidade; i++ ) {
		for ( int j = 0; j < MAX_ARRAY && processos[ i ].id_assunto[ j ] != 0; j++ ) {
			int assunto = processos[ i ].id_assunto[ j ];
			int novo = 1;

			// Verifica se já foi contado
			for ( int k = 0; k < count; k++ ) {
				if ( assuntos[ k ] == assunto ) {
					novo = 0;
					break;
				}
			}

			if ( novo ) {
				assuntos[ count++ ] = assunto;
			}
		}
	}

	return count;
}

void listarProcessosComMultiplosAssuntos( Processo * processos , int quantidade ) {
	printf( "Processos com múltiplos assuntos:\n" );
	for ( int i = 0; i < quantidade; i++ ) {
		int num_assuntos = 0;
		while ( num_assuntos < MAX_ARRAY && processos[ i ].id_assunto[ num_assuntos ] != 0 ) {
			num_assuntos++;
		}

		if ( num_assuntos > 1 ) {
			printf( "ID: %d, Número: %s, Assuntos: " , processos[ i ].id , processos[ i ].numero );
			for ( int j = 0; j < num_assuntos; j++ ) {
				printf( "%d " , processos[ i ].id_assunto[ j ] );
			}
			printf( "\n" );
		}
	}
}

int extrair_array( const char * str , int * array , int max_size ) {
	char * token;
	char temp[ MAX_TEMP ];  // Array com tamanho fixo
	int count = 0;

	strcpy( temp , str );
	temp[ strcspn( temp , "{" ) ] = ' ';
	temp[ strcspn( temp , "}" ) ] = ' ';

	token = strtok( temp , "," );
	while ( token != NULL && count < max_size ) {
		// Remove espaços e caracteres não numéricos
		char * clean = token;
		while ( *clean && !isdigit( *clean ) ) clean++;
		array[ count++ ] = atoi( clean );
		token = strtok( NULL , "," );
	}
	return count;
}

int split_csv_line( char * line , char ** fields , int max_fields ) {
	int in_quotes = 0;
	int field_count = 0;
	char * start = line;

	for ( char * p = line; *p && field_count < max_fields; p++ ) {
		if ( *p == '"' ) {
			in_quotes = !in_quotes;
		}
		else if ( *p == ',' && !in_quotes ) {
			*p = '\0';
			fields[ field_count++ ] = start;
			start = p + 1;
		}
	}
	if ( field_count < max_fields ) {
		fields[ field_count++ ] = start;
	}
	return field_count;
}

void salvarProcessosCSV( const char * filename , Processo * processos , int quantidade ) {
	FILE * arquivo = fopen( filename , "w" );
	if ( !arquivo ) {
		printf( "Erro ao criar o arquivo %s\n" , filename );
		return;
	}

	fprintf( arquivo , "id;numero;data_ajuizamento;id_classe;id_assunto;ano_eleicao\n" );

	for ( int i = 0; i < quantidade; i++ ) {
		Processo p = processos[ i ];

		fprintf( arquivo , "%d,\"%s\",%s," , p.id , p.numero , p.data_ajuizamento );

		fprintf( arquivo , "{" );
		for ( int j = 0; j < MAX_ARRAY && p.id_classe[ j ] != 0; j++ ) {
			fprintf( arquivo , "%d" , p.id_classe[ j ] );
			if ( j < MAX_ARRAY - 1 && p.id_classe[ j + 1 ] != 0 ) {
				fprintf( arquivo , "," );
			}
		}
		fprintf( arquivo , "}," );

		// Escreve array de assuntos
		fprintf( arquivo , "{" );
		for ( int j = 0; j < MAX_ARRAY && p.id_assunto[ j ] != 0; j++ ) {
			fprintf( arquivo , "%d" , p.id_assunto[ j ] );
			if ( j < MAX_ARRAY - 1 && p.id_assunto[ j + 1 ] != 0 ) {
				fprintf( arquivo , "," );
			}
		}
		fprintf( arquivo , "}," );

		fprintf( arquivo , "%d\n" , p.ano_eleicao );
	}

	fclose( arquivo );
	printf( "Processos salvos com sucesso em %s (%d registros)\n" , filename , quantidade );
}


int lerArquivoCSV( const char * filename , Processo * Processos , int * quantidade ) {
	FILE * arquivo = fopen( filename , "r" );
	if ( !arquivo ) {
		printf( "Erro ao abrir o arquivo %s\n" , filename );
		return 0;
	}

	char linha[ MAX_LINHA ];
	// Ignora cabeçalho
	fgets( linha , MAX_LINHA , arquivo );
	*quantidade = 0;
	int IgnoredLines = 0;

	while ( fgets( linha , MAX_LINHA , arquivo ) && *quantidade < MAX_PROCESSOS ) {
		char * fields[ 6 ];
		int num_fields = split_csv_line( linha , fields , 6 );

		if ( num_fields != 6 ) {
			IgnoredLines++;
			continue;
		}

		Processo p = { 0 };

		// Processa cada campo
		p.id = atoi( fields[ 0 ] );
		strncpy( p.numero , fields[ 1 ] , sizeof( p.numero ) );
		strncpy( p.data_ajuizamento , fields[ 2 ] , sizeof( p.data_ajuizamento ) );

		// Extrai arrays
		extrair_array( fields[ 3 ] , p.id_classe , MAX_ARRAY );
		extrair_array( fields[ 4 ] , p.id_assunto , MAX_ARRAY );

		p.ano_eleicao = atoi( fields[ 5 ] );

		Processos[ ( *quantidade )++ ] = p;
	}

	fclose( arquivo );
	printf( "file %s finished with %d lines and %d syntax errors\n" , filename , *quantidade , IgnoredLines );
	return 1;
}
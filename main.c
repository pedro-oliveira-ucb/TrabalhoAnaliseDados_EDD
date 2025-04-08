#include <stdio.h>      // (printf, scanf, etc)
#include <stdlib.h>     // (malloc), funções utilitárias
#include <string.h>     // (strcmp, strcpy, etc)
#include <time.h>       // (calcular dias entre datas)
#include <locale.h>     // (acentuação com setlocale)

#include "Processo/processo.h"

void demonstrarFuncionalidades( Processo * processos , int quantidade ) {
    int opcao;
    char nomeArquivo[ 100 ];
    int id_classe , id_assunto;

    do {
        printf( "\n=== MENU DE FUNCIONALIDADES ===\n" );
        printf( "1. Ordenar processos por ID (crescente)\n" );
        printf( "2. Ordenar processos por data (decrescente)\n" );
        printf( "3. Contar processos por classe\n" );
        printf( "4. Contar assuntos distintos\n" );
        printf( "5. Listar processos com múltiplos assuntos\n" );
        printf( "6. Calcular dias em tramitação\n" );
        printf( "7. Salvar processos em arquivo CSV\n" );
        printf( "0. Sair\n" );
        printf( "Escolha uma opção: " );
        scanf( "%d" , &opcao );

        switch ( opcao ) {
        case 1:
            ordenarPorId( processos , quantidade );
            printf( "Processos ordenados por ID!\n" );
            // Mostrar os primeiros 5 para demonstração
            for ( int i = 0; i < 5 && i < quantidade; i++ ) {
                printf( "ID: %d, Número: %s\n" , processos[ i ].id , processos[ i ].numero );
            }

            printf( "Processos ordenados por ID salvos em !\n" );
            salvarProcessosCSV( "processos_ordenado_por_id.csv" , processos , quantidade );

            break;

        case 2:
            ordenarPorDataDecrescente( processos , quantidade );
            printf( "Processos ordenados por data (mais recentes primeiro)!\n" );
            // Mostrar os primeiros 5 para demonstração
            for ( int i = 0; i < 5 && i < quantidade; i++ ) {
                printf( "Data: %s, ID: %d\n" , processos[ i ].data_ajuizamento , processos[ i ].id );
            }
            break;

        case 3:
            printf( "Digite o ID da classe: " );
            scanf( "%d" , &id_classe );
            printf( "Quantidade de processos na classe %d: %d\n" ,
                id_classe , contarPorClasse( processos , quantidade , id_classe ) );
            break;

        case 4:
            printf( "Quantidade de assuntos distintos: %d\n" ,
                contarAssuntosDistintos( processos , quantidade ) );
            break;

        case 5:
            listarProcessosComMultiplosAssuntos( processos , quantidade );
            break;

        case 6:
            printf( "Digite o ID do processo: " );
            scanf( "%d" , &id_classe );

            Processo * find_process = buscarProcessoPorId( processos , quantidade , id_classe );
            if ( find_process != NULL ) {
                printf( "Dias em tramitação:\n" );
                int dias = calcularDiasTramitacao( find_process->data_ajuizamento );
                printf( "Processo %d: %d dias\n" , find_process->id , dias );
            }
            else {
                printf( "Não foi possível encontrar processo com id %d!\n", id_classe );
            }
      
            break;

        case 7:
            printf( "Digite o nome do arquivo para salvar (ex: processos_ordenados.csv): " );
            scanf( "%99s" , nomeArquivo );
            salvarProcessosCSV( nomeArquivo , processos , quantidade );
            break;

        case 0:
            printf( "Saindo...\n" );
            break;

        default:
            printf( "Opção inválida!\n" );
        }

        if ( opcao != 0 ) {
            printf( "\nPressione Enter para continuar..." );
            while ( getchar( ) != '\n' ); // Limpa buffer
            getchar( ); // Espera Enter
        }

    } while ( opcao != 0 );
}


int main( int argc , char * argv[ ] ) {
    setlocale( LC_ALL , "Portuguese" );
   
	if ( argc != 2 ) {
		printf( "Uso: %s <nome_do_arquivo>\n" , argv[ 0 ] );
		return 1;
	}

    printf( "Utilizando caracteres e acentuação da língua portuguesa!\n\n" );

	int quantidade = 0;

	Processo * processos = malloc( MAX_PROCESSOS * sizeof( Processo ) );
	if ( !processos ) {
		printf( "Erro ao alocar memória.\n" );
		return 1;
	}

    if ( !lerArquivoCSV( argv[ 1 ] , processos , &quantidade ) ) {
        printf( "Erro ao ler arquivo.\n" );
        return 1;
    }

    demonstrarFuncionalidades( processos , quantidade );

	//createProcesso( filecontent );
	return 0;
}

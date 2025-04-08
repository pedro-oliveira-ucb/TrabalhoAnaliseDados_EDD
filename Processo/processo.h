#ifndef PROCESSO_H
#define PROCESSO_H

#define MAX_PROCESSOS 20000
#define MAX_LINHA 512
#define MAX_ARRAY 10
#define MAX_TEMP 256  // Defina um tamanho máximo suficiente

typedef struct {
    int id;
    char numero[ 21 ];
    char data_ajuizamento[ 24 ];
    int id_classe[ MAX_ARRAY ];
    int id_assunto[ MAX_ARRAY ];
    int ano_eleicao;
} Processo;


/* Funções de arquivo */
int lerArquivoCSV( const char * filename , Processo * Processos , int * quantidade );
void salvarProcessosCSV( const char * filename , Processo * processos , int quantidade );

/* Funções de ordenação */
void ordenarPorId( Processo * processos , int quantidade );
void ordenarPorDataDecrescente( Processo * processos , int quantidade );

/* Funções de consulta */
int contarPorClasse( Processo * processos , int quantidade , int id_classe );
int contarAssuntosDistintos( Processo * processos , int quantidade );
void listarProcessosComMultiplosAssuntos( Processo * processos , int quantidade );
int calcularDiasTramitacao( const char * data_ajuizamento );
Processo * buscarProcessoPorId( Processo * processos , int quantidade , int id_alvo );

/* Função de demonstração */
void demonstrarFuncionalidades( Processo * processos , int quantidade );

#endif // !PROCESSO_H





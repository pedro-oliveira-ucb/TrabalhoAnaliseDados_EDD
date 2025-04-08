#ifndef PROCESSO_H
#define PROCESSO_H

//#include <string>

typedef struct {
    int ID;
    char * Numero[ 21 ];
    int MES , DIA , ANO;
    int HORA , MIN , SEC , MS;

    int ID_CLASSE;
    int ID_ASSUNTO;

    int ANO_ELEICAO;
} Processo;

int validateProcesso( char * data );
void createProcesso( char * data );
void DataToInt( char * data_string );

#endif // !PROCESSO_H





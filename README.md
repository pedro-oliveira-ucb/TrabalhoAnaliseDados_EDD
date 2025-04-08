# Leitura e Manipulação de Processos Eleitorais em C

Este projeto tem como objetivo a implementação de um programa em linguagem C capaz de ler, interpretar e manipular dados formatados em um arquivo `.csv`, que contém informações de processos da Justiça Eleitoral.

## 📄 Formato dos Dados

O arquivo `processo_043_202409032338.csv` possui uma estrutura onde cada linha representa um processo. Os campos são separados por vírgulas e incluem:

- `id`: identificador único do processo
- `numero`: número do processo
- `data_ajuizamento`: data em que o processo foi iniciado
- `id_classe`: classe do processo (entre chaves `{}`)
- `id_assunto`: assunto do processo (entre chaves `{}`)
- `ano_eleicao`: ano da eleição associada ao processo (ou 0 se não houver)

### Exemplo de linhas do arquivo:
```csv
"id","numero","data_ajuizamento","id_classe","id_assunto","ano_eleicao"
638633058,"00000103020166070018",2016-04-20 15:03:40.000,{12554},{11778},0
405287812,"06000824620216070000",2021-07-01 16:33:15.000,{12377},{11778},2020
405277919,"00000238420156070011",2015-05-18 16:49:33.000,{11541},{11778},0
```

## 🔧 Funcionalidades Implementadas
O programa realiza as seguintes operações sobre os dados:

1. Ordenação crescente por id
2. Ordenação decrescente por data_ajuizamento
3. Contagem de processos por id_classe
4. Contagem de diferentes id_assunto
5. Listagem de processos com múltiplos assuntos
6. Cálculo de dias de tramitação para cada processo

## Estrutura do Projeto

- Implementação do TAD (Tipo Abstrato de Dados) Processo
- Organização do código-fonte em três arquivos: main.c, processo.c e processo.h
- Utilização de vetores de structs
- Sem uso de bibliotecas externas para ordenação ou pesquisa
- Dados multivalorados delimitados por {}

## 📁 Saídas

- Os resultados das ordenações (itens 1 e 2) são armazenados em arquivos .csv, mantendo o cabeçalho original.

## 🔨 Compilação

- Este projeto foi compilado utilizando Visual Studio 2022 ( v143 ) e C++ 14


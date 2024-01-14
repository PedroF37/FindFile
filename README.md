# FindFile
## Projeto em C de implementação simples do comando find

Programa é chamado: `$ ./ff <diretório> <arquivo-ou-padrão>`

Exemplos:
* `$ ./ff /home/pedro github.txt` -> Acha em /home/pedro ou ou os arquivo github.txt
* `$ ./ff ~ *.pdf` -> Acha em /home/pedro os arquivos .pdf

Atenção que não usa expressões regulares apenas padrão do shell `(*?[])` usando a biblioteca fnmatch
#
Programa usa as bibliotecas:
* `libdirutils` -> https://github.com/PedroF37/DirUtils
* `libfileutils` -> https://github.com/PedroF37/FileUtils
#
Programa é compilado: `$ clang -Wall -Wextra --pedantic -std=c99 -ldirutils -lfileutils -o ff ff.c` 

# À procura de estacionamento 

### Bibliotecas 

[GoogleTest](https://github.com/PedroFigueiredoo/cal-proj/tree/master/lib/googletest-master)

[GraphViewer](https://github.com/PedroFigueiredoo/cal-proj/tree/master/lib/GraphViewerCpp-master)

[Graph Viewer Github Repository](https://github.com/dmfrodrigues/GraphViewerCpp)

[PbPlots](https://github.com/PedroFigueiredoo/cal-proj/tree/master/lib/pbPlots-master)

[PbPlots Github Repository](https://github.com/InductiveComputerScience/pbPlots)


### Ficheiros de Input

[Data](https://github.com/PedroFigueiredoo/cal-proj/tree/master/data)

### Compilação 

Nota: O projeto foi feito para funcionar em Linux. Em windows dará um erro relacionado com um include da biblioteca SFML (necessária para o GraphViewer)

Em linux, basta instalar a biblioteca SFML com o seguinte comando: sudo apt-get install libsfml-dev

Para compilar basta abrir o projeto no Clion e correr lá o target main (ou test para Unit Tests).

Para compilar pela linha de commandos, seguir as seguintes instruções (dentro da pasta cal-proj):

mkdir build

cmake -S src/ -B /build ../cal-proj/

cmake --build build/

Tanto o executável principal (main) como o executável para os unit tests (test) estarão na pasta "build"

Chamar os exucutáveis sem qualquer argumento

ex: ./main (or ./test for unit tests and timed tests)

#ifndef OBJETOS_H
#define OBJETOS_H
 
#include <random>

class Nave{
    public:
        float vertices [12];
        int numInimigosMortos = 0;
};

class Inimigo{
    public:
        float vertices [12];
        float probabilidadeBomba = 0;
        //float probabilidadeDeDescer = 0;
        float probabilidadeDeDescer = (float)rand()/(float)RAND_MAX;
        float velocidade = 0.3;

        bool irParaEsquerda = true;
        int contagemMovimento = 0;
        bool troca = false;
};

class Tiro{
    public:
        float vertices [12];
};

class BombaInimiga{
    public:
        float vertices [12];
        //float velocidadeBomba = (float)rand()/(float)RAND_MAX;
};

class Estrela{
    public:
        float vertices [12];
        //float velocidadeBomba = (float)rand()/(float)RAND_MAX;
};

class Vida{
    public:
        float vertices [12];
        //float velocidadeBomba = (float)rand()/(float)RAND_MAX;
};

class Nivel{
    public:
        //Valores referentes ao nível 1 e serão modificados quando mudar de nível
        //Nivel 1 --> (640-((30*10)+(7*9)))/2 
        int nivel = 1;
        int numLinhas = 1; 
        int numInimigosPorLinha = 10;
        int ladoInimigo = 30;
        float incInimigo = 0.3;
        float espacoInimigos = 10;
        float bordasIniciaisTela = 125;
};

#endif
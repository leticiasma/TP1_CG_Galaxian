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
        float probabilidadeBomba = (float)rand()/(float)RAND_MAX;
};

class Tiro{
    public:
        float vertices [12];
};

class BombaInimiga{
    public:
        float vertices [12];
};

#endif
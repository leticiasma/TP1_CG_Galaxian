#ifndef OBJETOS_H
#define OBJETOS_H

class Nave{
    public:
        float vertices [12];
        int inimigosMortos = 0;
};

class Inimigo{
    public:
        float vertices [12];
};

class Tiro{
    public:
        float vertices [12];
};

#endif
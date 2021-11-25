#ifndef UTEIS_TELA_H
#define UTEIS_TELA_H

#include <GLFW/glfw3.h>
#include <list>
#include "objetos.hpp"

#include <iostream>
#include <ctime>

//------------------------------------------------------------------------------------

//Tela
#define LARGURA_TELA 640
#define ALTURA_TELA 480

//Estrelas
#define LADO_ESTRELA 1
#define NUM_ESTRELAS 100

//Vidas
#define NUM_VIDAS 5
#define ESPACO_VIDAS 10

#define ALTURA_VIDA 7.5
#define LARGURA_VIDA 30
#define Y_FIXO_TL_VIDA 12.5

#define BORDA_VIDA_ESQUERDA 10
#define BORDA_VIDA_INFERIOR 10

//------------------------------------------------------------------------------------

//Tela
void configuraJanela();

void renderizaJogo(float* nave, std::list <Vida>& vidas, std::list <Estrela>& estrelas, std::list <Inimigo>& inimigos, std::list <Tiro>& tiros, std::list <BombaInimiga>& bombasInimigas);

void imprimeCoordenadas(float* nave,std::list <Inimigo>& inimigos, std::list <Tiro>& tiros, std::list <BombaInimiga>& bombasInimigas);

//------------------------------------------------------------------------------------
//Estrelas
void geraEstrelas(std::list <Estrela>& estrelas);

//------------------------------------------------------------------------------------
//Vidas
void geraVidas(std::list <Vida>& vidas);


#endif
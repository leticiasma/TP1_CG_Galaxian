#ifndef UTEIS_INIMIGOS_H
#define UTEIS_INIMIGOS_H

#include <GLFW/glfw3.h>
#include <list>
#include "objetos.hpp"

#include <iostream>
#include <ctime>

//Bombas
#define ALTURA_BOMBA 10
#define LARGURA_BOMBA 10
#define INC_BOMBA 2 //Já tem o atributo velocidade, mas é bem bugado


//------------------------------------------------------------------------------------

//Inimigos
void geraInimigos(Nivel& nivelJogo, std::list <Inimigo>& inimigos);

void atualizaInimigos(std::list <Inimigo>* inimigos);

void mataInimigos(std::list <Inimigo>& inimigos, std::list <Tiro>& tiros, int* numInimigosMortos, int* totalInimigosMortos);

void removeInimigosTela(std::list <Inimigo>& inimigos);

bool verificaSePerdeuOJogo(std::list <Inimigo>& inimigos, int &numVidas);

//------------------------------------------------------------------------------------

//Bombas
void geraBomba(float x_meio_inimigo, float y_bl_inimigo, std::list <BombaInimiga>& bombasInimigas);

void atiraBombasInimigas(Nivel& nivelJogo, std::list <Inimigo>* inimigos, std::list <BombaInimiga>* bombasInimigas);

void atualizaBombas(std::list <BombaInimiga>* bombasInimigas);

void mudaProbabilidadesInimigos(std::list <Inimigo>* inimigos);

void removeBombasTela(std::list<BombaInimiga>& bombasInimigas);

void atingeNave(float* nave, std::list<BombaInimiga>& bombasInimigas, int &numVidas, std::list<Vida>& vidas);

#endif
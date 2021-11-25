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

//Nivel 1 --> (640-((30*10)+(7*9)))/2
#define NUM_LINHAS_N1 2
#define NUM_INIMIGOS_POR_LINHA_N1 10
#define LADO_INIMIGO_N1 30
#define INC_INIMIGO_N1 0.3
#define ESPACO_INIMIGOS_N1 10
#define BORDAS_INICIAIS_TELA_N1 125

//------------------------------------------------------------------------------------

//Inimigos
void geraInimigos(std::list <Inimigo>& inimigos);

void atualizaInimigos(std::list <Inimigo>* inimigos);

void mataInimigos(std::list <Inimigo>& inimigos, std::list <Tiro>& tiros, int* numInimigosMortos);

void removeInimigosTela(std::list <Inimigo>& inimigos);

bool verificaSePerdeuOJogo(std::list <Inimigo>& inimigos);

//------------------------------------------------------------------------------------

//Bombas
void geraBomba(float x_meio_inimigo, float y_bl_inimigo, std::list <BombaInimiga>& bombasInimigas);

void atiraBombasInimigas(std::list <Inimigo>* inimigos, std::list <BombaInimiga>* bombasInimigas);

void atualizaBombas(std::list <BombaInimiga>* bombasInimigas);

void mudaProbabilidadesBombas(std::list <Inimigo>* inimigos);

void removeBombasTela(std::list<BombaInimiga>& bombasInimigas);

void atingeNave(float* nave, std::list<BombaInimiga>& bombasInimigas, int &numVidas, std::list<Vida>& vidas);

#endif
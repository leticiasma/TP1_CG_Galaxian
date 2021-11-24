#ifndef UTEIS_H
#define UTEIS_H

#include <GLFW/glfw3.h>
#include <list>
#include "objetos.hpp"

#include <iostream>

//------------------------------------------------------------------------------------

//Tela
#define LARGURA_TELA 640
#define ALTURA_TELA 480

//Nave
#define ALTURA_NAVE 15
#define LARGURA_NAVE 60
#define Y_FIXO_TL_NAVE 25

//Tiros
#define ALTURA_TIRO 20
#define LARGURA_TIRO 5
#define INC_TIRO 5

//Bombas
#define ALTURA_BOMBA 10
#define LARGURA_BOMBA 10
#define INC_BOMBA 3 //Já tem o atributo velocidade, mas é bem bugado

//Nivel 1 --> (640-((30*10)+(7*9)))/2
#define NUM_LINHAS_N1 2
#define NUM_INIMIGOS_POR_LINHA_N1 10
#define LADO_INIMIGO_N1 30
#define INC_INIMIGO_N1 0.5
#define ESPACO_INIMIGOS_N1 10
#define BORDAS_INICIAIS_TELA_N1 125

//------------------------------------------------------------------------------------

//Tela
void configuraJanela();

void renderizaJogo(float* nave,std::list <Inimigo>& inimigos, std::list <Tiro>& tiros, std::list <BombaInimiga>& bombasInimigas);

void imprimeCoordenadas(float* nave,std::list <Inimigo>& inimigos, std::list <Tiro>& tiros, std::list <BombaInimiga>& bombasInimigas);

//------------------------------------------------------------------------------------

//Nave
void inicializaNave(GLFWwindow** window, float* nave);

void atualizaNave(GLFWwindow** window, float* nave);

//------------------------------------------------------------------------------------

//Inimigos
void geraInimigos(std::list <Inimigo>& inimigos);

void atualizaInimigos(std::list <Inimigo>* inimigos);

void mataInimigos(std::list <Inimigo>& inimigos, std::list <Tiro>& tiros, int* numInimigosMortos);

void removeInimigosTela(std::list <Inimigo>& inimigos);

bool verificaSePerdeuOJogo(std::list <Inimigo>& inimigos);

//------------------------------------------------------------------------------------

//Tiros
void geraTiro(float x_meio, std::list <Tiro>& tiros);

void atualizaTiros(std::list <Tiro>* tiros);

void removeTirosTela(std::list <Tiro>& tiros);

//------------------------------------------------------------------------------------

//Bombas
void geraBomba(float x_meio_inimigo, float y_bl_inimigo, std::list <BombaInimiga>& bombasInimigas);

void atiraBombasInimigas(std::list <Inimigo>* inimigos, std::list <BombaInimiga>* bombasInimigas);

void atualizaBombas(std::list <BombaInimiga>* bombasInimigas);

void mudaProbabilidadesBombas(std::list <Inimigo>* inimigos);

void removeBombasTela(std::list<BombaInimiga>& bombasInimigas);

void atingeNave(float* nave, std::list<BombaInimiga>& bombasInimigas, int &numVidas);

#endif
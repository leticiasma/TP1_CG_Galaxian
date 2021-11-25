#ifndef UTEIS_NAVE_H
#define UTEIS_NAVE_H

#include <GLFW/glfw3.h>
#include <list>
#include "objetos.hpp"

#include <iostream>
#include <ctime>

//Nave
#define ALTURA_NAVE 15
#define LARGURA_NAVE 60
#define Y_FIXO_TL_NAVE 25

//Tiros
#define ALTURA_TIRO 20
#define LARGURA_TIRO 5
#define INC_TIRO 5

//Tela
#define LARGURA_TELA 640
#define ALTURA_TELA 480

//------------------------------------------------------------------------------------

//Nave
void inicializaNave(GLFWwindow** window, float* nave);

void atualizaNave(GLFWwindow** window, float* nave);

//------------------------------------------------------------------------------------

//Tiros
void geraTiro(float x_meio, std::list <Tiro>& tiros);

void atualizaTiros(std::list <Tiro>* tiros);

void removeTirosTela(std::list <Tiro>& tiros);

#endif
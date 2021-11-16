#include <GLFW/glfw3.h>

#include <iostream>
#include <list>
#include <iterator>

#include "objetos.hpp"
#include "uteis.hpp"

//------------------------------------------------------------------------------------

//Tela
#define LARGURA_TELA 640
#define ALTURA_TELA 480

//Nave
#define ALTURA_NAVE 15
#define LARGURA_NAVE 60
#define Y_FIXO_TL_NAVE 25

//Inimigos
#define X_MEIO_INICIAL_INIMIGO 320

//------------------------------------------------------------------------------------

//Globais
bool pause = false; //Permite pausar o jogo

float vert_quad_princ[12];

float nave[12];
std::list <Tiro> tiros;
std::list <Inimigo> inimigos;

//-----------------------------------------------------------------------------------

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        geraTiro(nave[3]+(int)(LARGURA_NAVE/2), tiros);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        pause = !pause;
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS){
        pause = !pause;
    }
}

//-----------------------------------------------------------------------------------

int main(){
    GLFWwindow *window;
    
    //Initializa a biblioteca
    if (!glfwInit()){
        return -1;
    }
    
    //Cria uma janela em modo de janela e seu contexto OpenGL
    window = glfwCreateWindow(LARGURA_TELA, ALTURA_TELA, "Galaxian", NULL, NULL);
    
    if (!window){
        glfwTerminate();
        return -1;
    }
    
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    //Tornar o contexto da janela vigente
    glfwMakeContextCurrent(window);
    
    configuraJanela();

    inicializaNave(&window, nave); //POSSIVEL FONTE DE ERROS
    geraInimigos(X_MEIO_INICIAL_INIMIGO, inimigos);

    //Loop até que o usuário feche a janela
    while (!glfwWindowShouldClose(window)){
        if(!pause){
            removeTirosTela(tiros);
            mataInimigos(inimigos, tiros);

            atualizaNave(&window, nave);
            atualizaInimigos(&inimigos);
            atualizaTiros(&tiros);
        }

        renderizaJogo(nave, inimigos, tiros);
 
        //Troca os buffers front e back
        glfwSwapBuffers(window);
        
        //Identifica e processa eventos
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}
//TENTAR PERMITIR PARA LINUX TAMBÉM, COM .lib AO INVÉS DE .dll

#include <GLFW/glfw3.h>

#include <iostream>
#include <list>
#include <iterator>

#include "objetos.hpp"
#include "uteisTela.hpp"
#include "uteisNave.hpp"
#include "uteisInimigos.hpp"

//------------------------------------------------------------------------------------

//Tela
#define LARGURA_TELA 640
#define ALTURA_TELA 480

//Nave
#define ALTURA_NAVE 15
#define LARGURA_NAVE 60
#define Y_FIXO_TL_NAVE 25

//------------------------------------------------------------------------------------

//Globais
bool pause = false; //Permite pausar o jogo
bool sairJogo = false;
bool reiniciarJogo = false;

float nave[12]; //Mudar isso pra classe já definida

int numInimigosMortos = 0;
int numVidas = 5;

std::list <Tiro> tiros;
std::list <Inimigo> inimigos;

std::list<BombaInimiga> bombasInimigas;

std::list<Estrela> estrelas;
std::list<Vida> vidas;

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
        imprimeCoordenadas(nave, inimigos, tiros, bombasInimigas);
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        sairJogo = true;
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS){
        reiniciarJogo = true;
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
    glfwSetKeyCallback(window, key_callback);

    //Tornar o contexto da janela vigente
    glfwMakeContextCurrent(window);
    
    configuraJanela();

    inicializaNave(&window, nave); //POSSIVEL FONTE DE ERROS
    geraInimigos(inimigos);
    geraEstrelas(estrelas);
    geraVidas(vidas);

    bool printVenceuJogo = false;
    bool printPerdeuJogo = false;

    bool perdeuJogo = false;

    int contagemWhile = 0;

    //Loop até que o usuário feche a janela
    while (!glfwWindowShouldClose(window) && !sairJogo){

        if(!pause){
            if(reiniciarJogo){
                numInimigosMortos = 0;
                numVidas = 5;

                tiros.clear();
                inimigos.clear();
                bombasInimigas.clear();

                geraInimigos(inimigos);

                reiniciarJogo = false;
                printVenceuJogo = false;
                printPerdeuJogo = false;
            }

            if (numInimigosMortos == 20 && !printVenceuJogo){
                std::cout<<"\nVOCE VENCEU O JOGO!\n";
                printVenceuJogo = true;
            }

            if(contagemWhile == 100){ //Tornar aleatório para não virem todas as bombas de uma vez
                mudaProbabilidadesBombas(&inimigos);
                atiraBombasInimigas(&inimigos, &bombasInimigas);
                contagemWhile = 0;
            }

            contagemWhile ++;

            removeBombasTela(bombasInimigas);
            removeTirosTela(tiros);
            removeInimigosTela(inimigos);

            atingeNave(nave, bombasInimigas, numVidas, vidas);
            mataInimigos(inimigos, tiros, &numInimigosMortos);

            perdeuJogo = verificaSePerdeuOJogo(inimigos);
            if (perdeuJogo && !printPerdeuJogo){
                std::cout<<"\nVOCE PERDEU O JOGO!\n";
                printPerdeuJogo = true;
            }

            atualizaNave(&window, nave);
            atualizaInimigos(&inimigos);
            atualizaTiros(&tiros);
            atualizaBombas(&bombasInimigas);
        }

        renderizaJogo(nave, vidas, estrelas, inimigos, tiros, bombasInimigas);
 
        //Troca os buffers front e back
        glfwSwapBuffers(window);
        
        //Identifica e processa eventos
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}
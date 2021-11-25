//TENTAR PERMITIR PARA LINUX TAMBÉM, COM .lib AO INVÉS DE .dll

#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <iostream>
#include <list>
#include <iterator>
#include <string>

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

bool subirNivel = false;

bool venceu = false;
bool perdeu = false;

bool perdeuJogo = false;

float nave[12]; //Mudar isso pra classe já definida

int numInimigosMortos = 0;
int totalInimigosMortos = 0;

int numVidas = 5;

std::list <Tiro> tiros;
std::list <Inimigo> inimigos;

std::list<BombaInimiga> bombasInimigas;

std::list<Estrela> estrelas;
std::list<Vida> vidas;

Nivel nivelJogo;

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
        numVidas = 5; //AAAAAAAAAAAAAAAAAAAA
        reiniciarJogo = true;
        nivelJogo.nivel = 1;
        nivelJogo.numLinhas = 1;

        vidas.clear();
        geraVidas(vidas);

        perdeuJogo = false;

        totalInimigosMortos = 0;

        venceu = false;
        perdeu = false;
        
    }
}

// void bitmap_output(int x, int y, char *string, void *font)
// {
//   int len, i;

//   glRasterPos2f(x, y);
//   len = (int) strlen(string);
//   for (i = 0; i < len; i++) {
//     glutBitmapCharacter(font, string[i]);
//   }
// }

// void Draw_Game_Over()
// {
//   glColor3f(0.8, 0.0, 0.0);
//   bitmap_output((0 + LARGURA_TELA) / 2 - 8,
//                 (0 + ALTURA_TELA) / 2 + 4,
//                 "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);
//   if (true)
//     bitmap_output((0 + LARGURA_TELA) / 2 - 18,
//                   (0 + ALTURA_TELA) / 2 - 4,
//                   "Congratulations. You stopped the invasion.",
//                   GLUT_BITMAP_HELVETICA_18);
// //   else
// //     bitmap_output((SCREEN_LEFT + SCREEN_RIGHT) / 2 - 18,
// //                   (SCREEN_BOTTOM + SCREEN_TOP) / 2 - 4,
// //                   "Humpf. Mankind is doomed because of you.",
// //                   GLUT_BITMAP_HELVETICA_18);
// }

//-----------------------------------------------------------------------------------

int main(int argc, char *argv[]){
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
    geraInimigos(nivelJogo, inimigos);
    geraEstrelas(estrelas);
    geraVidas(vidas);

    bool printVenceuJogo = false;
    bool printPerdeuJogo = false;

    int contagemWhile = 0;

    glutInit( & argc, argv );

    //Loop até que o usuário feche a janela
    while (!glfwWindowShouldClose(window) && !sairJogo){ 

        //RenderString(0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Hello", RGB(1.0f, 0.0f, 0.0f));

        if(!pause && !perdeuJogo){
            if(reiniciarJogo){
                numInimigosMortos = 0;
                //numVidas = 5;

                tiros.clear();
                inimigos.clear();
                bombasInimigas.clear();

                geraInimigos(nivelJogo, inimigos);

                reiniciarJogo = false;
                printVenceuJogo = false;
                printPerdeuJogo = false;

                perdeuJogo = false; //hmm
            }


            if (numInimigosMortos == nivelJogo.numLinhas*nivelJogo.numInimigosPorLinha && !printVenceuJogo){
                if (nivelJogo.nivel == 3){                    
                    //std::cout<<"\nVOCE VENCEU O JOGO! FORAM MORTOS "<<totalInimigosMortos<<" INIMIGOS. DIGITE R PARA REINICIAR.\n"; //Pra vencer o jogo tem que melhorar essa contagem de numInimigosMortos
                    perdeuJogo = true; //Deveria travar a nave...

                    venceu = true;
                }
                else{
                    //std::cout<<"\nVOCE VENCEU O ATAQUE!\n"; //Pra vencer o jogo tem que melhorar essa contagem de numInimigosMortos
                }
                
                printVenceuJogo = true;
                numInimigosMortos = 0;
                //printVenceuJogo = false;
            } 

            if (!perdeuJogo && inimigos.size() == 0 && nivelJogo.nivel < 3){
                nivelJogo.nivel++;
                nivelJogo.numLinhas++;

                reiniciarJogo = true;
                subirNivel = true;
            } 

            if(contagemWhile == 100){ //Tornar aleatório para não virem todas as bombas de uma vez
                mudaProbabilidadesInimigos(&inimigos);
                atiraBombasInimigas(nivelJogo, &inimigos, &bombasInimigas);
                contagemWhile = 0;
            }

            contagemWhile ++;

            removeBombasTela(bombasInimigas);
            removeTirosTela(tiros);
            removeInimigosTela(inimigos);

            atingeNave(nave, bombasInimigas, numVidas, vidas);
            mataInimigos(inimigos, tiros, &numInimigosMortos, &totalInimigosMortos);


            perdeuJogo = verificaSePerdeuOJogo(inimigos, numVidas);
            if (perdeuJogo && !printPerdeuJogo){
                //std::cout<<"\nVOCE PERDEU O JOGO! APERTE R PARA REINICIAR.\n";
                printPerdeuJogo = true;
                perdeu = true;
            }

            if (!perdeuJogo){
                atualizaNave(&window, nave);
                atualizaInimigos(&inimigos);
                atualizaTiros(&tiros);
                atualizaBombas(&bombasInimigas);
            }
        }

        renderizaJogo(venceu, perdeu, totalInimigosMortos, nave, vidas, estrelas, inimigos, tiros, bombasInimigas);
 
        //Troca os buffers front e back
        glfwSwapBuffers(window);
        
        //Identifica e processa eventos
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}
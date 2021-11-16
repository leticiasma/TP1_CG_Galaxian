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

//Nivel 1 --> (640-((30*10)+(7*9)))/2
#define NUM_LINHAS_N1 2
#define NUM_INIMIGOS_POR_LINHA_N1 10
#define LADO_INIMIGO_N1 30
#define INC_INIMIGO_N1 0.5
#define ESPACO_INIMIGOS_N1 10
#define BORDAS_INICIAIS_TELA_N1 125

//------------------------------------------------------------------------------------

//Tela
void configuraJanela(){
    glViewport(0.0f, 0.0f, LARGURA_TELA, ALTURA_TELA); //Especifica a parte da janela na qual o OpenGL irá desenhar (em pixels), converte de normalizada para pixels
    glMatrixMode(GL_PROJECTION); //A matriz de projeção define as propriedades da câmera que visualiza os objetos no quadro de coordenadas global. Aqui normalmente é definido o fator de zoom, proporção e os planos de recorte próximos e distantes
    glLoadIdentity(); //Substitui a matriz atual pela matriz identidade e nos coloca novamente em (0, 0, 0) (já que as transformações de matriz, como glOrpho e glRotate acumulam)
    glOrtho(0, LARGURA_TELA, 0, ALTURA_TELA, 0, 1); //Define o sistema de coordenadas
    glMatrixMode(GL_MODELVIEW); //(modo de matriz padrão) modelview matrix define como seus objetos são transformados (significando translação, rotação e escala) em seu mundo
    glLoadIdentity(); 
}

void renderizaJogo(float* nave,std::list <Inimigo>& inimigos, std::list <Tiro>& tiros){
    glClear(GL_COLOR_BUFFER_BIT);

    // Render OpenGL here
    glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
    glVertexPointer( 3, GL_FLOAT, 0, nave); // point to the vertices to be used
    glDrawArrays( GL_QUADS, 0, 4 ); // draw the vertixes
    glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute


    for (auto &inimigo : inimigos){
        glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
        glVertexPointer( 3, GL_FLOAT, 0, inimigo.vertices); // point to the vertices to be used
        glDrawArrays( GL_QUADS, 0, 4 ); // draw the vertixes
        glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute
    }

    for (auto &tiro : tiros){
        glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
        glVertexPointer( 3, GL_FLOAT, 0, tiro.vertices); // point to the vertices to be used
        glDrawArrays( GL_QUADS, 0, 4 ); // draw the vertixes
        glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute
    }
}

//------------------------------------------------------------------------------------

//Nave
void inicializaNave(GLFWwindow** window, float* nave){
    double xpos, ypos;
    glfwGetCursorPos(*window, &xpos, &ypos);

    if(xpos < 0){
        xpos = 0;
    }

    if(xpos > LARGURA_TELA-LARGURA_NAVE){
        xpos = LARGURA_TELA-LARGURA_NAVE;
    }

    float x_tl_nave = xpos-LARGURA_NAVE/2;

    //TR
    nave[0] = x_tl_nave+LARGURA_NAVE;
    nave[1] = Y_FIXO_TL_NAVE;
    nave[2] = 0.0;

    //TL
    nave[3] = x_tl_nave;
    nave[4] = Y_FIXO_TL_NAVE;
    nave[5] = 0.0;

    //BL
    nave[6] = x_tl_nave;
    nave[7] = Y_FIXO_TL_NAVE-ALTURA_NAVE;
    nave[8] = 0.0;

    //BR
    nave[9] = x_tl_nave+LARGURA_NAVE;
    nave[10] = Y_FIXO_TL_NAVE-ALTURA_NAVE;
    nave[11] = 0.0;
}

void atualizaNave(GLFWwindow** window, float* nave){
    double xpos, ypos;
    glfwGetCursorPos(*window, &xpos, &ypos);

    if(xpos < 0){
        xpos = 0;
    }

    if(xpos > LARGURA_TELA-LARGURA_NAVE){
        xpos = LARGURA_TELA-LARGURA_NAVE;
    }

    nave[0] = xpos+LARGURA_NAVE;
    nave[3] = xpos;
    nave[6] = xpos;
    nave[9] = xpos+LARGURA_NAVE;
}

//------------------------------------------------------------------------------------

//Inimigos
void geraInimigos(std::list <Inimigo>& inimigos){
    float x_tl = BORDAS_INICIAIS_TELA_N1;
    float y_tl = ALTURA_TELA+LADO_INIMIGO_N1;

    for (int i=0; i<NUM_LINHAS_N1; i++){
        for (int j=0; j<NUM_INIMIGOS_POR_LINHA_N1; j++){
            Inimigo novo_inimigo;

            //TR
            novo_inimigo.vertices[0] = x_tl+LADO_INIMIGO_N1;
            novo_inimigo.vertices[1] = y_tl;
            novo_inimigo.vertices[2] = 0.0;

            //TL
            novo_inimigo.vertices[3] = x_tl;
            novo_inimigo.vertices[4] = y_tl;
            novo_inimigo.vertices[5] = 0.0;

            //BL
            novo_inimigo.vertices[6] = x_tl;
            novo_inimigo.vertices[7] = y_tl-LADO_INIMIGO_N1;
            novo_inimigo.vertices[8] = 0.0;

            //BR
            novo_inimigo.vertices[9] = x_tl+LADO_INIMIGO_N1;
            novo_inimigo.vertices[10] = y_tl-LADO_INIMIGO_N1;
            novo_inimigo.vertices[11] = 0.0;

            inimigos.push_back(novo_inimigo);

            x_tl += LADO_INIMIGO_N1+ESPACO_INIMIGOS_N1;
        }
        x_tl = BORDAS_INICIAIS_TELA_N1;
        y_tl += LADO_INIMIGO_N1+ESPACO_INIMIGOS_N1;
    }
}

void atualizaInimigos(std::list <Inimigo>* inimigos){
    for (auto &inimigo : *inimigos){
        inimigo.vertices[1] -= INC_INIMIGO_N1;
        inimigo.vertices[4] -= INC_INIMIGO_N1;
        inimigo.vertices[7] -= INC_INIMIGO_N1;
        inimigo.vertices[10] -= INC_INIMIGO_N1;
    }
}

void mataInimigos(std::list <Inimigo>& inimigos, std::list <Tiro>& tiros, int* numInimigosMortos){
    std::list <Inimigo>::iterator it_inimigo = inimigos.begin();

    while (it_inimigo!=inimigos.end()){
        std::list <Tiro>::iterator it_tiro = tiros.begin();

        while (it_tiro!=tiros.end()){
            if (it_tiro->vertices[9]>=it_inimigo->vertices[6] && it_tiro->vertices[6]<=it_inimigo->vertices[9]){
                if (it_tiro->vertices[4]>=it_inimigo->vertices[7]){
                    it_inimigo = inimigos.erase(it_inimigo);
                    it_tiro = tiros.erase(it_tiro);
                    
                    *numInimigosMortos += 1;
                }
            }

            ++it_tiro;
        }

        ++it_inimigo;
    }    
}

void removeInimigosTela(std::list <Inimigo>& inimigos){
    std::list <Inimigo>::iterator it = inimigos.begin();

    while (it!=inimigos.end()){
        if (it->vertices[4]<=0){
            it = inimigos.erase(it);
        }
        ++it;
    }
}

bool verificaSePerdeuOJogo(std::list <Inimigo>& inimigos){
    std::list <Inimigo>::iterator it = inimigos.begin();

    while (it!=inimigos.end()){
        if (it->vertices[7]<=Y_FIXO_TL_NAVE){
            return true;
        }
        ++it;
    }
    return false;
}

//------------------------------------------------------------------------------------

//Tiros
void geraTiro(float x_meio, std::list <Tiro>& tiros){
    Tiro novo_tiro;

    float x_tl = x_meio-LARGURA_TIRO/2;

    float y_inicial = Y_FIXO_TL_NAVE+ALTURA_TIRO;

    //TR
    novo_tiro.vertices[0] = x_tl+LARGURA_TIRO;
    novo_tiro.vertices[1] = y_inicial;
    novo_tiro.vertices[2] = 0.0;

    //TL
    novo_tiro.vertices[3] = x_tl;
    novo_tiro.vertices[4] = y_inicial;
    novo_tiro.vertices[5] = 0.0;

    //BL
    novo_tiro.vertices[6] = x_tl;
    novo_tiro.vertices[7] = Y_FIXO_TL_NAVE;
    novo_tiro.vertices[8] = 0.0;

    //BR
    novo_tiro.vertices[9] = x_tl+LARGURA_TIRO;
    novo_tiro.vertices[10] = Y_FIXO_TL_NAVE;
    novo_tiro.vertices[11] = 0.0;

    tiros.push_back(novo_tiro);
}

void atualizaTiros(std::list <Tiro>* tiros){
    for (auto &tiro : *tiros){
        tiro.vertices[1] += INC_TIRO;
        tiro.vertices[4] += INC_TIRO;
        tiro.vertices[7] += INC_TIRO;
        tiro.vertices[10] += INC_TIRO;
    }
}

void removeTirosTela(std::list <Tiro>& tiros){
    std::list <Tiro>::iterator it = tiros.begin();

    while (it!=tiros.end()){
        if (it->vertices[7]>=ALTURA_TELA){
            it = tiros.erase(it);
        }
        else{
            ++it;
        }
    }
}

#endif
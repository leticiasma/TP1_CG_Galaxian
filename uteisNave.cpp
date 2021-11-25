#include "uteisNave.hpp"

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

        ++it;
    }
}
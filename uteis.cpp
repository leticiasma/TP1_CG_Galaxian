#include "uteis.hpp"

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

void renderizaJogo(float* nave, std::list <Vida>& vidas, std::list <Estrela>& estrelas, std::list <Inimigo>& inimigos, std::list <Tiro>& tiros, std::list <BombaInimiga>& bombasInimigas){
    
    float colors[] = {
        1.0f, 0.0f, 0.0f // red
        // 1.0f, 0.0f, 0.0f,
        // 1.0f, 0.0f, 0.0f
        // 0.0f, 1.0f, 0.0f, // green
        // 0.0f, 1.0f, 0.0f,
        // 0.0f, 1.0f, 0.0f
    };

    float colors2[] = {
        0.0f, 0.0f, 1.0f // red
        // 1.0f, 0.0f, 0.0f,
        // 1.0f, 0.0f, 0.0f
        // 0.0f, 1.0f, 0.0f, // green
        // 0.0f, 1.0f, 0.0f,
        // 0.0f, 1.0f, 0.0f
    };

    static const GLfloat corNave[] = {0.4, 0.4, 0.4};
    static const GLfloat corVidas[] = {0.0, 1.0, 0.0};
    static const GLfloat corTiros[] = {1.0, 1.0, 0.1};
    static const GLfloat corInimigos[] = {0.6, 0.0, 0.0};
    static const GLfloat corBombas[] = {0.0, 0.0, 0.0};
    static const GLfloat corEstrelas[] = {1.0, 1.0, 1.0};
    
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto &estrela : estrelas){
        glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
        glVertexPointer( 3, GL_FLOAT, 0, estrela.vertices); // point to the vertices to be used

        // glEnableClientState(GL_COLOR_ARRAY);
        // glColorPointer(4, GL_FLOAT, 0, colors);
        // glBegin(GL_TRIANGLE_FAN);
        glColor3fv(corEstrelas);
        // glEnd();

        glDrawArrays( GL_QUADS, 0, 4 ); // draw the vertixes
        glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute
        //glDisableClientState( GL_COLOR_ARRAY );
    }    

    for (auto &inimigo : inimigos){
        glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
        glVertexPointer( 3, GL_FLOAT, 0, inimigo.vertices); // point to the vertices to be used

        // glEnableClientState(GL_COLOR_ARRAY);
        // glColorPointer(4, GL_FLOAT, 0, colors);
        // glBegin(GL_TRIANGLE_FAN);
        glColor3fv(corInimigos);
        // glEnd();

        glDrawArrays( GL_QUADS, 0, 4 ); // draw the vertixes
        glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute
        //glDisableClientState( GL_COLOR_ARRAY );
    }

    // glEnableClientState(GL_COLOR_ARRAY);
    // glColorPointer(4, GL_FLOAT, 0, colors2);

    // Render OpenGL here
    glColor3fv(corNave);
    glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
    glVertexPointer( 3, GL_FLOAT, 0, nave); // point to the vertices to be used
    glDrawArrays( GL_QUADS, 0, 4 ); // draw the vertixes
    glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute

    //glDisableClientState( GL_COLOR_ARRAY );

    for (auto &tiro : tiros){
        glColor3fv(corTiros);
        glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
        glVertexPointer( 3, GL_FLOAT, 0, tiro.vertices); // point to the vertices to be used
        glDrawArrays( GL_QUADS, 0, 4 ); // draw the vertixes
        glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute
    }

    for (auto &bomba : bombasInimigas){
        glColor3fv(corBombas);
        glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
        glVertexPointer( 3, GL_FLOAT, 0, bomba.vertices); // point to the vertices to be used
        glDrawArrays( GL_QUADS, 0, 4 ); // draw the vertixes
        glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute
    }

    for (auto &vida : vidas){
        glColor3fv(corVidas);
        glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
        glVertexPointer( 3, GL_FLOAT, 0, vida.vertices); // point to the vertices to be used
        glDrawArrays( GL_QUADS, 0, 4 ); // draw the vertixes
        glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute
    }

}

void imprimeCoordenadas(float* nave,std::list <Inimigo>& inimigos, std::list <Tiro>& tiros, std::list <BombaInimiga>& bombasInimigas){
    std::cout<<"POSICAO DA NAVE: \n";
    std::cout<<"("<<nave[3]<<","<<nave[4]<<") ";
    std::cout<<"("<<nave[0]<<","<<nave[1]<<") ";
    std::cout<<"("<<nave[9]<<","<<nave[10]<<") ";
    std::cout<<"("<<nave[6]<<","<<nave[7]<<") \n\n";

    std::cout<<"POSICAO TIROS DA NAVE: \n";
    for (auto &tiro : tiros){
        std::cout<<"("<<tiro.vertices[3]<<","<<tiro.vertices[4]<<") ";
        std::cout<<"("<<tiro.vertices[0]<<","<<tiro.vertices[1]<<") ";
        std::cout<<"("<<tiro.vertices[9]<<","<<tiro.vertices[10]<<") ";
        std::cout<<"("<<tiro.vertices[6]<<","<<tiro.vertices[7]<<") \n";
    }
    std::cout<<std::endl;


    std::cout<<"POSICAO DOS INIMIGOS: \n";
    for (auto &inimigo : inimigos){
        std::cout<<"("<<inimigo.vertices[3]<<","<<inimigo.vertices[4]<<") ";
        std::cout<<"("<<inimigo.vertices[0]<<","<<inimigo.vertices[1]<<") ";
        std::cout<<"("<<inimigo.vertices[9]<<","<<inimigo.vertices[10]<<") ";
        std::cout<<"("<<inimigo.vertices[6]<<","<<inimigo.vertices[7]<<") \n";
    }
    std::cout<<std::endl;

    std::cout<<"POSICAO DAS BOMBAS INIMIGAS: \n";
    for (auto &bomba : bombasInimigas){
        std::cout<<"("<<bomba.vertices[3]<<","<<bomba.vertices[4]<<") ";
        std::cout<<"("<<bomba.vertices[0]<<","<<bomba.vertices[1]<<") ";
        std::cout<<"("<<bomba.vertices[9]<<","<<bomba.vertices[10]<<") ";
        std::cout<<"("<<bomba.vertices[6]<<","<<bomba.vertices[7]<<") \n";
    }
    std::cout<<std::endl;

}

//------------------------------------------------------------------------------------

//Estrelas
void geraEstrelas(std::list <Estrela>& estrelas){

    unsigned seed = time(0);

    srand(seed);

    for (int i=0; i<NUM_ESTRELAS; i++){
        float x_tl = rand()%(LARGURA_TELA-LADO_ESTRELA);
        float y_tl = rand()%(ALTURA_TELA-LADO_ESTRELA);

        Estrela nova_estrela;

        //TR
        nova_estrela.vertices[0] = x_tl+LADO_ESTRELA;
        nova_estrela.vertices[1] = y_tl;
        nova_estrela.vertices[2] = 0.0;

        //TL
        nova_estrela.vertices[3] = x_tl;
        nova_estrela.vertices[4] = y_tl;
        nova_estrela.vertices[5] = 0.0;

        //BL
        nova_estrela.vertices[6] = x_tl;
        nova_estrela.vertices[7] = y_tl-LADO_ESTRELA;
        nova_estrela.vertices[8] = 0.0;

        //BR
        nova_estrela.vertices[9] = x_tl+LADO_ESTRELA;
        nova_estrela.vertices[10] = y_tl-LADO_ESTRELA;
        nova_estrela.vertices[11] = 0.0;

        estrelas.push_back(nova_estrela);
    }

}

//------------------------------------------------------------------------------------
//Vidas
void geraVidas(std::list <Vida>& vidas){

    float x_tl = BORDA_VIDA_ESQUERDA;
    float y_tl = BORDA_VIDA_INFERIOR+ALTURA_VIDA;

    for (int i=0; i<NUM_VIDAS; i++){

        Vida nova_vida;

        //TR
        nova_vida.vertices[0] = x_tl+LARGURA_VIDA;
        nova_vida.vertices[1] = y_tl;
        nova_vida.vertices[2] = 0.0;

        //TL
        nova_vida.vertices[3] = x_tl;
        nova_vida.vertices[4] = y_tl;
        nova_vida.vertices[5] = 0.0;

        //BL
        nova_vida.vertices[6] = x_tl;
        nova_vida.vertices[7] = y_tl-ALTURA_VIDA;
        nova_vida.vertices[8] = 0.0;

        //BR
        nova_vida.vertices[9] = x_tl+LARGURA_VIDA;
        nova_vida.vertices[10] = y_tl-ALTURA_VIDA;
        nova_vida.vertices[11] = 0.0;

        vidas.push_back(nova_vida);

        x_tl += LARGURA_VIDA+ESPACO_VIDAS;
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
            //geraBombaMutante(it);
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

        ++it;
    }
}

//------------------------------------------------------------------------------------

//Bombas
void geraBomba(float x_meio_inimigo, float y_bl_inimigo, std::list <BombaInimiga>& bombasInimigas){
    BombaInimiga nova_bomba;

    float x_tl = x_meio_inimigo-LARGURA_BOMBA/2;

    float y_inicial = y_bl_inimigo+ALTURA_BOMBA;

    //TR
    nova_bomba.vertices[0] = x_tl+LARGURA_BOMBA;
    nova_bomba.vertices[1] = y_inicial;
    nova_bomba.vertices[2] = 0.0;

    //TL
    nova_bomba.vertices[3] = x_tl;
    nova_bomba.vertices[4] = y_inicial;
    nova_bomba.vertices[5] = 0.0;

    //BL
    nova_bomba.vertices[6] = x_tl;
    nova_bomba.vertices[7] = y_bl_inimigo;
    nova_bomba.vertices[8] = 0.0;

    //BR
    nova_bomba.vertices[9] = x_tl+LARGURA_BOMBA;
    nova_bomba.vertices[10] = y_bl_inimigo;
    nova_bomba.vertices[11] = 0.0;

    bombasInimigas.push_back(nova_bomba);
}

void atiraBombasInimigas(std::list <Inimigo>* inimigos, std::list <BombaInimiga>* bombasInimigas){
    for (auto &inimigo : *inimigos){
        if (inimigo.probabilidadeBomba > 0.5){
            geraBomba(inimigo.vertices[3]+(LADO_INIMIGO_N1/2), inimigo.vertices[7], *bombasInimigas);
        }
    }
}

void atualizaBombas(std::list <BombaInimiga>* bombasInimigas){
    for (auto &bomba : *bombasInimigas){
        bomba.vertices[1] -= INC_BOMBA;
        bomba.vertices[4] -= INC_BOMBA;
        bomba.vertices[7] -= INC_BOMBA;
        bomba.vertices[10] -= INC_BOMBA;
    }
}

void mudaProbabilidadesBombas(std::list <Inimigo>* inimigos){
    for (auto &inimigo : *inimigos){
        inimigo.probabilidadeBomba = (float)rand()/(float)RAND_MAX;
    }
}

void removeBombasTela(std::list<BombaInimiga>& bombasInimigas){
    std::list<BombaInimiga>::iterator it = bombasInimigas.begin();

    while (it!=bombasInimigas.end()){
        if (it->vertices[4]<=0){
            it = bombasInimigas.erase(it);
        }
        
        ++it;
    }
}

void atingeNave(float* nave, std::list<BombaInimiga>& bombasInimigas, int &numVidas, std::list<Vida>& vidas){
    std::list<BombaInimiga>::iterator it = bombasInimigas.begin();

    while (it!=bombasInimigas.end()){ //Acho que tem que excluir as bombas antes do fim da tela senão se eu passar por cima vai contar como dano ou deixar o espaçamento embaixo da nave menor que uma bomba
        if (it->vertices[7]<=Y_FIXO_TL_NAVE){
            if (it->vertices[9]<=nave[9] && it->vertices[6]>=nave[6]){

                if (numVidas <= 0){
                    std::cout<<"\nVOCE PERDEU O JOGO! APERTE R PARA REINICIAR.\n";
                }
                else{
                    numVidas--;
                    std::cout<<"\nVOCE FOI ATINGIDO, RESTAM "<<numVidas<<" VIDAS!\n";

                    if(vidas.size()>0){
                        vidas.pop_back();
                    }
                }                    

                it = bombasInimigas.erase(it);
            }
        }

        ++it;
    }    
}
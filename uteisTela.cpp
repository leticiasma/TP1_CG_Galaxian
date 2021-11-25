#include "uteisTela.hpp"

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

void drawString2 (void * font, std::string s, float x, float y, float z){
     int i;
     glRasterPos3f(x, y, z);

     for (i = 0; i < s.size(); i++)
          glutBitmapCharacter (font, s[i]);
}

void renderizaJogo(bool venceu, bool perdeu, int score, float* nave, std::list <Vida>& vidas, std::list <Estrela>& estrelas, std::list <Inimigo>& inimigos, std::list <Tiro>& tiros, std::list <BombaInimiga>& bombasInimigas){

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

    glColor3f(0.8, 0.0, 0.0);
    std::string texto = "SCORE: "+std::to_string(score);
    drawString2(GLUT_BITMAP_HELVETICA_18, texto, LARGURA_TELA-120, 10, 0);

    if(venceu){
        glColor3f(1.0, 0.0, 0.0);
        std::string texto = "\nVOCE VENCEU O JOGO! FORAM MORTOS "+std::to_string(score)+" INIMIGOS. DIGITE R PARA REINICIAR.\n";
        drawString2(GLUT_BITMAP_HELVETICA_12, texto, 10, 300, 0);
    }
    else if (perdeu){
        glColor3f(1.0, 0.0, 0.0);
        std::string texto = "\nVOCE PERDEU O JOGO! APERTE R PARA REINICIAR.\n";
        drawString2(GLUT_BITMAP_HELVETICA_12, texto, 10, 300, 0);
    }

}



void imprimeCoordenadas(float* nave,std::list <Inimigo>& inimigos, std::list <Tiro>& tiros, std::list <BombaInimiga>& bombasInimigas){
    std::cout<<"POSICAO DA NAVE: \n";
    std::cout<<"("<<nave[3]<<","<<nave[4]<<") ";
    std::cout<<"("<<nave[0]<<","<<nave[1]<<") ";
    std::cout<<"("<<nave[9]<<","<<nave[10]<<") ";
    std::cout<<"("<<nave[6]<<","<<nave[7]<<") \n\n";

    std::cout<<"VELOCIDADE DOS TIROS DA NAVE: 5\n";
    std::cout<<"POSICAO TIROS DA NAVE: \n";
    for (auto &tiro : tiros){
        std::cout<<"("<<tiro.vertices[3]<<","<<tiro.vertices[4]<<") ";
        std::cout<<"("<<tiro.vertices[0]<<","<<tiro.vertices[1]<<") ";
        std::cout<<"("<<tiro.vertices[9]<<","<<tiro.vertices[10]<<") ";
        std::cout<<"("<<tiro.vertices[6]<<","<<tiro.vertices[7]<<") \n";
    }
    std::cout<<std::endl;

    std::cout<<"INIMIGOS: \n";
    for (auto &inimigo : inimigos){
        std::cout<<"Velocidade: "<<inimigo.velocidade<<" ; Posicao: ";
        std::cout<<"("<<inimigo.vertices[3]<<","<<inimigo.vertices[4]<<") ";
        std::cout<<"("<<inimigo.vertices[0]<<","<<inimigo.vertices[1]<<") ";
        std::cout<<"("<<inimigo.vertices[9]<<","<<inimigo.vertices[10]<<") ";
        std::cout<<"("<<inimigo.vertices[6]<<","<<inimigo.vertices[7]<<") \n";
    }
    std::cout<<std::endl;

    std::cout<<"VELOCIDADE DAS BOMBAS INIMIGAS: 2\n";
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
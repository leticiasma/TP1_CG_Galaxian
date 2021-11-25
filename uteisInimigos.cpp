#include "uteisInimigos.hpp"

//Tela
#define ALTURA_TELA 480

//Nave
#define Y_FIXO_TL_NAVE 25

//------------------------------------------------------------------------------------

//Inimigos
void geraInimigos(Nivel& nivelJogo, std::list <Inimigo>& inimigos){
    float x_tl = nivelJogo.bordasIniciaisTela;
    float y_tl = ALTURA_TELA+nivelJogo.ladoInimigo;

    for (int i=0; i<nivelJogo.numLinhas; i++){
        for (int j=0; j<nivelJogo.numInimigosPorLinha; j++){
            Inimigo novo_inimigo;

            //TR
            novo_inimigo.vertices[0] = x_tl+nivelJogo.ladoInimigo;
            novo_inimigo.vertices[1] = y_tl;
            novo_inimigo.vertices[2] = 0.0;

            //TL
            novo_inimigo.vertices[3] = x_tl;
            novo_inimigo.vertices[4] = y_tl;
            novo_inimigo.vertices[5] = 0.0;

            //BL
            novo_inimigo.vertices[6] = x_tl;
            novo_inimigo.vertices[7] = y_tl-nivelJogo.ladoInimigo;
            novo_inimigo.vertices[8] = 0.0;

            //BR
            novo_inimigo.vertices[9] = x_tl+nivelJogo.ladoInimigo;
            novo_inimigo.vertices[10] = y_tl-nivelJogo.ladoInimigo;
            novo_inimigo.vertices[11] = 0.0;

            inimigos.push_back(novo_inimigo);

            x_tl += nivelJogo.ladoInimigo+nivelJogo.espacoInimigos;
        }
        x_tl = nivelJogo.bordasIniciaisTela;
        y_tl += nivelJogo.ladoInimigo+nivelJogo.espacoInimigos;
    }
}

void atualizaInimigos(std::list <Inimigo>* inimigos){
    for (auto &inimigo : *inimigos){
        inimigo.vertices[1] -= inimigo.velocidade;
        inimigo.vertices[4] -= inimigo.velocidade;
        inimigo.vertices[7] -= inimigo.velocidade;
        inimigo.vertices[10] -= inimigo.velocidade;
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

void atiraBombasInimigas(Nivel& nivelJogo, std::list <Inimigo>* inimigos, std::list <BombaInimiga>* bombasInimigas){
    for (auto &inimigo : *inimigos){
        if (inimigo.probabilidadeDeDescer > 0.9){
            inimigo.velocidade = 0.5;
        }
        // else{
        //     inimigo.velocidade = 0.3;
        // }
        if (inimigo.probabilidadeBomba > 0.8){
            geraBomba(inimigo.vertices[3]+(nivelJogo.ladoInimigo/2), inimigo.vertices[7], *bombasInimigas);
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

void mudaProbabilidadesInimigos(std::list <Inimigo>* inimigos){
    for (auto &inimigo : *inimigos){
        inimigo.probabilidadeBomba = (float)rand()/(float)RAND_MAX;
        //inimigo.probabilidadeDeDescer = (float)rand()/(float)RAND_MAX;
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
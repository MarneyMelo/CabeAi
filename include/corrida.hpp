#ifndef CORRIDA
#define CORRIDA

#include "../include/veiculo.hpp"

const int MAX_PARADAS = MAX_CAPACIDADE;

class Corrida {
    private:
    int id_corrida;
    float duracao;
    float distTotal;
    int numParadas;
    float coordenadas[];

    public:
    Corrida();
    int getIdCorrida();
    float getDuracao();
    float getDistTotal();
    int getNumParadas();
    float getCoordenadas();
};
#endif
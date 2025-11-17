// TAD passageiro
#ifndef PASSAGEIRO
#define PASSAGEIRO

#include "../include/corrida.hpp"

struct coordenadas {
    float x;
    float y;
    float z;
};

class Passageiro {
    private:
    int idPassageiro;
    coordenadas origem;
};
#endif
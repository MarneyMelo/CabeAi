#include "../include/veiculo.hpp"
#include <iostream>

Veiculo::Veiculo(){
    this->id_veic = -1; //ID inválido para indicar que não foi inicializadp
    this->capacidade = 0;
    this-> velocidade = 0;
}

Veiculo::Veiculo(int id, int capaci, int veloc){
    this->id_veic = id;
    this->capacidade = capaci;
    this->velocidade = veloc;
}

int Veiculo::getIdVeic() const {
    return this->id_veic;
}

int Veiculo::getCapacidade() const {
    return this->capacidade;
}

float Veiculo::getVelocidade() const {
    return this->velocidade;
}

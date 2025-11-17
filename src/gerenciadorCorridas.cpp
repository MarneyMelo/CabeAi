#include "../include/gerenciadorViagens.hpp"
#include <iostream>

GerenciadorDeViagens::GerenciadorDeViagens(){
    this->maxOrigem = 0;
    this->maxDestino = 0;
}

GerenciadorDeViagens::GerenciadorDeViagens(float origemMax, float destinoMax){
    this->maxOrigem = origemMax;
    this->maxDestino = destinoMax;
}

float GerenciadorDeViagens::getMaxOrigem() const {
    return this->maxOrigem;
}

float GerenciadorDeViagens::getMaxDestino() const {
    return this->maxDestino;
}


#ifndef EVENTO_HPP
#define EVENTO_HPP

enum class TipoEvento {
    INICIO_CORRIDA,
    CHEGADA_PARADA,
    FIM_CORRIDA
};

class Evento {
private:
    float tempo;
    int idCorrida;
    int indiceParada;
    TipoEvento tipo;

public:
    Evento() : tempo(-1), 
        idCorrida(-1),
         indiceParada(-1), 
         tipo(TipoEvento::INICIO_CORRIDA) {}

    Evento(float tempo, int idCorrida, int indiceParada, TipoEvento tipo)
        : tempo(tempo),
          idCorrida(idCorrida),
          indiceParada(indiceParada),
          tipo(tipo) {}

    //getters
    float getTempo() const { return tempo; }
    int getIdCorrida() const { return idCorrida; }
    int getIndiceParada() const { return indiceParada; }
    TipoEvento getTipo() const { return tipo; }
    
    // Sobrecarga de operador < para facilitar comparações
    bool operator<(const Evento& outro) const {
        return this->tempo < outro.tempo;
    }
};

#endif
#ifndef GERENCIADOR_CORRIDAS
#define GERENCIADOR_CORRIDAS

class GerenciadorDeCorridas{
    private:
    float maxOrigem;
    float maxDestino;

    public:
    //default Constructor
    GerenciadorDeCorridas();
    
    //main constructor
    GerenciadorDeCorridas(float origemMax, float destinoMax);

    
    //getters
    float getMaxOrigem() const;
    float getMaxDestino() const;
};
#endif
#ifndef VEICULO
#define VEICULO

const int MAX_CAPACIDADE = 4;

class Veiculo {
    private:
    int id_veic;
    int capacidade; //todos os veiculos tem a mesma capacidade
    float velocidade; //todos os veiculos tem a mesma velocidade


    public:
    //deafault constructor
    Veiculo();
    
    //main constructor
    Veiculo(int id, int capaci, int veloc);

    //getters
    int getIdVeic() const;
    int getCapacidade() const;
    float getVelocidade() const;

};

#endif
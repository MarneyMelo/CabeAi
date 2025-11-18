#ifndef PONTO_HPP
#define PONTO_HPP

struct Ponto {
    float x;
    float y;

    Ponto() : x(0.0), y(0.0) {}

    Ponto(float x, float y) : x(x), y(y) {}
};

#endif
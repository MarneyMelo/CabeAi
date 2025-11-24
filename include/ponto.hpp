#ifndef PONTO_HPP
#define PONTO_HPP

struct Ponto {
    double x;
    double y;

    Ponto() : x(0.0), y(0.0) {}

    Ponto(double x, double y) : x(x), y(y) {}
};

#endif
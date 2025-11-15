#ifndef ESTRUCTURA_HPP
#define ESTRUCTURA_HPP

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

struct Info
    {
    vector<string> camino;
    long long distancia = numeric_limits<long long> :: max ()/ 2;
    string tipo;
    };

class nodo;

class conexion
    {
        public:
        nodo* destino;
        long long peso;

        conexion (nodo* dest, long long p) : destino(dest), peso(p){}
    };

class nodo
    {   
    public:
    string Nombre;
    vector<conexion> adyacente;
    int id;

    nodo(string n, int i) : Nombre(std::move(n)), id(i){}
    };    



#endif
#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <map>
#include <queue>
#include <algorithm>
#include <cctype>
#include "Estructura.hpp"


inline string aMayusculas (const string& texto)
    {
        string resultado = texto;
        transform(resultado.begin(), resultado.end(), resultado.begin(),
            [](unsigned char c){ return toupper(c); });
        return resultado;
    }

class Grafo
{
private:
    map<string, nodo*> cuidades;
    vector <nodo*> nodos_por_id;
    const long long INF = numeric_limits<long long>::max()/2;

    string ruta_a_string(const vector<string>& camino) const;
    void dfs_rutas(nodo* actual, nodo* destino, long long dist_acum, 
        vector<string>& camino_actual, vector<Info>& rutas_encontradas,size_t max_rutas) const;

public:
    Grafo();
    ~Grafo();
    void agregarCuidad(const string& nombre);
    bool conexion(const string& origen, const string& destino, long long distancia);

    Info dijkstra(const string& origen, const string& destino) const;

    void consultarRutas(const string& origen, const string& destino) const;
    void mostrarConexiones()const;
};

#endif
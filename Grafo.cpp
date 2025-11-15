#include "Grafo.hpp"
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cfloat>
#include <functional>
#include <iostream>


Grafo::Grafo()=default;
Grafo::~Grafo()
    {
        for (nodo* n : nodos_por_id) delete n;
    }

 string Grafo::ruta_a_string(const vector<string>& camino) const
    {
        stringstream ss;
        for (size_t i = 0; i < camino.size(); ++i)
            {
                ss<< camino [i];
                if (i < camino.size()-1)
                {
                    ss << "->";
                }
            } 
            return ss.str();
    }

void Grafo::dfs_rutas(nodo* actual, nodo* destino, long long dist_acum,
            vector<string>& camino_actual, vector<Info>& rutas_encontradas,size_t max_rutas) const  
            {
                if(rutas_encontradas.size()>= max_rutas) return;
                camino_actual.push_back(actual->Nombre);

                if(actual==destino)
                    {
                        Info r;
                        r.camino = camino_actual;
                        r.distancia = dist_acum;
                        rutas_encontradas.push_back(std::move(r));
                    }
                    else
                        {
                            for (const auto& conexion: actual->adyacente)
                                {
                                    nodo* vecino = conexion.destino;
                                    bool ya_en_camino = (find(camino_actual.begin(), camino_actual.end(), vecino->Nombre) != camino_actual.end());
                                    if (!ya_en_camino)
                                        {
                                            dfs_rutas(vecino, destino, dist_acum+conexion.peso, camino_actual, rutas_encontradas, max_rutas);

                                        }
                                }
                        }
                        camino_actual.pop_back();
            }

void Grafo::agregarCuidad(const string& nombre)
            {
                string nombreMayus = aMayusculas(nombre);
                if(cuidades.count(nombreMayus))
                {
                    cout << "La cuidad" << nombreMayus << "ya esta registrada."<< endl;
                    return;
                }
                
                int nuevo_id = (int) nodos_por_id.size();
                nodo* n2 = new nodo(nombreMayus, nuevo_id);
                
                cuidades[nombreMayus]= n2;
                nodos_por_id.push_back(n2);
                cout << "Cuidad"<< nombreMayus << "añadida."<<endl;
            }
 
 bool Grafo :: conexion (const string& origen, const string& destino, long long distancia)
            {
                string o = aMayusculas(origen);
                string d = aMayusculas(destino);

                if (!cuidades.count(o) || !cuidades.count(d) || o == d)
                    {
                        cout <<"Error: cuidades no existe" << endl;
                        return false;
                    }
                nodo* u = cuidades.at(o);
                nodo* v = cuidades.at(d);
                
                u->adyacente.emplace_back(v, distancia);
                v->adyacente.emplace_back(u, distancia);
                
                cout << "Conexion entre" << o << "y" << d << "(" <<distancia<< "km) establecida" <<endl;  
                return true;  
            }

 Info Grafo :: dijkstra(const string& origen, const string& destino) const
    {
        Info resultado = {{}, INF, "Corta"};

            string o = aMayusculas(origen);
            string d = aMayusculas(destino);

        if (!cuidades.count(o) || !cuidades.count(d)) return resultado;    

        nodo* s= cuidades.at(o);
        nodo* t= cuidades.at(d);
        int n = nodos_por_id.size();

        vector <long long> dist(n, INF);
        vector<int> parent(n, -1);

        using P = pair<long long, int>;
        priority_queue<P, vector<P>, greater<P>> pq;

        dist[s->id] = 0;
        pq.push({0, s->id});

        while (!pq.empty())
        {
            auto[d, u_id] = pq.top(); pq.pop();
            nodo* u = nodos_por_id[u_id];

            if(d > dist[u_id]) continue;
            if(u == t) break;

            for (const auto& conexion : u->adyacente)
            {
                int v_id =  conexion.destino->id;
                long long peso = conexion.peso;
                long long new_dist = d + peso;

                if(new_dist < dist[v_id])
                {
                    dist[v_id] = new_dist;
                    parent[v_id] = u_id;
                    pq.push({new_dist, v_id});
                }
            }
        }

        if (dist[t->id] != INF)
        {
            resultado.distancia = dist[t->id];
            vector<string> path_names;
            for(int cur_id = t->id; cur_id != -1; cur_id = parent[cur_id])
            {
                path_names.push_back(nodos_por_id[cur_id]->Nombre);
            }
            reverse(path_names.begin(), path_names.end());
            resultado.camino = path_names;
        }
        return resultado;
    }           

    void Grafo::consultarRutas (const string& origen, const string& destino) const
        {
            cout << "\n=== Consultar rutas entre" << origen << "y" << destino << "===\n";
            if (!cuidades.count(origen) || !cuidades.count(destino))
            {
                cout << "No existe una cuidad con la que quiere hacer la ruta."<< endl;
                return;
            }

            vector<string> camino_temp;
            vector<Info> rutas_encontrada;
            size_t max_rutas = 200;
            dfs_rutas(cuidades.at(origen), cuidades.at(destino), 0, camino_temp, rutas_encontrada, max_rutas);
            if (rutas_encontrada.empty())
                {
                    cout<<"No hay rutas entre las cuidades."<< endl;
                    return;
                }

            sort(rutas_encontrada.begin(), rutas_encontrada.end(), [](const Info& a, const Info& b)
            {
                return a.distancia < b.distancia;
            });

            Info ruta_corta = rutas_encontrada[0];
            Info ruta_larga = rutas_encontrada.back();

            long double suma = 0.0L;
            for (const auto& r: rutas_encontrada) suma += (long double)r.distancia;
            long double media = suma/(long double)rutas_encontrada.size();

            long double MR = LDBL_MAX;
            size_t idx_media = 0;

            for(size_t i = 1; i < rutas_encontrada.size(); ++i)
            {
            long double diff = fabsl((long double)rutas_encontrada[i].distancia-media);
            if (diff<MR)
                {
                    MR = diff;
                    idx_media = i;
                }
            }
            Info ruta_media = (rutas_encontrada.size()<= 1) ? ruta_corta : rutas_encontrada[idx_media];
            if (rutas_encontrada.size() <=2) ruta_media = ruta_larga;

            cout <<"\n Ruta 1 - Corta: \n";
            cout <<"Camino:" <<ruta_a_string(ruta_corta.camino)<< "\n";
            cout <<"Distancia total:" <<ruta_corta.distancia<< "km" ;

             cout <<"\n Ruta 2 - Media: \n";
            cout <<"Camino:" <<ruta_a_string(ruta_media.camino)<< "\n";
            cout <<"Distancia total:" <<ruta_media.distancia<< "km" <<(int)media<< "Km\n\n";

             cout <<"\n Ruta 3 - Larga: \n";
            cout <<"Camino:" <<ruta_a_string(ruta_larga.camino)<< "\n";
            cout <<"Distancia total:" <<ruta_larga.distancia<< "km\n\n";   
        }

        void Grafo ::mostrarConexiones()const
            {
              cout <<  "\n=== Mapa de conexiones ===\n";
               if (cuidades.empty())
               {
                cout << "No hay cuidades agregadas."<< endl;
                return;
               }

               for(const auto& pair : cuidades)
               {
                const nodo* nodo = pair.second;
                cout << "[" <<nodo->Nombre<<"]: ";
                if (nodo->adyacente.empty())
                    {
                        cout << "Sin conexiones." << endl;
                    }
                        else
                        {   
                          for (const auto& conexion : nodo->adyacente)
                            {
                                cout << "->" <<conexion.destino->Nombre << "(" << conexion.peso << "km)";
                            }  
                            cout << endl;
                        }
               }
               cout << "\n";
            }
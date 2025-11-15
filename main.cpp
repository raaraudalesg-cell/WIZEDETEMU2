#include <iostream>
#include <limits>
#include "Grafo.hpp"
#include <string>


using namespace std;

void Mostrarmenu()
{
cout <<"\n  Menu de las cuidades \n" ;
cout << "1. Agregar cuidad\n";
cout << "2. Establecer conexion\n";
cout << "3.  Consultar rutas\n";
cout << "4. Mostrar conexion\n";
cout << "5.  Salir\n";
cout << "Selecione una opcion\n";
}

void ejecutarAplicacion() {
    Grafo red;
    int opcion;
    string cuidad1, cuidad2;
    long long distancia;

    do {
        Mostrarmenu();
        // Manejo de entrada para la opción
        if (!(cin >> opcion)) {
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
             opcion = 0; // Opción inválida
        }
        // Consume el resto de la línea para evitar problemas con getline posterior
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                cout << "Nombre de la cuidad a agregar: ";
                getline(cin, cuidad1);
                red.agregarCuidad(cuidad1);
                break;
            case 2:
                cout << "Cuidad Origen: "; getline(cin, cuidad1);
                cout << "Cuidad Destino: "; getline(cin, cuidad2);
                cout << "Distancia en km: "; 
                
                // Lee la distancia con manejo de error
                if (!(cin >> distancia) || distancia <= 0) {
                    cout << "Distancia invalida. Debe ser un numero positivo." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                red.conexion(cuidad1, cuidad2, distancia);
                break;
            case 3:
                cout << "Cuidad Origen para la consulta: "; getline(cin, cuidad1);
                cout << "Cuidad Destino para la consulta: "; getline(cin, cuidad2);
                red.consultarRutas(cuidad1, cuidad2);
                break;
            case 4:
                red.mostrarConexiones();
                break;
            case 5:
                cout << "Saliendo del sistema. Adios!" << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 5);
}

int main() {
    ejecutarAplicacion();
    return 0;
}
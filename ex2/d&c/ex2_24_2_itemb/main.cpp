#include <iostream>
using namespace std;

struct Plato {
    string nombre;
    int cantidadDisponible;
    int cantidadReservada;
    double porcentajeReservas;
};

int main() {
    Plato platos[] = {
        {"Lomo saltado",50,30},
        {"Ceviche",40,35},
        {"Ají de Gallina",30,10},
        {"Causa Limeña",20,20},
        {"Arroz con Pollo",60,45}
    };

    

    return 0;
}

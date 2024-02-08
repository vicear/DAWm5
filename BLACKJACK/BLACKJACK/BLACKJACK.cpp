// BLACKJACK.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int TAMANIO_MAXIMO = 10; // Tamaño máximo para los arrays

// Función para obtener un valor aleatorio entre 2 y 10 para las cartas
int obtenerCarta() {
    return rand() % 9 + 2; // Números entre 2 y 10
}

// Función para obtener un palo aleatorio
string obtenerPalo() {
    string palos[] = { "Corazones", "Diamantes", "Tréboles", "Picas" };
    return palos[rand() % 4];
}

// Función para calcular el puntaje, considerando el valor del As
int calcularPuntaje(int cartas[], int numCartas) {
    int puntaje = 0;
    int numAses = 0;

    for (int i = 0; i < numCartas; ++i) {
        puntaje += cartas[i];

        if (cartas[i] == 11) {
            ++numAses;
        }
    }

    // Ajustar el valor del As si el puntaje supera 21
    while (numAses > 0 && puntaje > 21) {
        puntaje -= 10;
        --numAses;
    }

    return puntaje;
}

int main() {
    srand(time(0)); // Inicializar la semilla para generar números aleatorios

    int cartasJugador[TAMANIO_MAXIMO];
    int cartasCroupier[TAMANIO_MAXIMO];
    char decisionesAs[TAMANIO_MAXIMO]; // '1' para valor 1, '11' para valor 11
    string palosJugador[TAMANIO_MAXIMO];
    string palosCroupier[TAMANIO_MAXIMO];
    int numCartasJugador = 0;
    int numCartasCroupier = 0;

    // Repartir dos cartas al jugador
    cartasJugador[numCartasJugador] = obtenerCarta();
    palosJugador[numCartasJugador] = obtenerPalo();
    decisionesAs[numCartasJugador] = ' '; // Espacio indica que aún no se ha decidido el valor del As
    ++numCartasJugador;

    cartasJugador[numCartasJugador] = obtenerCarta();
    palosJugador[numCartasJugador] = obtenerPalo();
    decisionesAs[numCartasJugador] = ' ';
    ++numCartasJugador;

    // Repartir una carta al croupier
    cartasCroupier[numCartasCroupier] = obtenerCarta();
    palosCroupier[numCartasCroupier] = obtenerPalo();
    decisionesAs[numCartasCroupier] = ' ';
    ++numCartasCroupier;

    cout << "Tu puntaje inicial: " << calcularPuntaje(cartasJugador, numCartasJugador) << " (";
    for (int i = 0; i < numCartasJugador; ++i) {
        cout << cartasJugador[i] << " de " << palosJugador[i];
        if (i < numCartasJugador - 1)
            cout << ", ";
    }
    cout << ")" << endl;

    cout << "Carta del croupier: " << cartasCroupier[0] << " de " << palosCroupier[0] << endl;

    // Turno del jugador
    while (calcularPuntaje(cartasJugador, numCartasJugador) < 21) {
        char opcion;
        cout << "¿Quieres pedir otra carta? (s/n): ";
        cin >> opcion;

        if (opcion == 's') {
            cartasJugador[numCartasJugador] = obtenerCarta();
            palosJugador[numCartasJugador] = obtenerPalo();
            decisionesAs[numCartasJugador] = ' ';
            ++numCartasJugador;

            cout << "Tu nueva carta: " << cartasJugador[numCartasJugador - 1] << " de " << palosJugador[numCartasJugador - 1] << endl;
            cout << "Tu nuevo puntaje: " << calcularPuntaje(cartasJugador, numCartasJugador) << endl;
        }
        else {
            break; // El jugador se planta
        }
    }

    // Turno del croupier
    while (calcularPuntaje(cartasCroupier, numCartasCroupier) < 17) {
        cartasCroupier[numCartasCroupier] = obtenerCarta();
        palosCroupier[numCartasCroupier] = obtenerPalo();
        decisionesAs[numCartasCroupier] = ' ';
        ++numCartasCroupier;
    }

    cout << "Puntaje del croupier: " << calcularPuntaje(cartasCroupier, numCartasCroupier) << " (";
    for (int i = 0; i < numCartasCroupier; ++i) {
        cout << cartasCroupier[i] << " de " << palosCroupier[i];
        if (i < numCartasCroupier - 1)
            cout << ", ";
    }
    cout << ")" << endl;

    // Determinar el resultado del juego
    if (calcularPuntaje(cartasJugador, numCartasJugador) > 21 ||
        (calcularPuntaje(cartasCroupier, numCartasCroupier) <= 21 &&
            calcularPuntaje(cartasCroupier, numCartasCroupier) >= calcularPuntaje(cartasJugador, numCartasJugador))) {
        cout << "¡Has perdido!" << endl;
    }
    else if (calcularPuntaje(cartasJugador, numCartasJugador) == calcularPuntaje(cartasCroupier, numCartasCroupier)) {
        cout << "¡Empate!" << endl;
    }
    else {
        cout << "¡Has ganado!" << endl;
    }

    return 0;
}

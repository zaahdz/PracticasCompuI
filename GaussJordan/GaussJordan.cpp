// Autora: Zared Hernández Cortés
// Contacto: zaredhdz333@gmail.com
// Fecha: 27-Marzo-2023

#include <iostream>
#include <array>


// Añadir std para fácil llamado de funciones
using namespace std;

//// Declaración de funciones
//Definimos un template (un tipo de dato) para nuestra matriz
template <typename matriz>
void LlenarMatriz(matriz & miMatriz);

template <typename matriz>
void ImprimirMatriz(matriz & miMatriz);

template <typename matriz>
void GaussJordan(matriz & miMatriz);

template <typename matriz>
void ImprimirSolucion(matriz & miMatriz);

template <typename matriz>
void Intercambiar_Filas(matriz & miMatriz);

int main()
{
    // Definimos el número de variables de nuestro sistema
    const int variables = 3;
    // El número de columnas será el número de variables más su solución para cada ecuación
    const int columnas = variables + 1;

    // Inicializamos la matriz que vamos a ocupar
    array <array<float, columnas>, variables> miMatriz = { 0 };

    // Pedimos al usuario que llene la matriz
    LlenarMatriz(miMatriz);

    // Ordenamos la matriz
    Intercambiar_Filas(miMatriz);

    // Aplicamos el método de Gauss-Jordan sobre nuestra matriz
    GaussJordan(miMatriz);

    // ImprimirMatriz(miMatriz);

    // Imprimimos la solución de la matriz
    ImprimirSolucion(miMatriz);

    return 0; // Indicamos que salimos del programa con éxito
}

/*
Llena 'miMatriz' con valores ingresados por el usuario para cada elemento.
No regresa ningún valor.
*/
template <typename matriz>
void LlenarMatriz(matriz & miMatriz)
{
    int variables = miMatriz.size();
    for (int i = 0; i < variables; i++) {
        for (int j = 0; j <= variables; j++) {
            cout << "Valor elemento [" << i << "][" << j << "]: ";
            cin >> miMatriz[i][j];
        }
    }
}

/*
Imprime cada elemento de 'miMatriz' emulando una matriz con corchetes cuadrados.
No regresa ningún valor.
*/
template <typename matriz>
void ImprimirMatriz(matriz & miMatriz)
{
    int variables = miMatriz.size();
    for (int i = 0; i < variables; i++) {
        cout << "[ ";
        for (int j = 0; j < variables + 1; j++)
            cout << miMatriz[i][j] << '\t';
        cout << "]\n";
    }
}

/*
Imprime en pantalla la solución para cada variable del sistema de ecuaciones correspondiente a los valores en 'miMatriz'.
No regresa ningún valor.
*/
template <typename matriz>
void ImprimirSolucion(matriz & miMatriz)
{
    cout<<"\nLa solucion es:"<<endl;
    for (int i = 0; i < 1; i++) {
        if (miMatriz[2][2] != 0){
            cout << "X0 = "<< miMatriz[0][3] << endl;
            cout << "X1 = "<< miMatriz[1][3] << endl;
            cout << "X2 = "<< miMatriz[2][3] << endl;
        } else{
            cout << "Indeterminado, tiene infinitas soluciones" << endl;
        }
    }
}

/*
Implementa el algoritmo de Gauss-Jordan sobre 'miMatriz', finalizando en ella la solución del algoritmo.
No regresa ningún valor.
*/
template <typename matriz>
void    GaussJordan(matriz & miMatriz)
{
    int variables = miMatriz.size();
    float temp1 = miMatriz[0][0]; // almacenar el valor del primer elemento
    for (int j = 0; j <= variables; j++) {
        miMatriz[0][j] /= temp1; // dividir cada elemento por el primer elemento
    }

    // Eliminar fila 2 y 3
    // fila 2
    float inv_add1 = -miMatriz[1][0];
    for (int j = 0; j <= variables; j++){
        miMatriz[1][j] += miMatriz[0][j] * inv_add1;
    }
    //  fila 3
    float inv_add2 = -miMatriz[2][0];
    for (int j = 0; j <= variables; j++){
        miMatriz[2][j] += miMatriz[0][j] * inv_add2;
    }
    // Intercambiar filas si es necesario
    for(int i = 2; i < 4 ; i++) {
        if (miMatriz[1][1] == 0){
            for (int j = 0; j < 4; j++){
                int fila_temp = miMatriz[1][j];
                miMatriz[1][j] = miMatriz[2][j];
                miMatriz[2][j] = fila_temp;
            }
        }
    }

    // Si la fila 2 esta llena de 0 se indetermina
    float suma_fila2 = 0;
    for (int j = 0; j < variables; j++) {
        suma_fila2 += (miMatriz[2][j] - miMatriz[2][3]);
    }
    if (suma_fila2 == 0){
        return;
    }

    // Hacer 1 a la posicion [1][1]
    float temp2 = miMatriz[1][1]; // **** del segundo elemento
    for (int j = 1; j <= variables; j++) {
        miMatriz[1][j] /= temp2;
    }

    // Eliminar fila 1 y 3
    // fila 1
    float inv_add = -miMatriz[0][1];
    for (int j = 1; j <= variables; j++){
        miMatriz[0][j] += miMatriz[1][j] * inv_add;
    }
    //  fila 3
    float inv_add0 = -miMatriz[2][1];
    for (int j = 1; j <= variables; j++){
        miMatriz[2][j] += miMatriz[1][j] * inv_add0;
    }

    // Si la fila 2 esta llena de 0 se indetermina
    if (miMatriz[2][2] == 0){
        return;
    }

    // Hacer 1 la 3ra fila
    float temp3 = miMatriz[2][2]; // **** del segundo elemento
    for (int j = 2; j <= variables; j++) {
        miMatriz[2][j] /= temp3;
    }

    // Eliminar fila 1 y 2
    // fila 1
    float inv_add3 = -miMatriz[0][2];
    for (int j = 2; j <= variables; j++){
        miMatriz[0][j] += miMatriz[2][j] * inv_add3;
    }
    //  fila 2
    float inv_add4 = -miMatriz[1][2];
    for (int j = 2; j <= variables; j++){
        miMatriz[1][j] += miMatriz[2][j] * inv_add4;
    }
}

template <typename matriz>
void Intercambiar_Filas(matriz & miMatriz)
{
    for(int i = 0; i < 4 ; i++) {
        if (miMatriz[0][0] == 0) {
            if (miMatriz[1][0] == 0) {
                // Intercambio de la primera fila con la tercera fila
                for (int j = 0; j < 4; j++) {
                    int fila_temp = miMatriz[0][j];
                    miMatriz[0][j] = miMatriz[2][j];
                    miMatriz[2][j] = fila_temp;
                }
            } else {
                for (int j = 0; j < 4; j++) {
                    int temp = miMatriz[0][j];
                    miMatriz[0][j] = miMatriz[1][j];
                    miMatriz[1][j] = temp;
                }
            }
        }
    }
}




// Autora: Zared Hernández Cortés
// Contacto: zaredhdz333@gmail.com
// Fecha: 29-Marzo-2023

#include <iostream>
#include <array>
using namespace std; // Añadir std para fácil llamado de funciones

#define NumeroVariables 3

//// Declaración de funciones
//Definimos un template (un tipo de dato) para nuestra matriz
template <typename matriz>
void LlenarMatriz(matriz &miMatriz);

template <typename matriz>
void GaussJordan(matriz &miMatriz);

template <typename matriz>
void ImprimirSolucion(matriz &miMatriz);

template <typename matriz>
array<float, 4> Resta(array<float, 4> a, array<float, 4> b);

template <typename matriz>
array<float, 4> Multiplicacion(array<float, 4> a, float multiplo);

template <typename matriz>
void ReordenarFilas(matriz &miMatriz);

int main()
{
    // Definimos el número de variables de nuestro sistema
    const int variables = NumeroVariables;
    // El número de columnas será el número de variables más su solición para cada ecuación
    const int columnas = variables + 1;

    // Inicializamos la matriz que vamos a ocupar
    array<array<float, columnas>, variables> miMatriz = {0};

    // Pedimos al usuario que llene la matriz
    LlenarMatriz(miMatriz);

    // Aplicamos el método de Gauss-Jordan sobre nuestra matriz
    GaussJordan(miMatriz);

    // Imprimimos la solución de la matriz
    ImprimirSolucion(miMatriz);

    return 0; // Indicamos que salimos del programa con éxito
}

/*
Llena 'miMatriz' con valores ingresados por el usuario para cada elemento.
No regresa ningún valor.
*/

template <typename matriz>
void LlenarMatriz(matriz &miMatriz)
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

/* template <typename matriz>
void ImprimirMatriz(matriz &miMatriz)
{
    int variables = miMatriz.size();
    for (int i = 0; i < variables; i++)
    {
        cout << "\n[";
        for (int j = 0; j < variables + 1; j++)
        {
            cout << miMatriz[i][j] << "\t";
        }
        cout << "]";
    }
    cout << "\n";
}*/

/*
Imprime en pantalla la solución para cada variable del sistema de ecuaciones correspondiente a los valores en 'miMatriz'.
No regresa ningún valor.
*/
template <typename matriz>
void ImprimirSolucion(matriz & miMatriz)
{
    int variables = miMatriz.size();
    cout << "\nSolucion:" <<endl;
    for(int i = 0; i < variables; i++) {
        cout << "x" << i << " = " << miMatriz[i][variables] << endl;
    }
}

/*
Implementa el algoritmo de Gauss-Jordan sobre 'miMatriz', finalizando en ella la solución del algoritmo.
No regresa ningún valor.
*/
template <typename matriz>
void GaussJordan(matriz & miMatriz)
{
    double superior;
    int index;
    double aux;
    double piv;

    int rows = miMatriz.size();
    for(int i = 0; i < rows; i++ ){
        superior = abs(miMatriz[i][i]);
        index = i;
        for(int j = i + 1; j < rows; j++){
            if(superior < abs(miMatriz[j][i])){
                superior = abs(miMatriz[j][i]);
                index = j;
            }
        }
        if(i != index){
            for(int n = 0; n < rows + 1; n++){
                aux = miMatriz[i][n];
                miMatriz[i][n] = miMatriz[index][n];
                miMatriz[index][n] = aux;
            }
        }
        if(miMatriz[i][i] == 0){
            cout << "No existe solucion\n";
        }
        else{
            for(int n = 0; n < rows; n++){
                if (n!=i){
                    piv = -miMatriz[n][i];
                    for(int m = i; m< rows + 1; m++){
                        miMatriz[n][m] = miMatriz[n][m] + piv * miMatriz[i][m] / miMatriz[i][i];
                    }
                }
                else{
                    piv = miMatriz[i][i];
                    for(int m= i; m< rows + 1; m++){
                        miMatriz[n][m] = miMatriz[n][m] / piv;
                    }
                }
            }
        }
    }
}

/*TRABAJO PRÁCTICO FINAL
INTEGRANTES: Burgos Denise, Gimenez Cinthia*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_ARTICULOS 100

// PROTOTIPO DE FUNCIONES
int ingresarCodigo();
bool validarCodigo(int codigo);
void ordenarPorDescripcion(int articulos[][5], char descripciones[][100], int n);
void ordenarPorCantidadVendida(int articulos[][5], char descripciones[][100], int n);
void mostrarStockActual(int articulos[][5], char descripciones[][100], int n);
void buscarPorCodigo(int articulos[][5], char descripciones[][100], int n, int codigo);
void mostrarEstadisticas(int articulos[][5], int n);
void salir();

int main()
{
    int art, cant_existente, cant_vendida, cant_vendida2, opcion, n;
    char descripcion[MAX_ARTICULOS][100];
    float precio;

    printf("Ingrese la cantidad de articulos que posee la ferreteria:\n");
    scanf("%d", &art);

    int articulos[MAX_ARTICULOS][5]; // Matriz para los artículos

    // Carga de artículos
    for (int i = 0; i < art; i++)
    {
        printf("Ingrese el codigo del articulo %d:\n", i + 1);
        do
        {
            scanf("%d", &articulos[i][0]);
            if (!validarCodigo(articulos[i][0]))
            {
                printf("Codigo invalido. Por favor, ingrese un codigo de 8 dígitos que comience con un rubro valido.\n");
            }

        } while (!validarCodigo(articulos[i][0]));

        printf("Ingrese la descripcion del articulo %d:\n", i + 1);
        scanf("%49[^\n]", &descripcion);
        printf("Ingrese el precio de venta del articulo %d:\n", i + 1);
        scanf("%f", &precio);
        printf("Ingrese la cantidad existente del articulo %d:\n", i + 1);
        scanf("%d", &cant_existente);
        printf("Ingrese la cantidad vendida del articulo en la primera quincena %d:\n", i + 1);
        scanf("%d", &cant_vendida);
        printf("Ingrese la cantidad vendida del articulo en la segunda quincena: %d\n", i + 1);
        scanf("%d", &cant_vendida2);

        // PARA GUARDAR LOS DATOS EN LA MATRIZ
        // articulos[i][0] = i + 1;
        articulos[i][1] = cant_existente;
        articulos[i][2] = cant_vendida + cant_vendida2; // Total vendido
        articulos[i][3] = precio;
        articulos[i][4] = cant_vendida;
        // articulos[i][5] = cant_vendida2;
    }

    // Menú de opciones
    do
    {
        printf("\nSeleccione una opcion:\n");
        printf("1. Mostrar lista de articulos ordenada por descripcion\n");
        printf("2. Mostrar lista de articulos ordenada por cantidad vendida\n");
        printf("3. Mostrar stock actual de articulos\n");
        printf("4. Buscar articulo por codigo\n");
        printf("5. Mostrar estadisticas\n");
        printf("6. Salir\n");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            ordenarPorDescripcion(articulos, descripcion, art);
            break;
        case 2:
            ordenarPorCantidadVendida(articulos, descripcion, art);

            break;
        case 3:
            mostrarStockActual(articulos, descripcion, art);
            break;
        case 4:
        {
            int codigo;
            printf("Ingrese el codigo del articulo a buscar:\n");
            scanf("%d", &codigo);
            buscarPorCodigo(articulos, descripcion, art, codigo);
            break;
        }
        case 5:
            mostrarEstadisticas(articulos, art);
            break;
        case 6:
            salir();
            break;
        default:
            printf("Opcion no valida. Intente nuevamente.\n");
            break;
        }
    } while (opcion != 6);

    return 0;
}

// FUNCION PARA ORDENAR SEGUN DESCRIPCION
void ordenarPorDescripcion(int articulos[][5], char descripciones[][100], int n) // AÑADIR PUNTERO????????
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(descripciones[i], descripciones[j]) > 0)
            {
                // Intercambia las descripciones
                char tempDesc[100];
                strcpy(tempDesc, descripciones[i]);
                strcpy(descripciones[i], descripciones[j]);
                strcpy(descripciones[j], tempDesc);
                // Intercambia los otros datos
                for (int k = 0; k < 5; k++)
                {
                    int temp = articulos[i][k];
                    articulos[i][k] = articulos[j][k];
                    articulos[j][k] = temp;
                }
            }
        }
    }
    printf("Lista de articulos ordenada por descripcion:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Codigo: %d - Descripcion: %s - Precio: %.2f - Cantidad Existente: %d - Cantidad Vendida: %d\n",
               articulos[i][0], descripciones[i], articulos[i][3], articulos[i][1], articulos[i][2]);
    }
}

// FUNCION PARA ORDENAR SEGUN CANTIDAD DE ARTICULOS VENDIDA
void ordenarPorCantidadVendida(int articulos[][5], char descripciones[][100], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int cantidadVendida_i = articulos[i][3] + articulos[i][4];
            int cantidadVendida_j = articulos[j][3] + articulos[j][4];
            if (cantidadVendida_i < cantidadVendida_j)
            {
                // Intercambia las descripciones y cantidades
                char tempDesc[50];
                strcpy(tempDesc, descripciones[i]);
                strcpy(descripciones[i], descripciones[j]);
                strcpy(descripciones[j], tempDesc);

                for (int k = 0; k < 5; k++)
                {
                    int temp = articulos[i][k];
                    articulos[i][k] = articulos[j][k];
                    articulos[j][k] = temp;
                }
            }
        }
    }
    printf("Lista de articulos ordenada por cantidad vendida:\n");
    for (int i = 0; i < n; i++)
    {
        int totalVendida = articulos[i][3] + articulos[i][4];
        float importeTotal = totalVendida * (float)articulos[i][2];
        printf("Código: %d - Descripcion: %s - Cantidad Total vendida: %d - Importe Total: %.2f\n",
               articulos[i][0], descripciones[i], totalVendida, importeTotal);
    }
}

// FUNCION PARA VER EL STOCK ACTUAL
void mostrarStockActual(int articulos[][5], char descripciones[][100], int n)
{
    printf("Stock actual de articulos:\n");
    for (int i = 0; i < n; i++)
    {
        int stockActual = articulos[i][1] - (articulos[i][4] + articulos[i][5]);
        printf("Codigo: %d - Descripcion: %s - Stock Actual: %d\n", articulos[i][0], descripciones[i], stockActual);
    }
}

// FUNCION PARA BUSCAR CODIGO
void buscarPorCodigo(int articulos[][5], char descripciones[][100], int n, int codigo)
{
    bool encontrado = false;
    for (int i = 0; i < n; i++)
    {
        if (articulos[i][0] == codigo)
        {
            printf("Articulo encontrado:\n");
            printf("Codigo: %d - Descripcion: %s - Precio: %.2f - Cantidad Vendida primera quincena: %d - Cantidad Vendida segunda quincena: %d - Stock Actual: %d\n",
                   articulos[i][0], descripciones[i], articulos[i][3], articulos[i][4], articulos[i][5], articulos[i][1] - (articulos[i][4] + articulos[i][5]));
            encontrado = true;
            break;
        }
    }
    if (!encontrado)
    {
        printf("Articulo no encontrado.\n");
    }
}

// FUNCION PARA VER ESTADISTICAS
void mostrarEstadisticas(int articulos[][5], int n)
{
    float totalArticulos = 0;
    float cantidadTotalVendida = 0;
    for (int i = 0; i < n; i++)
    {
        totalArticulos += articulos[i][1];
        cantidadTotalVendida += articulos[i][2];
    }
    printf("Total de articulos en stock: %.2f\n", totalArticulos);
    printf("Total de articulos vendidos: %.2f\n", cantidadTotalVendida);
}

// FUNCION PARA VALIDAR EL CODIGO DE ARTICULO
bool validarCodigo(int codigo)
{
    bool valido;

    if (codigo < 10000000 || codigo > 99999999)
    {
        return false;
    }

    // TOMA LOS PRIMEROS TRES DIGITOS
    int rubro = codigo / 100000;

    // VERIFICA QUE EL RUBRO ESTÉ EN LA LISTA
    return (rubro == 100 || rubro == 300 || rubro == 450 || rubro == 680 || rubro == 720);
}

// FUNCION PARA INGRESAR EL CODIGO
int ingresarCodigo()
{
    int codigo;
    bool esValido = false;
    do
    {
        printf("Ingrese el codigo del articulo (8 digitos, rubro valido: 100, 300, 450, 680, 720):\n");
        scanf("%d", &codigo);

        if (validarCodigo(codigo))
        {
            esValido = true;
        }
        else
        {
            printf("Codigo invalido. Por favor, ingrese un codigo de 8 digitos que comience con un rubro valido.\n");
        }
    } while (!esValido);

    return codigo;
}

// SALIRRR!!!!!!!
void salir()
{
    printf("Gracias por usar el sistema de gestion de 'El Tornillo Loco'. ¡Hasta pronto!\n");
}
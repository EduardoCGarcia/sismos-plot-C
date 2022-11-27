#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void generaGrafica(char *nombre, int v[], int tam);
void transformarVector(float vector[], int v[], int tam);
void mostrarVector(float v[], int tam);
void mostrarVectorI(int v[], int tam);

/*int main()
{

    char *nombre;
    nombre = "grafica.pgm";
    float vector[] = {4.5f, 6.3f, 3.5f, 7.3f, 4.7f, 6.9f, 5.5f};
    int v[] = {0, 0, 0, 0, 0, 0, 0};
    mostrarVector(vector, 7);
    transformarVector(vector, v, 7);
    mostrarVectorI(v, 7);
    generaGrafica(nombre, v, 7);
}*/
/**
 * @brief 
 * Genera una imagen bmp o mapa de bits
 * @param nombre Nombre del archivo bmp
 * @param v vector para generar la grafiaca
 * @param tam tamanio del vector
 */
void generaGrafica(char *nombre, int v[], int tam)
{

    FILE *arch;

    int numFilas = tam + (tam - 1); // numero de renglones
    // Medidas tamaño de las barras

    /* bp es el numero de pixeles standar de la base de barra (debe existir una relación entre base de pixeles,
       numFilas y altura de imagen para que la graficación no tenga errores)*/
    int bp = 60;

    // Medidas tamaño de la imagen
    int width = 100;            // ancho de la imagen
    int height = bp * numFilas; // alto de la imagen

    // Color: tiene un rango 0-255 donde 0 es negro y 255 es blanco

    int blanco = 255;
    int negro = 0;
    remove(nombre);
    arch = fopen(nombre, "a");

    if (arch == NULL)
    {
        printf("No se pudo abrir el archivo");
        return;
    }

    // fprintf(arch, "# imgane dibujada con mi aplicacion en c\n");
    fprintf(arch, "P2\n");

    fprintf(arch, "%d %d\n", width, height); // Se genera la imagen con las medidas establecidas
    //printf("\nPrimer paso");
    int color = blanco;
    int rec = 0;
    for (int i = 0; i < numFilas; i++)
    { // Genera el numero de columnas que representan los días
        //printf("Numero de filas %d:", i);
        if (i % 2 == 0)
        {

            color = blanco;
            for (int ancho = 0; ancho < bp; ancho++)
            { // ancho de la barra
                //printf("\nAncho: %d", ancho);
                for (int j = 0; j < v[rec]; j++)
                { // largo de la barra de la magnitud del sismo
                    //printf("\nLargo blanco j: %d, valor: %d", j, v[rec]);
                    fprintf(arch, "%d\n", blanco);
                }
                color = negro;
                for (int k = v[rec]; k < width; k++)
                { // largo de la barra de la magnitud del sismo
                    //printf("\nLargo negro k: %d", k);
                    fprintf(arch, "%d\n", negro);
                }
            }
            rec++;
        }
        else
        {
            //printf("\nElse");
            color = negro;
            for (int ancho = 0; ancho < bp; ancho++)
            {
                //printf("\nElse ancho: %d", ancho);
                for (int e = 0; e < width; e++)
                {
                    //printf("\nElse largo e Barra negra: %d", e);
                    fprintf(arch, "%d\n", negro);
                }
            }
        }
    }
    fclose(arch);
}
void transformarVector(float vector[], int v[], int tam)
{

    for (int i = 0; i < tam; i++)
    {
        v[i] = vector[i] * 10;
    }
}

void mostrarVector(float vector[], int tam)
{
    printf("\nVector: \n");
    for (int i = 0; i < tam; i++)
    {
        printf("|%.1f", vector[i]);
    }
}

void mostrarVectorI(int v[], int tam)
{
    printf("\nVector: \n");
    for (int i = 0; i < tam; i++)
    {
        printf("|%d", v[i]);
    }
}
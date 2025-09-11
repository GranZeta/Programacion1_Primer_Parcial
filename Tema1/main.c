#include <stdio.h>
#include <ctype.h>   // Para toupper()

// --------- PROTOTIPOS ---------
int leerEnteroEnRango(char mensaje[], int min, int max);
char leerForma();

// --------- PROGRAMA PRINCIPAL ---------
int main() {
    int nroSocio, edad, hora;
    char forma;

    // Variables de cálculo
    int sumaEdadP = 0, contP = 0;
    int socioMin = 999999, edadSocioMin = 0;
    int contSinP_7a9 = 0;

    // Carga repetida
    do {
        // 🔁 Reutilizo la misma función genérica
        nroSocio = leerEnteroEnRango("Ingrese nro de socio (0 o negativo para terminar): ", -999999, 999999);
        if (nroSocio <= 0) break;

        forma = leerForma();

        // 🔁 Reutilizo para edad (solo rango positivo, ejemplo 0-120)
        edad = leerEnteroEnRango("Ingrese edad (0-120): ", 0, 120);

        // 🔁 Reutilizo para hora (0-23)
        hora = leerEnteroEnRango("Ingrese hora (0-23): ", 0, 23);

        // Promedio prioridad
        if (forma == 'P') {
            sumaEdadP += edad;
            contP++;
        }

        // Socio con nro mínimo
        if (nroSocio < socioMin) {
            socioMin = nroSocio;
            edadSocioMin = edad;
        }

        // Personas sin prioridad entre 7 y 9
        if (forma == 'N' && hora >= 7 && hora <= 9) {
            contSinP_7a9++;
        }

    } while (nroSocio > 0);

    // --------- RESULTADOS ---------
    if (contP > 0)
        printf("\nPromedio edad prioridad: %.2f\n", (float)sumaEdadP / contP);
    else
        printf("\nNo hubo atenciones con prioridad\n");

    if (socioMin != 999999)
        printf("Edad del socio con nro minimo (%d): %d\n", socioMin, edadSocioMin);

    printf("Cantidad sin prioridad entre 7 y 9: %d\n", contSinP_7a9);

    return 0;
}

// --------- FUNCIONES AUXILIARES ---------

// 🔁 Función genérica que valida un entero en un rango
int leerEnteroEnRango(char mensaje[], int min, int max) {
    int x;
    do {
        printf("%s", mensaje);
        scanf("%d", &x);
        if (x < min || x > max)
            printf("Error: debe estar entre %d y %d.\n", min, max);
    } while (x < min || x > max);
    return x;
}

// Valida forma P o N (convierte a mayúscula)
char leerForma() {
    char c;
    do {
        printf("Ingrese forma (P prioridad / N normal): ");
        scanf(" %c", &c);
        c = toupper(c);
        if (c != 'P' && c != 'N') printf("Error: solo P o N.\n");
    } while (c != 'P' && c != 'N');
    return c;
}
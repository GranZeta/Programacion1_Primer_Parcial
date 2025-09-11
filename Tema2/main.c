#include <stdio.h>
#include <ctype.h>   // Para toupper()

// --------- PROTOTIPOS ---------
int leerEnteroEnRango(char mensaje[], int min, int max);
char leerTipoEntrega();
char leerSector();

// --------- PROGRAMA PRINCIPAL ---------
int main() {
    int nroRemito, cant;
    char tipo, sector;
    float precio;

    // Contadores y acumuladores
    int contTotal = 0, contDomicilio = 0;
    float recaudacion = 0;

    // Ventas por sector
    int ventasP = 0, ventasG = 0, ventasO = 0;

    // Carga repetida
    do {
        // 🔁 Reutilizo la misma función genérica
        nroRemito = leerEnteroEnRango("Ingrese nro remito (0 para terminar): ", 0, 999999);
        if (nroRemito == 0) break;

        tipo   = leerTipoEntrega();
        sector = leerSector();
        
        // 🔁 Precio y cantidad reutilizan la misma función
        precio = leerEnteroEnRango("Ingrese precio unitario (>0): ", 1, 1000000);
        cant   = leerEnteroEnRango("Ingrese cantidad (>0): ", 1, 100000);

        // Calculo de importe
        float importe = precio * cant;
        if (tipo == 'D') {
            importe += 5000; // recargo domicilio
            contDomicilio++;
        }

        recaudacion += importe;
        contTotal++;

        // Acumular ventas por sector
        if (sector == 'P') ventasP += cant;
        else if (sector == 'G') ventasG += cant;
        else ventasO += cant;

    } while (nroRemito != 0);

    // --------- RESULTADOS ---------
    if (contTotal > 0) {
        printf("\nPorcentaje a domicilio: %.2f %%\n", (float)contDomicilio * 100 / contTotal);
    } else {
        printf("\nNo hubo ventas.\n");
    }

    printf("Recaudacion total: $%.2f\n", recaudacion);

    // Sector con menor ventas (único)
    if (ventasP < ventasG && ventasP < ventasO)
        printf("Sector con menor ventas: Perro\n");
    else if (ventasG < ventasP && ventasG < ventasO)
        printf("Sector con menor ventas: Gato\n");
    else
        printf("Sector con menor ventas: Otro\n");

    return 0;
}

// --------- FUNCIONES AUXILIARES ---------

// 🔁 Función genérica que valida un entero dentro de un rango
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

// Valida tipo entrega D o L (convierte a mayúscula)
char leerTipoEntrega() {
    char c;
    do {
        printf("Ingrese tipo entrega (D domicilio / L local): ");
        scanf(" %c", &c);
        c = toupper(c);
        if (c != 'D' && c != 'L') printf("Error: solo D o L.\n");
    } while (c != 'D' && c != 'L');
    return c;
}

// Valida sector P/G/O (convierte a mayúscula)
char leerSector() {
    char c;
    do {
        printf("Ingrese sector (P perro / G gato / O otro): ");
        scanf(" %c", &c);
        c = toupper(c);
        if (c != 'P' && c != 'G' && c != 'O') printf("Error: solo P, G u O.\n");
    } while (c != 'P' && c != 'G' && c != 'O');
    return c;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PALABRA 100

// Función que convierte una cadena a minúsculas
void convertir_minusculas(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Función que elimina caracteres no alfanuméricos
void limpiar_palabra(char *dest, const char *src) {
    int j = 0;
    for (int i = 0; src[i]; i++) {
        if (isalnum((unsigned char)src[i])) {
            dest[j++] = src[i];
        }
    }
    dest[j] = '\0';
}

// Función que verifica si una palabra es palíndromo
int es_palindromo(const char *str) {
    int izquierda = 0;
    int derecha = strlen(str) - 1;

    while (izquierda < derecha) {
        if (str[izquierda] != str[derecha]) {
            return 0; // No es palíndromo
        }
        izquierda++;
        derecha--;
    }
    return 1;
}

int main() {
    FILE *archivo = fopen("input.txt", "r");
    if (archivo == NULL) {
        perror("No se pudo abrir input.txt");
        return 1;
    }

    char palabra_raw[MAX_PALABRA];
    char palabra_limpia[MAX_PALABRA];
    char palindromo_mas_largo[MAX_PALABRA] = "";
    
    while (fscanf(archivo, "%99s", palabra_raw) == 1) {
        convertir_minusculas(palabra_raw);
        limpiar_palabra(palabra_limpia, palabra_raw);

        if (es_palindromo(palabra_limpia)) {
            if (strlen(palabra_limpia) > strlen(palindromo_mas_largo)) {
                strcpy(palindromo_mas_largo, palabra_limpia);
            }
        }
    }

    fclose(archivo);

    if (strlen(palindromo_mas_largo) > 0) {
        printf("El palíndromo más largo encontrado es: %s\n", palindromo_mas_largo);
    } else {
        printf("No se encontró ningún palíndromo.\n");
    }

    return 0;
}

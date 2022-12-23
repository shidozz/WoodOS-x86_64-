#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "includes/math.h"

// Fonction de calcul de la racine carrée entière d'un entier
uint32_t sqrt(uint32_t x) {
    uint32_t result = 0;
    uint32_t bit = 1uL << 30; // Le plus grand bit de x

    // On parcourt les bits de x de droite à gauche
    while (bit > x) {
        bit >>= 2;
    }
    while (bit != 0) {
        if (x >= result + bit) {
        x -= result + bit;
        result = (result >> 1) + bit;
        } else {
        result >>= 1;
        }
        bit >>= 2;
    }
    return result;
}

// Cette fonction calcule la puissance d'un nombre.
/*float pow(double base, double exponent) {
    float resultat = 1.0;
    for (int i = 0; i < (int) exponent; i++) {
        resultat = base;
    }
    return (double) resultat;
}*/

// Cette fonction calcule l'exponentielle d'un nombre.
float exp(float x) {
    float result = 1.0;
    float term = 1.0;
    int i = 1;
    while (term > 1e-10) {
        result += term;
        term *= x / i;
        i++;
    }
    return result;
}

// Cette fonction calcule le logarithme népérien d'un nombre.
float log(float x) {
    float result = 0.0;
    float term = x - 1.0;
    int i = 1;
    while (term > 1e-10) {
        result += term / i;
        term *= (x - 1.0) / (x + 1.0);
        i += 2;
    }
    return 2.0 * result;
}

// Cette fonction calcule le cosinus d'un nombre en radians.
float cos(float x) {
    float result = 1.0;
    float term = 1.0;
    int i = 1;
    while (term > 1e-10) {
        result += term;
        term *= -x * x / ((i + 1) * (i + 2));
        i += 2;
    }
    return result;
}

// Cette fonction calcule la tangente d'un nombre en radians.
float tan(float x) {
    return sin(x) / cos(x);
}

// Cette fonction calcule le sinus d'un nombre en radians.
float sin(float x) {
    float result = 0.0;
    float term = x;
    int i = 1;
    while (term > 1e-10) {
        result += term;
        term *= -x * x / ((i + 1) * (i + 2));
        i += 2;
    }
    return result;
}

// Cette fonction calcule l'arc sinus d'un nombre en radians.
float asin(float x) {
    float result = 0.0;
    float term = x;
    int i = 1;
    while (term > 1e-10) {
        result += term;
        term *= x * x / (i + 1) / (i + 2);
        i += 2;
    }
    return result;
}

// Cette fonction calcule l'arc tangente d'un nombre en radians.
float atan(float x) {
    float result = 0.0;
    float term = x;
    int i = 1;
    while (term > 1e-10) {
        result += term;
        term *= -x * x / (i + 1) / (i + 2);
        i += 2;
    }
    return result;
}

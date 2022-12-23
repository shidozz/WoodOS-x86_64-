#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "includes/alloc.h"

#define BLOCK_SIZE 16
#define MAX_BLOCKS 1024

struct MemoryBlock {
    size_t size;
    void* data;
    int free;
    int buddy;
    struct MemoryBlock* next;
};

struct MemoryBlock blocks[MAX_BLOCKS];

void* malloc(size_t size) {
    // trouver un bloc de mémoire assez grand
    struct MemoryBlock* current = (struct MemoryBlock*) blocks;
    while (current != NULL && current->size < size) {
        current = current->next;
    }
    
    // s'il n'y a pas de bloc assez grand, en créer un
    if (current == NULL) {
        // trouver la taille de bloc nécessaire
        size_t block_size = BLOCK_SIZE;
        while (block_size < size) {
            block_size *= 2;
        }
        
        // trouver un bloc libre assez grand
        current = (struct MemoryBlock*) blocks;
        while (current != NULL && (current->free == 0 || current->size < block_size)) {
            current = current->next;
        }
        
        // s'il n'y a pas de bloc libre assez grand, en créer un
        if (current == NULL) {
            current = blocks;
            while (current != NULL && current->size != 0) {
                current = current->next;
            }
            if (current == NULL) {
                return NULL; // plus de place dans la zone de mémoire
            }
            current->size = block_size;
            current->data = current + 1; // on déplace le pointeur de données juste après la structure MemoryBlock
        }
        
        // diviser le bloc en deux si nécessaire
        while (current->size > size) {
            struct MemoryBlock* buddy = current + current->size / 2;
            buddy->size = current->size / 2;
            buddy->data = buddy + 1; // on déplace le pointeur de données juste après la structure MemoryBlock
            buddy->free = 1;
            buddy->buddy = current - blocks; // on enregistre l'indice du "buddy" dans le tableau
            current->size /= 2;
            current->free = 0;
            current->buddy = buddy - blocks; // on enregistre l'indice du "buddy" dans le tableau
        }
    }
    
    // marquer le bloc comme occupé
    current->free = 0;
    
    // retourner l'adresse des données
    return current->data;
}

void free(void* ptr) {
    // trouver le bloc de mémoire associé au pointeur
    struct MemoryBlock* current = blocks;
    while (current != NULL && current->data != ptr) {
        current = current->next;
    }
    
    // s'il a été trouvé, mettre à jour les structures de données
    if (current != NULL) {
        current->free = 1;
        
        // fusionner avec le "buddy" si celui-ci est libre
        struct MemoryBlock* buddy = blocks + current->buddy;
        while (buddy->free) {
            // mettre à jour les tailles
            current->size *= 2;
            buddy->size = 0;
            
            // mettre à jour les pointeurs de données
            current->data = current + 1;
            
            // mettre à jour l'indice du "buddy"
            int next_buddy = buddy->buddy;
            current->buddy = next_buddy;
            
            // passer au "buddy" suivant
            buddy = blocks + next_buddy;
        }
    }
}

void* realloc(void* ptr, size_t size) {
    // trouver le bloc de mémoire associé au pointeur
    struct MemoryBlock* current = blocks;
    while (current != NULL && current->data != ptr) {
        current = current->next;
    }
    
    // s'il a été trouvé, allouer une nouvelle zone de mémoire et copier les données
    if (current != NULL) {
        void* new_ptr = malloc(size);
        if (new_ptr != NULL) {
        for (size_t i = 0; i < current->size && i < size; i++) {
            ((char*)new_ptr)[i] = ((char*)ptr)[i];
        }
        free(ptr);
        return new_ptr;
        }
    }
    
    // sinon, retourner NULL
    return NULL;
}

int atoi(const char* str) {
    // Initialiser le résultat et le signe à 1
    int result = 0;
    int sign = 1;
    
    // Si la chaîne commence par un signe moins, mettre à jour le signe et avancer le pointeur de chaîne
    if (*str == '-') {
        sign = -1;
        str++;
    }
    
    // Parcourir la chaîne et convertir chaque caractère en un chiffre
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    
    // Retourner le résultat multiplié par le signe
    return result * sign;
}

char* itoa(int value, char* str, int base) {
    // Vérifier que la base est valide
    if (base < 2 || base > 36) {
        return NULL;
    }
    
    // Initialiser le pointeur de résultat
    char* result = str;
    
    // Si la valeur est négative et que la base est 10, ajouter un signe moins et mettre à jour la valeur
    if (value < 0 && base == 10) {
        *result = '-';
        result++;
        value = -value;
    }
    
    // Convertir la valeur en chaîne de caractères en utilisant la base donnée
    char* ptr = result;
    do {
        *ptr = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base];
        ptr++;
        value /= base;
    } while (value > 0);
    
    // Ajouter le caractère de fin de chaîne et inverser la chaîne de caractères
    *ptr = '\0';
    char* start = result;
    ptr--;
    while (start < ptr) {
        char tmp = *start;
        *start = *ptr;
        *ptr = tmp;
        start++;
        ptr--;
    }
    
    // Retourner le pointeur de résultat
    return result;
}


#define RAND_MAX 32767

static unsigned long int next = 1;

int rand(void) {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void srand(unsigned int seed) {
    next = seed;
}


// Fonction de comparaison utilisée par qsort
int compare(const void* a, const void* b) {
  int x = *(int*)a;
  int y = *(int*)b;
  if (x < y) {
    return -1;
  }
  if (x > y) {
    return 1;
  }
  return 0;
}

void* memcpy(void* dest, const void* src, size_t n) {
  char* d = (char*)dest;
  const char* s = (const char*)src;
  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return dest;
}

void* bsearch(const void* key, const void* base, size_t nmemb, size_t size,
              int (*compar)(const void*, const void*)) {
  const char* p = base;
  size_t l = 0;
  size_t r = nmemb;
  while (l < r) {
    size_t m = l + (r - l) / 2;
    int cmp = compar(key, p + m * size);
    if (cmp == 0) {
      return (void*)p + m * size;
    } else if (cmp < 0) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  return NULL;
}

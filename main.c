#include <stdio.h>
#include <malloc.h>

typedef struct HashMap{
    int* KPtr;
    int* VPtr;
    int size;
} HashMap;

int get_hash(int value){
    int hash;
    hash = (~value);
    return hash - value * 2;
}


void add(HashMap* h, int key, int value){
    unsigned int index, hash;
    hash = get_hash(key);

    for (int i = 0; i < h->size; ++i){
        index = (hash + i) % h->size;
        if (!h->KPtr[index]){
            h->KPtr[index] = key;
            h->VPtr[index] = value;
            return;
        }
    }
}

int get(HashMap* h, int key){
    unsigned int index, hash;
    hash = get_hash(key);

    for (int i = 0; i < h->size; ++i){
        index = (hash + i) % h->size;
        if (h->KPtr[index] == key){
            return h->VPtr[index];
        }
    }
    return INT_MAX;
}


HashMap create(int* keys, int* values, int length){
    HashMap hashMap;
    hashMap.size = length * 2;
    hashMap.KPtr = calloc(hashMap.size, sizeof(int));
    hashMap.VPtr = calloc(hashMap.size, sizeof(int));

    for (int i = 0; i < length; i ++){
        add(&hashMap, keys[i], values[i]);
    }
    return hashMap;
}


void rehash(HashMap* hashMap, int size){
    int oldSize = hashMap->size;
    int keys[hashMap->size];
    int values[hashMap->size];

    for (int i = 0; i < hashMap->size; i++){
        keys[i] = hashMap->KPtr[i];
        values[i] = hashMap->VPtr[i];
        hashMap->KPtr[i] = 0;
        hashMap->VPtr[i] = 0;
    }

    hashMap->size = 2 * size;
    hashMap->KPtr = calloc(hashMap->size, sizeof(int));
    hashMap->VPtr = calloc(hashMap->size, sizeof(int));

    for (int i = 0; i < oldSize; i ++){
        add(hashMap, keys[i], values[i]);
    }
}


int main() {

    int keys[] = {1, 2, 3, 4, 5, 6};
    int values[] = {10, 20, 30, 40, 50, 60};

    HashMap hashMap = create(keys, values, sizeof(values) / sizeof(int));

    for (int i = 0; i < hashMap.size; ++i){
        printf("%d, ", hashMap.VPtr[i]);
    }
    printf("\n");

    rehash(&hashMap, 15);

    for (int i = 0; i < hashMap.size; ++i){
        printf("%d, ", hashMap.VPtr[i]);
    }

    return 0;
}

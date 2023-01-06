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

int main() {
    HashMap hashMap;
    hashMap.size = 10;
    hashMap.KPtr = calloc(hashMap.size, sizeof(int));
    hashMap.VPtr = calloc(hashMap.size, sizeof(int));

    add(&hashMap, 1, 10);
    add(&hashMap, 2, 20);
    add(&hashMap, 3, 30);
    add(&hashMap, 4, 40);
    add(&hashMap, 5, 50);
    add(&hashMap, 6, 60);
    add(&hashMap, 7, 70);
    add(&hashMap, 8, 80);


    for (int i = 0; i < hashMap.size; ++i){
        printf("%d, ", hashMap.VPtr[i]);
    }
    printf("\n");

    printf("%d", get(&hashMap, -1));


    return 0;
}

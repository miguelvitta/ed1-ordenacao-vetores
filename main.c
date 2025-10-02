#include "functions.h"
// Não inclua outras bibliotecas, inclua em functions.h

int main() {
    int v[10] = {10,7,5,9,6,8,4,3,2,1};
    RadixSort(v,10);
    for(int i=0;i<10;i++){
        printf("%d ",v[i]);
    }

    return 0;
}
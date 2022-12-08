#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARR 10000

void putArr(int a[], int n){
    for (int i = 0; i<n; i++){
        printf("%8d", a[i]);
    }
}

int readFileTxt(int a[], char *nameFile){
    FILE *f;
    f = fopen(nameFile, "r");
    if (f == NULL){
        printf("\nloi mo file!");
        exit(1);
    }
    int n = 0; //biến chạy
    while (fscanf(f, "%d", &a[n++]) != EOF){
    }
    fclose(f);
    return n - 1;
}

void writeFileBin(int a[], int n, char *nameFile){
    FILE *f;
    f = fopen(nameFile, "w");
    fwrite(a, sizeof(a[0]), n, f);
    fclose(f);
}

void swap(int *x, int *y){
    int tg = *x;
    *x = *y;
    *y = tg;
}

void selectionSort(int a[], int n){
    int i, j, iMin;
    for (i = 0; i<n-1;i++){
        iMin = i;
        for (j = i+1; j<n;j++){
            if (a[j] < a[iMin]){
                iMin = j;
            }
        }
        if (iMin != i){
            swap(&a[iMin], &a[i]);
        }
    }
}

int nhapData(int a[], int n){
    int k;
    printf("vui long nhap so luong so can them: "); scanf("%d", &k);
    for (int i = n; i<n+k; i++){
        printf("nhap so thu %d: ", i-n+1); scanf("%d", &a[i]);
    }
    return n+k;
}

int main()
{
    //phần a
    int a[MAX_ARR];
    int n = readFileTxt(a, "day_so_nguyen.txt");
    selectionSort(a, n);
    writeFileBin(a, n, "day_so_nguyen.bin");


    //phần b
    int n1 = nhapData(a, n);
    selectionSort(a, n1);
    writeFileBin(a, n1, "day_so_nguyen.bin");
    putArr(a, n1);

    return 0;
}

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

int readFileBin(int a[], char *nameFile){
    FILE *f;
    f = fopen(nameFile, "r");
    if (f == NULL){
        printf("\nloi mo file!");
        exit(1);
    }
    int n=0;
    int num;

    fseek(f, 0, SEEK_END);//đưa con trỏ về cuối file

    n = ftell(f)/sizeof(int);//tính số lượng số

    fseek(f, 0, SEEK_SET);//đưa trở về đầu file

    fread(a, sizeof(int), n, f);//đọc file vào a

    //putArr(a, n);//in ra màn hình
    fclose(f);
    return n;
}

void suLiDuLieu(int a[], int n , char *nameFile){
    FILE *f;
    f = fopen(nameFile, "w");
    int min, max, demChan = 0, demLe = 0;

    min = a[0];
    max = a[0];
    for (int i = 0; i<n; i++){
        if (a[i] < min){
            min = a[i];
        }
        if (a[i] > max){
            max = a[i];
        }
        if (a[i]%2==0)
            demChan++;
        else demLe++;
    }

    fprintf(f, "so luong cac phan tu la: %d\n", n);
    fprintf(f, "so lon nha la: %d\n", max);
    fprintf(f, "so nho nhat la: %d\n", min);
    fprintf(f, "so luong cac so chan la: %d\n", demChan);
    fprintf(f, "so luong cac so le la: %d\n", demLe);

    fclose(f);
}

int main()
{
    int a[MAX_ARR];
    int n = readFileTxt(a, "day_so_nguyen.txt");
    writeFileBin(a, n, "day_so_nguyen.bin");

    int b[MAX_ARR];
    int n1 = readFileBin(b, "day_so_nguyen.bin");
    suLiDuLieu(b, n1, "ket_qua.txt");
    return 0;
}

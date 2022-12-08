#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARR 10000
#define MAX_STR 255

struct SINHVIEN{
    char hoten[MAX_STR];
    int namsinh;
    char gioitinh[MAX_STR];
    float dtb;//điểm trung bình
};

typedef struct SINHVIEN sinhvien;

sinhvien sv[1000];
int n;

void writeFile(){
    FILE *f = fopen("Lop_tin13.dat", "w");
    fprintf(f, "| STT |         HO VA TEN         | NAM SINH | GIOI TINH | DTB |\n");//5 27 10 11 5
    for(int i=0; i<n;i++){
        fprintf(f, "|%5d|%27s|%10d|%11s|%5.2f|\n", i, sv[i].hoten, sv[i].namsinh, sv[i].gioitinh, sv[i].dtb);
    }
    fclose(f);
}

void ghi_ds(){
    int chon;
    printf("nhap so luong sinh vien can ghi: "); scanf("%d", &n);
    for (int i = 0;i<n;i++){
        fflush(stdin);
        printf("\nnhap du lieu cho sinh vien %d\n", i+1);

        printf("nhap ho va ten: ");fflush(stdin); gets(sv[i].hoten);
        printf("nhap nam sinh: "); scanf("%d", &sv[i].namsinh);
        do{
            printf("1: nu\n");
            printf("2: nam\n");
            printf("lua chon gioi tinh: "); scanf("%d", &chon);
        }
        while (chon != 1 && chon != 2);
        if (chon == 1)
            strcpy(sv[i].gioitinh, "nu");
        else strcpy(sv[i].gioitinh, "nam");
        printf("nhap diem trung binh: "); scanf("%f", &sv[i].dtb);
    }
    writeFile();
}

void tim_sv(){
    char tenSv[MAX_STR];
    FILE *f = fopen("Lop_tin13.dat", "r");
    printf("nhap ho va ten de tim sinh vien: "); gets(tenSv);
    printf("\n");
    for(int i=0; i<n;i++){
        //fprintf(f, "|%5d|%27s|%10d|%11s|%5.2f|\n", i, sv[i].hoten, sv[i].namsinh, sv[i].gioitinh, sv[i].dtb);
        if (strstr(strlwr(sv[i].hoten), strlwr(tenSv)) != NULL){
            printf("|%5d|%27s|%10d|%11s|%5.2f|\n", i, sv[i].hoten, sv[i].namsinh, sv[i].gioitinh, sv[i].dtb);
        }
    }
    fclose(f);
}

int main()
{

    ghi_ds();
    tim_sv();
    return 0;
}


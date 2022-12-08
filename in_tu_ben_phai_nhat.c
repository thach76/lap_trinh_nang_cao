#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARR 10000
#define MAX_STR 1000

int demDauCach(char *s){
    int len = strlen(s);
    int dem = 0;
    for (int i = 0; i<len;i++){
        if (s[i] == ' ') dem ++;
    }
    return dem;
}

int suLyChuoi(char *nameFileIn, char *nameFileOut){
    FILE *f, *f1;
    f = fopen(nameFileIn, "r");
    f1 = fopen(nameFileOut, "w");
    if (f == NULL){
        printf("\nloi mo file!");
        exit(1);
    }
    char s[MAX_STR];
    int n = 0; //biến chạy
    int soLuongDauCach;
    while (fgets(s, sizeof(s), f) != NULL){
        n = 0;
        soLuongDauCach = demDauCach(s);
        if (soLuongDauCach == 0){
            fprintf(f1, "%s\n", s);
        }
        else{
            for (int i = 0; i<strlen(s); i++){
                fprintf(f1, "%c", s[i]);
                if(s[i] == ' ' && n == 0){
                    fprintf(f1, "\n");
                    n++;
                }
            }
        }
    }
    fclose(f);
    fclose(f1);
    return n - 1;
}

int main()
{
    suLyChuoi("input.txt", "output.txt");

    return 0;
}

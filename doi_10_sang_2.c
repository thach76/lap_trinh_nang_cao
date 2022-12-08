#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_ARR 10000

struct LINKLIST{
    int data;
    struct LINKLIST *next;
};

typedef struct LINKLIST *node;
typedef char kieudata;

/////////////////////////////STACK/////////////////////////////

node initStack(){
    return NULL;
}

node createNode(kieudata value){
    node temp = (node)malloc(sizeof(struct LINKLIST));
    temp->data = value;
    temp->next = NULL;
    return temp;
}

//cho vào cuối
node push(node head, kieudata value){
    node temp = createNode(value);
    if (head == NULL){
        head = temp;
    }
    else{
        node p;
        for(p = head; p->next!=NULL; p=p->next){
        }
        p->next = temp;
    }
    return head;
}

//xóa ở cuối
node pop(node head){
    if (head == NULL){
        printf("khong co gi de xoa!\n");
    }
    else if(head->next == NULL){
        free(head->next);
        head = NULL;
    }
    else{
        node p;
        for(p = head; p->next->next!=NULL; p=p->next){
        }
        free(p->next);
        p->next = NULL;
    }
    return head;
}

//lấy giá trị ở đỉnh stack(cuối dslk)
kieudata peekStack(node head){
    node p;
    for(p = head; p->next!=NULL; p=p->next){
    }
    return p->data;
}

//1 là rỗng
int isEmpty(node head){
    if (head == NULL)
        return 1;
    return 0;
}

////////////////////////////FILE/////////////////////////////

int readFile(int a[], char *nameFile){
    FILE *f;
    f = fopen(nameFile, "r");
    if (f == NULL){
        printf("\nloi mo file!");
        return 0;
    }
    int n = 0; //biến chạy
    while (fscanf(f, "%d", &a[n++]) != EOF){
    }
    return n - 1;
}

void writeFile(char bin[MAX_ARR][255], int n, char *nameFile){
    FILE *f;
    f = fopen(nameFile, "w");
    for (int i = 0; i<n; i++){
        fprintf(f, "%20s\n", bin[i]);
    }
    fclose(f);
}

//in ra màn hình stack
void putS(node head){
    node p;
    for(p = head; p!=NULL; p=p->next){
        printf("%d", p->data);
    }
}

///////////////////////ĐỔI 10 SANG 2//////////////////////
int IntToChar(int n){
    if (n<0){
        return 48 - n%2;
    }
    else{
        return n%2 + 48;//số 0 có mã asci là 48
    }
}

void DecToBin(int dec, char *bin){
    node stack = initStack();
    int temp = dec, i = 0;
    do{
        stack = push(stack, IntToChar(temp));
        temp/=2;
    }
    while (temp != 0);

    //sử lý sô âm
    if (dec < 0){
        stack = push(stack, '-');
    }

    do{
        bin[i++] = peekStack(stack);
        stack = pop(stack);
    }
    while (isEmpty(stack)!=1);
}

void doi10(int a[], int n, char bin[MAX_ARR][255]){
    for (int i = 0; i<n; i++){
        DecToBin(a[i], bin[i]);
    }
}

int main(){
    char bin[MAX_ARR][255];
    int a[MAX_ARR];
    int n = readFile(a, "1_000.txt");
    doi10(a, n, bin);
    writeFile(bin, n, "output.txt");
    return 0;
}

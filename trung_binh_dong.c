#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_ARR 10000

struct LINKLIST{
    int data;
    struct LINKLIST *next;
};

typedef struct LINKLIST *node;
typedef int kieudata;

/////////////////////////////QUEUE/////////////////////////////

node initQueue(){
    return NULL;
}

node createNode(kieudata value){
    node temp = (node)malloc(sizeof(struct LINKLIST));
    temp->data = value;
    temp->next = NULL;
    return temp;
}

//cho vào cuối
node enQueue(node head, kieudata value){
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

//xóa ở đầu
node deQueue(node head){
    if (head == NULL){
        printf("khong co gi de xoa!\n");
    }
    else{
        head = head->next;
    }
    return head;
}

//lấy giá trị ở đầu queue
kieudata peekHeadQueue(node head){
    return head->data;
}

//lấy giá trị ở cuối queue(cuối dslk)
kieudata peekTailQueue(node head){
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

void writeFile(float a[], int n, char *nameFile){
    FILE *f;
    f = fopen(nameFile, "w");
    for (int i = 0; i<n; i++){
        fprintf(f, "%10.2f", a[i]);
    }
    fclose(f);
}

//in ra màn hình stack
void putS(node head){
    node p;
    for(p = head; p!=NULL; p=p->next){
        printf("%4d", p->data);
    }
}

void trungBinhDong(int a[], int n, int k, float tbd[]){
    node queue = initQueue();
    int sum = 0;
    float temp;
    for (int i = 0; i<k; i++){
        queue = enQueue(queue, a[i]);
        sum+=a[i];
    }

    tbd[0] = (float) sum/k;

    for (int i = k; i<n; i++){
        sum -= peekHeadQueue(queue);
        queue = enQueue(queue, a[i]);
        queue = deQueue(queue);
        sum += peekTailQueue(queue);
        temp = (float) sum/k;
        tbd[i-k+1] = temp;
    }
}

int main()
{
    int a[MAX_ARR];
    float tbd[MAX_ARR];
    int n = readFile(a, "input.txt");
    int k = 4;
    trungBinhDong(a, n, k, tbd);
    writeFile(tbd, n-k+1, "output.txt");
    return 0;
}

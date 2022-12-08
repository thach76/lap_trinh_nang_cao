//bảng băm
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARR 1000
#define MAX_STR 255
#define M 1000 //số phần tử trong bảng băm

typedef int datatype;

struct LINKLIST{
    datatype data;
    struct LINKLIST *next;
};

typedef struct LINKLIST *node;

//////////////////////DSLK//////////////////////////////////////////////////////
//tạo 1 node
node createNode(datatype value){
    node temp = malloc(sizeof(struct LINKLIST));
    temp->data = value;
    temp->next = NULL;
    return temp;
}

//thêm vào cuối
node addTail(node head, datatype value){
    node temp = createNode(value);
    if (head == NULL)
        head = temp;
    else{
        node p = head;
        for (; p->next!=NULL;p=p->next);
        p->next = temp;
    }
    return head;
}

//xóa ở cuối
node delTail(node head){
    if (head == NULL){
        //printf("khong co gi de xoa!!");
    }
    else if (head->next == NULL){
        head = NULL;
    }
    else{
        node p = head;
        for (; p->next->next!=NULL;p=p->next);
        p->next = NULL;
    }
    return head;
}

//xóa đầu
node delHead(node head){
    head = head->next;
    return head;
}

//xóa 1 phần tử có giá trị value
node delValue(node head, datatype value){
    //không có gì để xóa
    if (head == NULL){
        //printf("khong co gi de xoa!!");
    }
    // else if (head->next == NULL){
    //     if (head->data == value){
    //         head = delHead(head);
    //     }
    //     else{
    //         printf("\nkhong co so %d trong bang bam", value);
    //     }
    // }
    else{
        int n = 0;
        node p = head;
        node q = NULL;
        //thoát khi gặp số liệu có value hoặc chạy hết
        while (p != NULL){
            if (p->data == value){
                break;
            }
            q=p;
            p=p->next;
        }
        // for (; p->next!=NULL && p->data == value;p=p->next)
        //     q=p;
        // if (q == NULL){
        //     printf("\nkhong co so %d trong bang bam", value);
        // }
        // //xóa ở đầu
        // else
        if (q == NULL){
            n++;
            head = delHead(head);
        }
        //xóa ở cuối
        else if (q->next == NULL){
            n++;
            head = delTail(head);
        }
        //xóa ở giữa
        else{
            //xóa mất phần tử p
            //q->next = p->next->next;
            n++;
            q -> next = p -> next;
            p -> next = NULL;
            //p->next = NULL;
        }
        if (n==0){
            printf("\nkhong co so %d trong bang bam", value);
        }
    }
    return head;
}

//in ra dslk
void putList(node head){
    node p = head;
    for (; p!=NULL;p=p->next){
        printf("%8d", p->data);
    }
}

/////////////////////////BẢNG BĂM (HASH TABLE)//////////////////////////////////
//khai báo bảng băm
node hashTable[M];

//khởi tạo bảng băm
void initHash(){
    for(int i = 0;i<M;i++){
        hashTable[i] = NULL;
    }
}

//tính toán chỉ số băm
int hashFunct(datatype value){
    return (value % M);
}

//chèn thêm 1 phần tử vào bảng băm
void inSert(datatype value){
    int index = hashFunct(value);//tính chỉ số hashFunct

    hashTable[index] = addTail(hashTable[index], value);
}

//loại 1 phần tử trong bảng băm
void reMove(datatype value){
    int index = hashFunct(value);//tính chỉ số hashFunct

    hashTable[index] = delValue(hashTable[index], value);
}

//xóa tất cả các phần tử trong bảng băm
void clear(){
    for (int i=0;i<M;i++){
        while(hashTable[i]!=NULL){
            hashTable[i] = delHead(hashTable[i]);
        }
    }
}

//in ra bảng băm
void traver(){
    printf("\nbang bam: ");
    for (int i=0;i<M;i++){
        if (hashTable[i] != NULL){
            printf("\n%d: ", i);
            putList(hashTable[i]);
        }

    }
}

//Tìm kiếm một giá trị trả về có hay không
//1 là có //0 là không
int search(int value){
    int index = hashFunct(value);//tính chỉ số hashFunct

    node p = hashTable[index];
    if (p == NULL){
        return 0;
    }
    for (; p!=NULL;p=p->next){
        if (p->data == value){
            return 1;
        }
    }
    return 0;
}

void menu(){
//     Thêm một nút vào bảng băm
// • Xóa một nút trong bảng băm
// • Xóa toàn bộ bảng băm
// • Duyệt bảng băm
// • Tìm kiếm
    printf("\n\t\tMENU");
    printf("\n1: Them mot nut vao bang bam");//inSert
    printf("\n2: Xoa mot nut trong bang bam");//remove
    printf("\n3: Xoa toan bo bang bam bang bam");//clear
    printf("\n4: Duyet bang bam");//traver
    printf("\n5: Tim kiem");//search
    printf("\n6: Thoat");//break
}

int main()
{
    int chon, value;
    menu();
    do{
        printf("\nvui long chon: ");
        scanf("%d", &chon);
        switch(chon){
            case 1:
                printf("\nnhap gia tri can them: ");
                scanf("%d", &value);
                inSert(value);
                break;
            case 2:
                printf("\nnhap gia tri can xoa: ");
                scanf("%d", &value);
                reMove(value);
                break;
            case 3:
                printf("\nda xoa toan bo bang bam");
                clear();
                break;
            case 4:

                traver();
                break;
            case 5:
                printf("\nnhap gia tri can tim kiem: ");
                scanf("%d", &value);
                if (search(value) == 1){
                    printf("\nco gia tri %d trong bang bam", value);
                }
                else{
                    printf("\nkhong gia tri %d trong bang bam", value);
                }
                break;
            case 6:
                printf("\nDa thoat");
                break;
        }
    }
    while (chon !=6);
    return 0;
}

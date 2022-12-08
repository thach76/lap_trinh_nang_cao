//kiểm tra xem chuỗi có sử dụng đúng cú pháp dấu ngoặc không
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CHUOI 1000

////////////////////////////////CẤU TRÚC DỮ LIỆU NGĂN XẾP//////////////////////////////
typedef char data_type_linklist;

struct LinkList{
    data_type_linklist data;
    struct LinkList *pNext;
};

typedef struct LinkList *node;

//tạo một node mới
node createNode(data_type_linklist value){
    node temp = (node) malloc(sizeof(struct LinkList));
    temp->data = value;
    temp->pNext = NULL;
    return temp;
}

//thêm một phần tử vào stack
//thêm vào cuối
node push(node head, data_type_linklist value){
    node temp = createNode(value);
    if (head == NULL){
        head = temp;
    }
    else{
        node p = head;
        while(p->pNext != NULL){
            p = p->pNext;
        }
        p->pNext = temp;
    }
    return head;
}


//lấy phần tử ra khỏi stack
//xóa node cuối
node pop(node head){
    if (head == NULL || head->pNext == NULL){
        free(head->pNext);
        head = NULL;
    }
    else {
        node p = head;
        while(p->pNext->pNext != NULL){
            p = p->pNext;
        }
        free(p->pNext);
        p->pNext = NULL;
    }
    return head;
}

//lấy giá trị phần tử đầu
data_type_linklist peekHeadStack(node head){
    //chuỗi rỗng
    if (head == NULL){
        //trả về char min tức là phần tử nhỏ nhất trong kiểu char
        return CHAR_MIN;
    }
    return head->data;
}

//lấy giá trị cuối
data_type_linklist peekTailStack(node head){
    //chuỗi rỗng
    if (head == NULL){
        //trả về char min tức là phần tử nhỏ nhất trong kiểu char
        return CHAR_MIN;
    }
    node p = head;
    while(p->pNext != NULL){
        p = p->pNext;
    }
    return p->data;
}

//in danh sách liên kết
void getStack(node head){
    if (head == NULL){
        return;
    }
    for (node p = head; p != NULL; p = p->pNext){
        printf("%2c", p->data);
    }
}

//giá trị trả về
//1 rỗng
//0 không rỗng
int checkEmptyStack(node head){
    if (head == NULL) return 1;
    return 0;
}

////////////////////////////////LÀM VIỆC VỚI FILE//////////////////////////////
//đọc 1 chuỗi từ file
void readFile(char s[], char nameFile[]){
    FILE *f;
    f = fopen(nameFile, "r");
    if (f == NULL){
        printf("loi mo file");
        exit(1);
    }
    fgets(s, MAX_CHUOI, f);
    fclose(f);
}

//////////////////////////////// KIỂM TRA XEM CHUỖI CÓ DẤU NGOẶC ĐÚNG HAY KHÔNG/////////////////////////////
//chuỗi s cần kiểm tra
//giá trị trả về
//1 chuỗi có ngoặc đúng
//0 chuỗi không có ngoặc đúng
int checkBrackets(char s[]){
    node stack = NULL;
    int lengS = strlen(s);
    for (int i = 0; i<lengS; i++){
        if (s[i] == '(' || s[i] == '[' || s[i] == '{'){
            stack = push(stack, s[i]);
        }
        if (s[i] == ')' || s[i] == ']' || s[i] == '}'){
            //lấy giá trị cuối stack
            char c = peekTailStack(stack);
            //nếu chuỗi rỗng mà đã có ngoặc đóng -> thoát
            //( không  đi chung với ), [ không đi chung với ], { không đi chung với }
            if (checkEmptyStack(stack) == 1 || ((c == '(' && s[i] != ')') || (c == '[' && s[i] != ']') || (c == '{' && s[i] != '}') )){
                //chuỗi không có ngoặc đúng
                return 0;
            }
            //phần tử cuối stack mà là (, [, {
            //( đi chung với ), [ đi chung với ], { đi chung với }
            else if ((c == '(' && s[i] == ')') || (c == '[' && s[i] == ']') || (c == '{' && s[i] == '}') ){
                stack = pop(stack);
            }
        }
    }
    //chuỗi vẫn còn phần tử -> vẫn còn ngoặc
    if (checkEmptyStack(stack) == 0){
        //chuỗi không có ngoặc đúng
        //ngoặc sai
        return 0;
    }
    return 1;
}

int parser(char s[]){
    int lengS = strlen(s);
    node stack = NULL;
    for (int i = 0; i<lengS; i++){
        switch (s[i]){
        case '(':
        case '[':
        case '{':
            stack = push(stack, s[i]);
            break;
        case ')':
            if (peekTailStack(stack) == '(')
                stack = pop(stack);
            else
                //ngoặc sai
                return 0;
            break;
        case ']':
            if (peekTailStack(stack) == '[')
                stack = pop(stack);
            else
                //ngoặc sai
                return 0;
            break;
        case '}':
            if (peekTailStack(stack) == '{')
                stack = pop(stack);
            else
                //ngoặc sai
                return 0;
            break;
        }
    }
    //chuỗi vẫn còn phần tử -> vẫn còn ngoặc
    if (checkEmptyStack(stack) == 0){
        //chuỗi không có ngoặc đúng
        //ngoặc sai
        return 0;
    }
    return 1;

}

/////////////////////////////////////HÀM CHÍNH/////////////////////////////////////////////
int main()
{
    node head = NULL;
    char s[MAX_CHUOI];
    readFile(s, "string.txt");
    if (parser(s) == 1){
        printf("\nchuoi co dau ngoac dung");
    }
    else{
        printf("\nchuoi co dau ngoac sai");
    }
    return 0;
}




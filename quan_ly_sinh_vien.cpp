#include <stdio.h>
#include <stdlib.h> //hàm exit()
#include <string.h> //sử lí với chuỗi
#include <windows.h> //lệnh xóa màn hình
#include <time.h> //tính thời gian tìm kiếm

/*
    QUẢN LÍ DANH SÁCH SINH VIÊN
    1. NHẬP LIỆU( nhập xong tự động in vào file)
    2. NHẬP LẠI TỪ ĐẦU (xóa toàn bộ dữ liệu cũ và nhập lại)
    3. TÌM KIẾM SINH VIÊN (tìm kiếm theo họ tên, mã sinh viên)
    4. SẮP XẾP SINH VIÊN (sắp xếp theo họ tên(a->z), điểm tb(cao->thấp), năm sinh(già->trẻ))
    5. THOAT
*/


//tạo kiểu dữ liệu sinh viên
struct SINHVIEN{
    char HoTen[30];
    char MaSV[15];
    int NamSinh;
    float Dtb; //điểm trung bình
    unsigned char HanhKiem; // hạnh kiểm
};


//khai báo biến toàn cục
struct SINHVIEN person; //biến kiểu struct


//khai báo các hàm dùng trong chương trình
void xoa_Xuong_Dong(char *str);
void in_vao_FILE_txt(FILE *f);
void in_vao_FILE_bin(FILE *fbin);
void nhap_lieu(FILE *f);
void start_deco(FILE *f);
int tim_du_lieu(char Ten[], char TimTen[]);
void tim_kiem(FILE *f);
void tim_kiem_ho_ten(FILE *f);
void tim_kiem_masv(FILE *f);
void sap_xep(FILE* f, FILE* fxuat);
void sap_xep_ho_ten(FILE* fbin, FILE* fxuat);
void sap_xep_masv(FILE* fbin, FILE* fxuat);
void home_page();
void lua_chon();
void tieu_de();


//xóa xuống dòng trong chuỗi (nhap_lieu, tim_kiem)
void xoa_Xuong_Dong(char *str) {
    //Lấy độ dài chuỗi str
    size_t len = strlen(str);

    str[len - 1] = 0; //Thay thế ký tự xuống dòng bằng kí tự trống nếu tìm thấy.
}


//in vào file (chon 1 || chon 2)
void in_vao_FILE_txt(FILE *f){
    fflush(stdin); //xóa bộ nhớ đệm
    fprintf(f, "|%-30s|%-16s|%-10d|%-9f|", person.HoTen, person.MaSV, person.NamSinh, person.Dtb);//in vào file txt
    switch(person.HanhKiem){
        case 1:
            fprintf(f, "Tot        |\n");
            break;
        case 2:
            fprintf(f, "Kha        |\n");
            break;
        case 3:
            fprintf(f, "Trung Binh |\n");
            break;
        case 4:
            fprintf(f, "Yeu        |\n");
            break;
    }
}

void in_vao_FILE_bin(FILE* fbin){
    fwrite(&person, sizeof(person), 1, fbin); // in vào file nhị phân( dành cho tìm kiếm )
}

//cho user nhập dữ liệu(chọn 1)
void nhap_lieu(FILE* f){
    fflush(stdin); //xóa bộ nhớ đệm

    printf("                                 --------------                               \n");

    printf("nhap ho va ten: "); fgets(person.HoTen, sizeof(person.HoTen), stdin);
    xoa_Xuong_Dong(person.HoTen);

    printf("nhap ma sinh vien:"); fgets(person.MaSV, sizeof(person.MaSV), stdin);
    xoa_Xuong_Dong(person.MaSV);

    printf("nhap nam sinh: "); scanf("%d", &person.NamSinh);

    printf("nhap diem trung binh: "); scanf("%f", &person.Dtb);

    printf("1. Tot\n2. Kha\n3. Trung Binh\n4. Yeu\n");
    do{
        printf("nhap so tuong ung voi hanh kiem: "); scanf("%hhd", &person.HanhKiem);
    }
    while(person.HanhKiem < 1 || person.HanhKiem > 4);

    printf("                                 --------------                               \n");
}

//trang trí mở đầu file(chọn 2)
void start_deco(FILE* f){
    fprintf(f, "DANH SACH CAC SINH VIEN K14\n");
    fprintf(f, "----------------------------------------------------------------------------------\n");
    fprintf(f, "|           Ho va Ten          |  Ma Sinh Vien  | Nam Sinh | Diem tb | Hanh Kiem |\n");
    fprintf(f, "|------------------------------|----------------|----------|---------|-----------|\n");
}

//in ra tiêu đề
void tieu_de(){
    printf("----------------------------------------------------------------------------------\n");
    printf("|           Ho va Ten          |  Ma Sinh Vien  | Nam Sinh | Diem tb | Hanh Kiem |\n");
    printf("|------------------------------|----------------|----------|---------|-----------|\n");
}

//tìm kiếm               (chọn 3)
void tim_kiem(FILE* f){
    int chon;
    printf("1. tim kiem theo ho ten\n");
    printf("2. tim kiem theo ma sinh vien\n");
    printf("3. quay tro lai\n");
    do{
        printf("nhap lua chon: "); scanf("%d", &chon);
    }
    while(chon < 1 || chon > 3);
    switch(chon){
        case 1:
            system("cls");
            home_page();
            tim_kiem_ho_ten(f);
            break;
        case 2:
            system("cls");
            home_page();
            tim_kiem_masv(f);
            break;
        case 3:
            system("cls");
            home_page();
            break;
    }
}


//tìm kiếm dữ liệu có trong tên cần tìm hay không
//trả về 1 nếu tìm thấy, trả về 0 nếu ko thấy
int tim_du_lieu(char Ten[], char TimTen[]){
    strcpy(Ten, strlwr(Ten));
    strcpy(TimTen, strlwr(TimTen));
        if (strstr(Ten, TimTen) != NULL){
            return 1;
        }
        else return 0;
}

//tìm kiếm theo họ tên      (chon 3 -> chọn 1)
//biến file là biến nhị phân
void tim_kiem_ho_ten(FILE* f){
    clock_t start_t, end_t; //khai báo bắt đầu, kết thúc thời gian chạy
    char hoTen[30], timHoTen[30];
    int n = 0; //bien dem

    fflush(stdin); //xóa bộ nhớ đệm

    printf("nhap ten can tim: "); fgets(timHoTen, sizeof(timHoTen), stdin);
    xoa_Xuong_Dong(timHoTen);

    start_t = clock();
    while (fread(&person, sizeof(person), 1, f) != 0){
        strcpy(hoTen, person.HoTen);
        if (tim_du_lieu(hoTen, timHoTen) == 1){
            if (n == 0){
                printf("danh sach sinh vien can tim la: \n");
                tieu_de();
            }
            printf("|%-30s|%-16s|%-10d|%-9f|", person.HoTen, person.MaSV, person.NamSinh, person.Dtb);
            switch(person.HanhKiem){
                case 1:
                    printf("Tot        |\n");
                    break;
                case 2:
                    printf("Kha        |\n");
                    break;
                case 3:
                    printf("Trung Binh |\n");
                    break;
                case 4:
                    printf("Yeu        |\n");
                    break;
            }
            n++;
        }
    }
    end_t = clock();

    if (n == 0){
        printf("khong tim thay \"%s\" trong danh sach Ho va Ten\n", timHoTen);
    }
    else {
        printf("\ntim %d ket qua trong %f giay\n", n, (double)(end_t - start_t)/CLOCKS_PER_SEC);
    }
}

//tìm kiếm theo mã sinh viên(chọn 3 -> chọn 2)
//biến file là biến nhị phân
void tim_kiem_masv(FILE* f){
    clock_t start_t, end_t; //khai báo bắt đầu, kết thúc thời gian chạy
    char maSinhVien[15], timMaSV[30];
    int n = 0; //bien dem

    fflush(stdin); //xóa bộ nhớ đệm

    printf("nhap ma sinh vien can tim: "); fgets(timMaSV, sizeof(timMaSV), stdin);
    xoa_Xuong_Dong(timMaSV);
    start_t = clock();
    while (fread(&person, sizeof(person), 1, f) != 0){
        strcpy(maSinhVien, person.MaSV);
        if (tim_du_lieu(maSinhVien, timMaSV) == 1 ){
            if (n == 0){
                printf("danh sach sinh vien can tim la: \n");
                tieu_de();
            }
            printf("|%-30s|%-16s|%-10d|%-9f|", person.HoTen, person.MaSV, person.NamSinh, person.Dtb);
            switch(person.HanhKiem){
                case 1:
                    printf("Tot        |\n");
                    break;
                case 2:
                    printf("Kha        |\n");
                    break;
                case 3:
                    printf("Trung Binh |\n");
                    break;
                case 4:
                    printf("Yeu        |\n");
                    break;
            }
            n++;
        }
    }
    end_t = clock();
    if (n == 0){
        printf("khong tim thay \"%s\" trong danh sach ma sinh vien\n", timMaSV);
    }
    else {
        printf("\ntim %d ket qua trong %f giay\n", n, (double)(end_t - start_t)/CLOCKS_PER_SEC);
    }
}


//sắp xếp
void sap_xep(FILE* fbin, FILE* fxuat){
    int chon;
    printf("1. sap xep theo ho ten\n");
    printf("2. sap xep theo ma sinh vien\n");
    printf("3. quay tro lai\n");
    do{
        printf("nhap lua chon: "); scanf("%d", &chon);
    }
    while(chon < 1 || chon > 3);
    switch(chon){
        case 1:
            system("cls");
            home_page();
            sap_xep_ho_ten(fbin, fxuat);
            break;
        case 2:
            system("cls");
            home_page();
            sap_xep_masv(fbin, fxuat);
            break;
        case 3:
            system("cls");
            home_page();
            break;
    }
}


//sắp xếp theo họ tên
//f là biến đọc kiểu bin
//fxuat là biến ghi kiểu txt
void sap_xep_ho_ten(FILE* fbin, FILE* fxuat){
    clock_t start_t, end_t; //khai báo bắt đầu, kết thúc thời gian chạy
    char ghiFile[1000][30]; //biến ghi giữ liệu từ file
    int n = 0; //biến đếm
    start_t = clock();
    while (fread(&person, sizeof(person), 1, fbin) != 0){
        strcpy(ghiFile[n], person.HoTen);
        //strcpy(hoTen, strlwr(hoTen));
        //strcpy(timHoTen, strlwr(timHoTen));
        n++;
    }
    //buble_shot(ghiFile, i);
    int dem, dem2;
    char tg[30];
    for (dem=0; dem<n-1; dem++)
        for (dem2=0; dem2<n-1-dem;dem2++)
            if (strcmp(ghiFile[dem2] , ghiFile[dem2+1]) > 0){ //a[j] > a[j+1]
                strcpy(tg, ghiFile[dem2]);
                strcpy(ghiFile[dem2], ghiFile[dem2+1]);
                strcpy(ghiFile[dem2+1], tg);
            }

    for (int i=0; i<n; i++){
        printf("%s\n", ghiFile[i]);
    }
        //if (strstr(hoTen, timHoTen) != NULL){
            //printf("----------------------------------------------------------------------------------\n");

            fprintf(fxuat, "\n|%-30s|%-16s|%-10d|%-9f|", person.HoTen, person.MaSV, person.NamSinh, person.Dtb);
            switch(person.HanhKiem){
                case 1:
                    fprintf(fxuat, "Tot        |\n");
                    break;
                case 2:
                    fprintf(fxuat, "Kha        |\n");
                    break;
                case 3:
                    fprintf(fxuat, "Trung Binh |\n");
                    break;
                case 4:
                    fprintf(fxuat, "Yeu        |\n");
                    break;
            //}
        }

    end_t = clock();
    printf("\nxap xep trong trong %f giay\n", (double)(end_t - start_t)/CLOCKS_PER_SEC);
}

//sắp xếp theo mã sinh viên
void sap_xep_masv(FILE* fbin, FILE* fxuat){
}
//deco đầu chương trình (main)
void home_page(){
    printf("----------------------------------------------------------------------------------\n");
    printf("                 DAY LA CHUONG TRINH QUAN LI DANH SACH SINH VIEN\n");
    printf("                                                   by ThachCute\n");
    printf("----------------------------------------------------------------------------------\n");

}

//lựa chọn (main)
void lua_chon(){
    printf("----------------------------------------------------------------------------------\n");
    printf("vui long nhap lua chon!!!\n");
    printf("1. them mot du lieu sinh vien\n");
    printf("2. nhap lai(nhap lai danh sach tu dau)\n");
    printf("3. tim kiem\n");
    printf("4. sap xep\n");
    printf("5. thoat\n");
}

int main(){
    system("cls");
    int chon;

    FILE *f, *fbin;//file nhập txt và bin
    FILE *fxuat; //file xuất dữ liệu đã xử lý

    home_page();

    do{
        lua_chon();
        do{
            printf("nhap lua chon: "); scanf("%d", &chon);
        }
        while(chon < 1 || chon > 5);

        switch(chon){
            case 1:
                system("cls");
                home_page();
                f = fopen("sinhvien.txt", "a");
                fbin = fopen("sinhvien.bin", "ab");
                nhap_lieu(f);
                in_vao_FILE_txt(f);
                in_vao_FILE_bin(fbin);
                fclose(f);
                fclose(fbin);
                break;

            case 2:
                system("cls");
                home_page();
                f = fopen("sinhvien.txt", "w");
                fbin = fopen("sinhvien.bin", "wb");
                start_deco(f);
                nhap_lieu(f);
                in_vao_FILE_txt(f);
                in_vao_FILE_bin(fbin);
                fclose(f);
                fclose(fbin);
                break;

            case 3:
                system("cls");
                home_page();
                fbin = fopen("sinhvien.bin", "rb");
                if (fbin == NULL){
                    printf("loi mo file!!");
                    break;
                }
                tim_kiem(fbin);
                fclose(fbin);
                break;

            case 4:
                system("cls");
                home_page();
                fbin = fopen("sinhvien.bin", "rb");
                if (fbin == NULL){
                    printf("loi mo file!!");
                    break;
                }
                fxuat = fopen("SV_da_sap_xep.txt", "w");
                sap_xep(fbin, fxuat);
                fclose(fbin);
                fclose(fxuat);
                break;

            case 5:
                system("cls");
                printf("\nhen gap lai!!");
                break;

        }
    }
    while(chon != 5);

    return 0;
}

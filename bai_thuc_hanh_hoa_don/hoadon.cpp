#include<bits/stdc++.h>
using namespace std;

class KHACH_HANG{
    int maKH;
    string HoTenKhach;
    string sdt;
    string DiaChi;
    public:
        KHACH_HANG();
        KHACH_HANG(int ma, string ten, string so, string diachi);

        int layMa() const {
            return maKH;
        }

        string layHoTen() const {
            return HoTenKhach;
        }

        string laySDT() const {
            return sdt;
        }

        string layDiaChi() const {
            return DiaChi;
        }

        void nhap();
        void in();
};

KHACH_HANG :: KHACH_HANG() :
    maKH(0), HoTenKhach(""), sdt(""), DiaChi("") {}

KHACH_HANG :: KHACH_HANG(int ma, string ten, string so, string diachi) :
    maKH(ma), HoTenKhach(ten), sdt(so), DiaChi(diachi) {}

void KHACH_HANG::nhap() {
    cout << "Nhap ma khach hang: ";
    cin >> maKH;

    cout << "Nhap ho ten khach hang: ";
    cin >> HoTenKhach;

    cout << "Nhap so dien thoai: ";
    cin >> sdt;

    cout << "Nhap dia chi khach hang: ";
    cin >> DiaChi;
}

void KHACH_HANG :: in(){
    cout << "Ma khach hang: " << maKH << " - "
         << "Khach hang: " << HoTenKhach << " - "
         << "so dien thoai: " << sdt << " - "
         << "dia chi: " << DiaChi;
}

class HANG_HOA{
    int maHH;
    string TenHangHoa;
    int SoLuong;
    float DonGia;
    public:
        HANG_HOA();
        HANG_HOA(int ma, string ten, int soluong, float dongia);

        void nhap();
        void in();

        float ThanhTien(){
            return SoLuong * DonGia;
        }
};

HANG_HOA :: HANG_HOA() :
    maHH(0), TenHangHoa(""), SoLuong(0), DonGia(0.0) {}

HANG_HOA :: HANG_HOA(int ma, string ten, int soluong, float dongia) :
    maHH(ma), TenHangHoa(ten), SoLuong(soluong), DonGia(dongia) {}

void HANG_HOA::nhap(){
    cout << "Nhap ma hang hoa: ";
    cin >> maHH;

    cout << "Nhap ten hang hoa: ";
    cin >> TenHangHoa;

    cout << "Nhap so luong hang: ";
    cin >> SoLuong;

    cout << "Nhap don gia: ";
    cin >> DonGia;
}

void HANG_HOA :: in(){
    cout << "Ma: " << maHH << " - "
         << "Ten: " << TenHangHoa << " - "
         << "So luong: " << SoLuong << " - "
         << "Don gia: " << DonGia << " - "
         << "Thanh tien: " << ThanhTien();
}

class HOA_DON{
    KHACH_HANG x;
    int smh;
    HANG_HOA *a;

    public:
        HOA_DON(){
            smh = 0;
            a = NULL;
        }

        ~HOA_DON(){
            delete[] a;
        }

        void nhap(){
            cout << "\nNHAP THONG TIN KHACH HANG\n";
            x.nhap();

            cout << "\nNhap so mat hang: ";
            cin >> smh;

            delete[] a;
            a = new HANG_HOA[smh];

            for(int i = 0; i < smh; i++){
                cout << "\nMAT HANG " << i + 1 << "\n";
                a[i].nhap();
            }
        }

        void in(){
            cout << "\n             HOA DON             \n";
            cout << "----------------------------------------\n";
            cout << "Thong tin khach hang:\n";
            x.in();
            cout << "\n----------------------------------------\n";
            cout << "\nDanh sach hang hoa:\n";
            cout << "----------------------------------------\n";
            for(int i = 0; i < smh; i++){
                cout << "\nSTT: " << i + 1 << " - ";
                a[i].in();
            }

            cout << "\nTong tien: " << TongTien() << endl;
            cout << "----------------------------------------\n";
        }

        float TongTien(){
            float tong = 0;

            for(int i = 0; i < smh; i++){
                tong += a[i].ThanhTien();
            }

            return tong;
        }
};

int main(){
    HOA_DON hd;
    int chon;

    do{
        cout << "\n========== MENU ==========\n";
        cout << "1. Nhap thong tin trong hoa don\n";
        cout << "2. In thong tin hoa don\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> chon;

        switch(chon){
            case 1:{
                hd.nhap();
                break;
            }

            case 2:{
                hd.in();
                break;
            }

            case 0:{
                cout << "Thoat chuong trinh!\n";
                break;
            }

            default:{
                cout << "Lua chon khong hop le!\n";
                break;
            }
        }
    }while(chon != 0);

    return 0;
}
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class phuong_tien
{
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }

double phuong_tien::tinh_phi() const
{
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0
                                                                      : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h)
    {
        if (h < 2)
            tong += gia * (cao_diem ? 1.30 : 0.95);
        else
            tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const
{
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}

class bai_xe
{
private:
    int ma_bai;
    char kich_thuoc;
    static const int xe_max = 3;
    phuong_tien ds_xe[xe_max];
    int so_luong_xe;
    int suc_chua() const
    {
        return (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2
                                                             : 3;
    }

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool co_xe(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int &dem, double &tong) const;
    bool trong() const;
    bool day() const;
    void hien_thi_loai(const string &loai) const;
    int tim_vi_tri_xe(int ma_xe) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), so_luong_xe(0) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_luong_xe(0) {}

int bai_xe::lay_ma() const { return ma_bai; }

int bai_xe::tim_vi_tri_xe(int ma_xe) const
{
    for (int i = 0; i < so_luong_xe; i++)
    {
        if (ds_xe[i].lay_ma_xe() == ma_xe)
            return i;
    }
    return -1;
}
bool bai_xe::them(phuong_tien v)
{
    if (day())
        return false;
    ds_xe[so_luong_xe] = v;
    so_luong_xe++;
    return true;
}
bool bai_xe::trong() const
{
    return so_luong_xe == 0;
}
void bai_xe::hien_thi_loai(const string &loai) const
{
    for (int i = 0; i < so_luong_xe; i++)
    {
        if (ds_xe[i].lay_loai_xe() == loai)
        {
            cout << "Bai " << ma_bai << ":\n";
            ds_xe[i].hien_thi();
        }
    }
}

bool bai_xe::day() const
{
    return so_luong_xe >= suc_chua();
}
bool bai_xe::xoa(int ma_xe)
{
    int vi_tri = tim_vi_tri_xe(ma_xe);
    if (vi_tri == -1)
        return false;

    for (int i = vi_tri; i < so_luong_xe; i++)
    {
        ds_xe[i] = ds_xe[i + 1];
    }
    so_luong_xe--;
}

bool bai_xe::co_xe(int ma_xe) const
{
    return tim_vi_tri_xe(ma_xe) != -1;
}

void bai_xe::hien_thi() const
{
    if (ma_bai == 0) return;
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_luong_xe << "/" << suc_chua() << " xe\n";
    for (int i = 0; i < so_luong_xe; i++)
    {
        ds_xe[i].hien_thi();
    }
}

bool bai_xe::co_loai(string loai, int &dem, double &tong) const
{
    dem = 0;
    tong = 0;
    for (int i = 0; i < so_luong_xe; i++)
    {
        if (ds_xe[i].lay_loai_xe() == loai)
        {
            dem++;
            tong += ds_xe[i].tinh_phi();
        }
    }
    return dem > 0;
}

class SystemInterface
{
private:
    static const int bai_max = 10;
    bai_xe ds_bai[bai_max];
    int so_luong_bai;
    bool trung_bai(int ma_bai) const;
    bool trung_xe(int ma_xe) const;

public:
    SystemInterface();
    void runMenu();
    int tao_ma();
};

SystemInterface::SystemInterface() : so_luong_bai(0) {}

int SystemInterface::tao_ma()
{
    int ma_moi;
}
bool SystemInterface::trung_bai(int ma_bai) const
{
    for (int i = 0; i < so_luong_bai; i++)
    {
        if (ds_bai[i].lay_ma() == ma_bai)
            return true;
    }
    return false;
}
bool SystemInterface::trung_xe(int ma_xe) const
{
    for (int i = 0; i < so_luong_bai; i++)
    {
        if (ds_bai[i].co_xe(ma_xe))
            return true;
    }
    return false;
}
void SystemInterface::runMenu()
{
    int chon = 0;
    while (chon != 9)
    {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        cin >> chon;
        // các e chuyển sang lệnh switch cho thầy
        switch (chon)
        {
        case (1):
        {
            int ma;
            char kt;
            if (so_luong_bai >= bai_max)
            {
                cout << "Da tao toi da " << bai_max << " bai xe\n";
                break;
            }
            
            do {
                cout << "Ma bai: ";
                cin >> ma;
                if (ma == 0) {
                    cout << "Ma bai xe phai lon hon 0" << endl;
                }
            } while (ma == 0);
            cout << "Kich thuoc (S/M/L): ";
            cin >> kt;
            kt = toupper(kt);
            if (kt == 'S')
                ;
            else if (kt == 'M')
                ;
            else if (kt == 'L')
                ;
            else
            {
                cout << "Kich thuoc khong ton tai" << endl;
                break;
            }
            if (!trung_bai(ma))
            {
                ds_bai[so_luong_bai] = bai_xe(ma, kt);
                so_luong_bai++;
                cout << "Da tao bai " << ma << endl;
            }
            else
            {
                cout << "Bai da ton tai" << endl;
                break;
            }
            break;
        }
        case (2):
        {
            if (so_luong_bai == 0)
            {
                cout << "chua co bai do xe nao" << endl;
                break;
            }
            int ma, gio, tg;
            string loai;

            do
            {
                cout << "Ma xe: ";
                cin >> ma;
                if (ma > 0)
                {
                    if (trung_xe(ma))
                    {
                        cout << "Ma xe nay da ton tai" << endl;
                    }
                }
                else
                {
                    cout << "ma xe phai lon hon 0" << endl;
                }
            } while (ma <= 0 || (trung_xe(ma)));
            do
            {
                cout << "Loai (Car/Motorcycle/Bicycle): ";
                cin >> loai;
                if (loai != "Car" && loai != "Motorcycle" && loai != "Bicycle")
                {
                    cout << "loai xe khong ton tai" << endl;
                }
            } while (loai != "Car" && loai != "Motorcycle" && loai != "Bicycle");
            do
            {
                cout << "Gio vao (0-23): ";
                cin >> gio;
                if (gio < 0 || gio > 23)
                {
                    cout << "gio vao phai tu 0h-23h" << endl;
                }
            } while (gio < 0 || gio > 23);
            do
            {
                cout << "Thoi luong (1-23): ";
                cin >> tg;
                if (tg < 1 || tg > 23)
                {
                    cout << "thoi gian do hop le la 1h-23h" << endl;
                }
            } while (tg < 1 || tg > 23);
            phuong_tien v(ma, loai, gio, tg);
            bool ok = false;
            for (int i = 0; i < so_luong_bai; i++)
            {
                if (!ds_bai[i].day())
                {
                    ds_bai[i].them(v);
                    cout << "Da them xe" << endl;
                    break;
                }
                else if (i != so_luong_bai - 1 && ds_bai[i].day())
                {
                    continue;
                }
                else if (i == so_luong_bai - 1 && ds_bai[i].day())
                {
                    cout << "Tat ca bai xe da day" << endl;
                }
            }
            break;
        }
        case (3):
        {
            if (so_luong_bai == 0)
            {
                cout << "chua co bai do xe nao" << endl;
                break;
            }
            int ma;
            cout << "Ma bai can xoa: ";
            cin >> ma;
            bool dang_co_xe = false;
            for (int i = 0; i < so_luong_bai; i++)
            {
                if (ds_bai[i].lay_ma() == ma && !ds_bai[i].trong())
                {
                    cout << "Bai nay dang co xe, khong the xoa" << endl;
                    dang_co_xe = true;
                    break;
                }
            }
            if (dang_co_xe)
                break;
            int da_xoa = 0;
            bool ko_co_xe = true;
            for (int i = 0; i < so_luong_bai; i++)
            {
                if (da_xoa == 0)
                {
                    if (ds_bai[i].lay_ma() == ma)
                    {
                        ds_bai[i] = bai_xe();
                        i--;
                        da_xoa = 1;
                        ko_co_xe = false;
                    }
                }
                else if (da_xoa == 1)
                {
                    if (i != so_luong_bai - 1)
                    {
                        ds_bai[i] = ds_bai[i + 1];
                    }
                    if (i == so_luong_bai - 1)
                    {
                        ds_bai[i] = bai_xe();
                        so_luong_bai--;
                        cout << "Da xoa bai xe " << ma << endl;
                    }
                }
                if (da_xoa == 0 && ko_co_xe) {
                    cout << "Khong tim thay bai do xe " << ma << endl;
                }
            }
            break;
        }
        case (4):
        {
            int ma;
            cout << "Ma xe can lay ra: ";
            cin >> ma;
            for (int i = 0; i < so_luong_bai; i++) {
                if(ds_bai[i].co_xe(ma)) {
                    ds_bai[i].xoa(ma);
                    cout << "Da xoa xe " << ma << endl;
                    break; 
                }
                else {
                    cout << "Xe khong ton tai" << endl;
                }
            }
            break;
        }
        case (5):
        {
            for (int i = 0; i < so_luong_bai; i++)
            {
                ds_bai[i].hien_thi();
            }
            break;
        }
        case (6):
        {
            int ma;
            cout << "Ma bai: ";
            cin >> ma;
            for (int i = 0; i < so_luong_bai; i++) {
                if (ds_bai[i].lay_ma() == ma) {
                    ds_bai[i].hien_thi();
                    break;
                }
            }
            break;
        }
        case (7):
        {
            string loai;
            cout << "Loai xe: ";
            cin >> loai;
            int dem;
            double tong;
            for (int i = 0; i < so_luong_bai; i++) {
                if (ds_bai[i].co_loai(loai, dem, tong)) {
                    ds_bai[i].hien_thi_loai(loai);
                }
            }
            break;
        }
        case (8):
        {
            string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
            for (int t = 0; t < 3; ++t)
            {
                int dem = 0;
                double tong = 0;
                int d;
                double s;
                for (int i = 0; i < so_luong_bai; i++) {
                    if(ds_bai[i].co_loai(loai_arr[t], d, s)) {
                        dem += d;
                        tong += s;
                    }
                }
                cout << loai_arr[t] << ": ";
                if (dem == 0)
                    cout << "khong co xe\n";
                else
                    cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
            }
            break;
        }
        case (9):
            cout << "da thoat chuong trinh\n";
            break;
        }
    }
}

int main()
{
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
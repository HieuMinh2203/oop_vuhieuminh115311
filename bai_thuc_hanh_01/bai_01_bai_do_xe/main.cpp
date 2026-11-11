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
    phuong_tien pt1, pt2, pt3; // sau này dùng mảng
    bool co_xe1, co_xe2, co_xe3;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int &dem, double &tong) const;
    bool trong() const;
    void hien_thi_loai(const string &loai) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), co_xe1(false), co_xe2(false), co_xe3(false) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), co_xe1(false), co_xe2(false), co_xe3(false) {}

int bai_xe::lay_ma() const { return ma_bai; }

bool bai_xe::them(phuong_tien v)
{
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2
                                                            : 3;
    if (cap >= 1 && !co_xe1)
    {
        pt1 = v;
        co_xe1 = true;
        return true;
    }
    if (cap >= 2 && !co_xe2)
    {
        pt2 = v;
        co_xe2 = true;
        return true;
    }
    if (cap >= 3 && !co_xe3)
    {
        pt3 = v;
        co_xe3 = true;
        return true;
    }
    return false;
}
bool bai_xe::trong() const
{
    return !co_xe1 && !co_xe2 && !co_xe3;
}
void bai_xe::hien_thi_loai(const string &loai) const {
    if (co_xe1 && pt1.lay_loai_xe() == loai) pt1.hien_thi();
    if (co_xe2 && pt2.lay_loai_xe() == loai) pt2.hien_thi();
    if (co_xe3 && pt3.lay_loai_xe() == loai) pt3.hien_thi();
}

bool bai_xe::xoa(int ma_xe)
{
    if (co_xe1 && pt1.lay_ma_xe() == ma_xe)
    {
        if (co_xe2)
        {
            pt1 = pt2;
            if (co_xe3)
            {
                pt2 = pt3;
                co_xe3 = false;
            }
            else
                co_xe2 = false;
        }
        else
            co_xe1 = false;
        return true;
    }
    if (co_xe2 && pt2.lay_ma_xe() == ma_xe)
    {
        if (co_xe3)
        {
            pt2 = pt3;
            co_xe3 = false;
        }
        else
            co_xe2 = false;
        return true;
    }
    if (co_xe3 && pt3.lay_ma_xe() == ma_xe)
    {
        co_xe3 = false;
        return true;
    }
    return false;
}

bool bai_xe::chua(int ma_xe) const
{
    if (co_xe1 && pt1.lay_ma_xe() == ma_xe)
        return true;
    if (co_xe2 && pt2.lay_ma_xe() == ma_xe)
        return true;
    if (co_xe3 && pt3.lay_ma_xe() == ma_xe)
        return true;
    return false;
}

void bai_xe::hien_thi() const
{
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2
                                                            : 3;
    int so_xe = co_xe1 + co_xe2 + co_xe3;
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_xe << "/" << cap << " xe\n";
    if (co_xe1)
        pt1.hien_thi();
    if (co_xe2)
        pt2.hien_thi();
    if (co_xe3)
        pt3.hien_thi();
}

bool bai_xe::co_loai(string loai, int &dem, double &tong) const
{
    dem = 0;
    tong = 0;
    if (co_xe1 && pt1.lay_loai_xe() == loai)
    {
        ++dem;
        tong += pt1.tinh_phi();
    }
    if (co_xe2 && pt2.lay_loai_xe() == loai)
    {
        ++dem;
        tong += pt2.tinh_phi();
    }
    if (co_xe3 && pt3.lay_loai_xe() == loai)
    {
        ++dem;
        tong += pt3.tinh_phi();
    }
    return dem > 0;
}

class SystemInterface
{
private:
    bai_xe bai1, bai2, bai3; // sau này dùng mảng
    bool co_bai1, co_bai2, co_bai3;

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() : co_bai1(false), co_bai2(false), co_bai3(false) {}

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
            do
            {
                cout << "Ma bai: ";
                cin >> ma;
                if (co_bai1 && bai1.lay_ma() == ma || co_bai2 && bai2.lay_ma() == ma || co_bai3 && bai3.lay_ma() == ma)
                {
                    cout << "bai nay da ton tai" << endl;
                }
            } while (co_bai1 && bai1.lay_ma() == ma || co_bai2 && bai2.lay_ma() == ma || co_bai3 && bai3.lay_ma() == ma);
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
            if (!co_bai1)
            {
                bai1 = bai_xe(ma, kt);
                co_bai1 = true;
                cout << "Da tao bai " << ma << "\n";
            }
            else if (!co_bai2)
            {
                bai2 = bai_xe(ma, kt);
                co_bai2 = true;
                cout << "Da tao bai " << ma << "\n";
            }
            else if (!co_bai3)
            {
                bai3 = bai_xe(ma, kt);
                co_bai3 = true;
                cout << "Da tao bai " << ma << "\n";
            }
            else
            {
                cout << "chi duoc tao toi da 3 bai xe\n";
            }
            break;
        }
        case (2):
        {
            if (co_bai1 == false && co_bai2 == false && co_bai3 == false)
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
                    if ((co_bai1 && bai1.chua(ma)) || (co_bai2 && bai2.chua(ma)) || (co_bai3 && bai3.chua(ma)))
                    {
                        cout << "Ma xe nay da ton tai" << endl;
                    }
                }
                else
                {
                    cout << "ma xe phai lon hon 0" << endl;
                }
            } while (ma <= 0 || ((co_bai1 && bai1.chua(ma)) == true || (co_bai2 && bai2.chua(ma)) == true || (co_bai3 && bai3.chua(ma)) == true));
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
            if (co_bai1 && !ok)
                ok = bai1.them(v);
            if (co_bai2 && !ok)
                ok = bai2.them(v);
            if (co_bai3 && !ok)
                ok = bai3.them(v);
            if (ok)
                cout << "Da them xe " << ma << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
            else
                cout << "Tat ca bai da day!\n";
            break;
        }
        case (3):
        {
            if (co_bai1 == false && co_bai2 == false && co_bai3 == false)
            {
                cout << "chua co bai do xe nao" << endl;
                break;
            }
            int ma;
            cout << "Ma bai can xoa: ";
            cin >> ma;
            if ((co_bai1 && !bai1.trong() && bai1.lay_ma() == ma) || (co_bai2 && !bai2.trong() && bai2.lay_ma() == ma) || (co_bai3 && !bai3.trong() && bai3.lay_ma() == ma))
            {
                cout << "bai nay dang co xe do, khong the xoa" << endl;
                break;
            }
            if (co_bai1 && bai1.lay_ma() == ma)
            {
                if (co_bai2)
                {
                    bai1 = bai2;
                    if (co_bai3)
                    {
                        bai2 = bai3;
                        bai3 = bai_xe();
                        co_bai3 = false;
                    }
                    else
                    {
                        bai2 = bai_xe();
                        co_bai2 = false;
                    }
                }
                else
                {
                    bai1 = bai_xe();
                    co_bai1 = false;
                }
                cout << "Da xoa bai " << ma << "\n";
            }
            else if (co_bai2 && bai2.lay_ma() == ma)
            {
                if (co_bai3)
                {
                    bai2 = bai3;
                    bai3 = bai_xe();
                    co_bai3 = false;
                }
                else
                {
                    bai2 = bai_xe();
                    co_bai2 = false;
                }
                cout << "Da xoa bai " << ma << "\n";
            }
            else if (co_bai3 && bai3.lay_ma() == ma)
            {
                bai3 = bai_xe();
                co_bai3 = false;
                cout << "Da xoa bai " << ma << "\n";
            }
            break;
        }
        case (4):
        {
            int ma;
            cout << "Ma xe can lay ra: ";
            cin >> ma;
            bool ok = false;
            if (co_bai1 && !ok)
                ok = bai1.xoa(ma);
            if (co_bai2 && !ok)
                ok = bai2.xoa(ma);
            if (co_bai3 && !ok)
                ok = bai3.xoa(ma);
            cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
            break;
        }
        case (5):
        {
            if (co_bai1)
                bai1.hien_thi();
            if (co_bai2)
                bai2.hien_thi();
            if (co_bai3)
                bai3.hien_thi();
            break;
        }
        case (6):
        {
            int ma;
            cout << "Ma bai: ";
            cin >> ma;
            if (co_bai1 && bai1.lay_ma() == ma)
                bai1.hien_thi();
            else if (co_bai2 && bai2.lay_ma() == ma)
                bai2.hien_thi();
            else if (co_bai3 && bai3.lay_ma() == ma)
                bai3.hien_thi();
            break;
        }
        case (7):
        {
            string loai;
            cout << "Loai xe: ";
            cin >> loai;
            int dem;
            double tong;
            if (co_bai1 && bai1.co_loai(loai, dem, tong))
                bai1.hien_thi_loai(loai);
            if (co_bai2 && bai2.co_loai(loai, dem, tong))
                bai2.hien_thi_loai(loai);
            if (co_bai3 && bai3.co_loai(loai, dem, tong))
                bai3.hien_thi_loai(loai);
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
                if (co_bai1)
                {
                    bai1.co_loai(loai_arr[t], d, s);
                    dem += d;
                    tong += s;
                }
                if (co_bai2)
                {
                    bai2.co_loai(loai_arr[t], d, s);
                    dem += d;
                    tong += s;
                }
                if (co_bai3)
                {
                    bai3.co_loai(loai_arr[t], d, s);
                    dem += d;
                    tong += s;
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
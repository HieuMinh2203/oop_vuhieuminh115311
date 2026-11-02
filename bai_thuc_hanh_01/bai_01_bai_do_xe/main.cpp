#include <iostream>
using namespace std;
class phuong_tien {
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
phuong_tien::phuong_tien(){
	ma_xe = 0;
	loai_xe = "";
	gio_vao = 0;
	tg_do = 0;	
}
phuong_tien::phuong_tien(int ma, string loai, int gio, int tg) {
	ma_xe = ma;
	loai_xe = loai;
	gio_vao = gio;
	tg_do = tg;
}
int phuong_tien :: lay_ma_xe() const {return ma_xe;}
string phuong_tien :: lay_loai_xe() const {return loai_xe;}
void phuong_tien :: hien_thi() const {
	cout << "Ma xe: " << ma_xe << endl
		 << "Loai xe: " << loai_xe << endl
		 << "Gio vao: " << gio_vao << endl
		 << "Thoi gian do: " << tg_do << endl;
}
double phuong_tien :: tinh_phi() const {
	double tien = 0;

    if (loai_xe == "Xe oto") {
        tien += 6;
    }
    else if (loai_xe == "Xe may") {
        tien += 4;
    }
    else if (loai_xe == "Xe dap") {
        tien += 2;
    }
    bool caoDiem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    int gioDau;
    if (tg_do < 2) {
    	 gioDau = tg_do;
	}
	else gioDau = 2;
	double giaDau;
	if(caoDiem) giaDau = tien * 1.3;
	else giaDau = tien * 0.95;
    int gioSau = tg_do - gioDau;
    double giaSau = tien * 0.9;
    double TongTien = gioDau * giaDau + gioSau * giaSau;
}
class bai_xe{
	private:
		int ma_bai;
		char kich_thuoc;
		phuong_tien pt1, pt2, pt3;
		bool co1,co2,co3;
	public:
		bai_xe();
		bai_xe(int ma, char kt);
		int lay_ma() const;
		bool them(phuong_tien v);
		bool xoa(int ma_xe);
		bool chua(int ma_xe) const;
		void hien_thi() const;
		bool co_loai(string loai, int& dem, double& tong)const;
};
bai_xe::bai_xe() {
	ma_bai = 0;
	kich_thuoc = '\0';
	co1 = false;
	co2 = false;
	co3 = false;
}; 
bai_xe::bai_xe(int ma, char kt){
	ma_bai = ma;
	kich_thuoc = kt;
};
int bai_xe::lay_ma() const {return ma_bai;}
bool bai_xe::them(phuong_tien v){
	int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
	if (cap >= 1 && !co1){
		pt1 = v;
		co1 = true;
		return true;
	}
	else if (cap >= 2 && !co2) {
		pt2 = v;
		co2 = true;
		return true;
	}
	else if (cap >= 3 && !co3) {
		pt3 = v;
		co3 = true;
		return true;
	}
	return false;
}
class SystemInterFace{
	private:
		bai_xe bai1, bai2, bai3;
		bool co1,co2,co3;
	public:
		SystemInterFace();
		void runMenu();	
};

int main () {

}
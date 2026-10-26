#include <iostream>
#include<string>
#include<cctype>
#include<iomanip>
using namespace std;
class Vehicle {
    private:
    int vehicleID, entryTime, parkingDuration;
    string vehicleType;
    double parkingFee;
    bool isOccupied = false;
    public:
    Vehicle(): vehicleID(0), entryTime(0), parkingDuration(0), vehicleType(""),parkingFee(0.0), isOccupied(false){} 
    Vehicle(int ID, int time, int dur, string type){setVehicleID(ID); setEntryTime(time); setParkingDuration(dur); setVehicleType(type); calculateFee();}
    void calculateFee();
    void display() const;
    int getVehicleID() const {return vehicleID;}
    void setVehicleID(int ID){ vehicleID = ID;}
    int getEntryTime() const {return entryTime;}
    void setEntryTime(int time){
        if (time >= 0 && time <= 23) {
            entryTime = time;
        }
    }
    int getParkingDuration() const {return parkingDuration;}
    void setParkingDuration(int dur){
        if (dur >= 1 && dur <= 23) parkingDuration = dur;
    }
    string getVehicleType() const {return vehicleType;}
    bool setVehicleType(string type){
        for (int i = 0; i < type.length(); i++){
            type[i] = tolower(type[i]);
        }
        if (type == "car"){
            vehicleType = "Car";
            return true;
        }
        else if (type == "motorcycle")
        {
            vehicleType = "Motorcycle";
            return true;
        }
        else if (type == "bicycle"){
            vehicleType = "Bicycle";
            return true;
        }
        else {
            return false;
        }
        
    }
    double getParkingFee() const {return parkingFee;}
    void setParkingFee(double fee){ parkingFee = fee;}
    bool getIsOccupied() const {return isOccupied;}
    void setIsOccupied(bool occupied){ isOccupied = occupied;}
    
};
class ParkingLot {
    private:
    int parkID;
    char size;
    Vehicle vehicle1, vehicle2, vehicle3;
    bool hasVehicle1, hasVehicle2, hasVehicle3;
    public:
    ParkingLot(): parkID(0), size('S'), hasVehicle1(false), hasVehicle2(false), hasVehicle3(false){}
    ParkingLot(int pID, char kichthuoc): parkID(0), size('S'), hasVehicle1(false), hasVehicle2(false), hasVehicle3(false) {setParkID(pID); setSize(kichthuoc);}
    int getParkID() const {return parkID;}
    void setParkID(int pID) { parkID = pID;}
    char getSize() const {return size;}
    bool setSize(char kichthuoc) {
        kichthuoc = toupper(kichthuoc);
        if (kichthuoc == 'S') {
            size = 'S';
            return true;
        } 
        else if (kichthuoc == 'M') {
            size = 'M';
            return true;
        }
        else if (kichthuoc == 'L') {
            size = 'L';
            return true;
        }
        else return false;
    }
    bool getHasVehicle1() const {return hasVehicle1;}
    void setHasVehicle1(bool hasve1) {hasVehicle1 = hasve1;}
    bool getHasVehicle2() const {return hasVehicle2;}
    void setHasVehicle2(bool hasve2) {hasVehicle2 = hasve2;}
    bool getHasVehicle3() const {return hasVehicle3;}
    void setHasVehicle3(bool hasve3) {hasVehicle3 = hasve3;}
    bool addVehicle(const Vehicle& v);
    bool removeVehicle(int vID);
    void displayLotInfo();
    int capacity() const;
};
void Vehicle::calculateFee(){
    double tien = 0;

    if (vehicleType == "Car") {
        tien += 6;
        
    }
    else if (vehicleType == "Motorcycle") {
        tien += 4;
    }
    else if (vehicleType == "Bicycle") {
        tien += 2;
    }
    bool caoDiem = (entryTime >= 6 && entryTime <= 9) || (entryTime >= 15 && entryTime <= 18);
    int gioDau = (parkingDuration < 2) ? parkingDuration : 2;
    double giaDau = caoDiem ? tien * 1.3 : tien * 0.95;
    int gioSau = parkingDuration - gioDau;
    double giaSau = tien * 0.9;
    parkingFee = gioDau * giaDau + gioSau * giaSau;
}
void Vehicle::display() const {
    cout << "Vehicle ID: " << vehicleID << endl;
    cout << "Vehicle Type: " << vehicleType << endl;
    cout << "Entry Time: " << entryTime << endl;
    cout << "Duration: " << parkingDuration << endl;
    cout << "Parking Fee: "  << fixed << setprecision(2) << parkingFee << endl;
    cout << "Status: " << (isOccupied ? "Occupied" : "Empty") << endl;
}
int ParkingLot::capacity() const {
    switch (size)
    {
    case 'S':
        return 1;
    case 'M':
        return 2;
    case 'L':
        return 3;
    default:
        return 0;
    }
}
bool ParkingLot::addVehicle(const Vehicle& v) {
    if (hasVehicle1 == true && vehicle1.getVehicleID() == v.getVehicleID()) return false;
    if (hasVehicle2 == true && vehicle2.getVehicleID() == v.getVehicleID()) return false;
    if (hasVehicle3 == true && vehicle3.getVehicleID() == v.getVehicleID()) return false;
    if (hasVehicle1 == false) {
        vehicle1 = v;
        vehicle1.setIsOccupied(true);
        hasVehicle1 = true;
        return true;
    }
    if (hasVehicle2 == false && capacity() >= 2) {
        vehicle2 = v;
        vehicle2.setIsOccupied(true);
        hasVehicle2 = true;
        return true;
    }
    if (hasVehicle3 == false && capacity() >= 3) {
        vehicle3 = v;
        vehicle3.setIsOccupied(true);
        hasVehicle3 = true;
        return true;
    }
    return false;
}
bool ParkingLot::removeVehicle(int vID) {
    if (hasVehicle1 == true && vehicle1.getVehicleID() == vID) {
        vehicle1 = Vehicle();
        hasVehicle1 = false;
        return true;
    }
    if (hasVehicle2 == true && vehicle2.getVehicleID() == vID) {
        vehicle2 = Vehicle();
        hasVehicle2 = false;
        return true;
    }
    if (hasVehicle3 == true && vehicle3.getVehicleID() == vID) {
        vehicle3 = Vehicle();
        hasVehicle3 = false;
        return true;
    }
    return false;
}
void ParkingLot::displayLotInfo(){
    if (hasVehicle1 == true) vehicle1.display();
    if (hasVehicle2 == true) vehicle2.display();
    if (hasVehicle3 == true) vehicle3.display();
    if (hasVehicle1 == false && hasVehicle2 == false && hasVehicle3 == false) {
        cout << "bai trong" << endl;
    }
}
class SystemInterface {
    ParkingLot parkingLot1, parkingLot2, parkingLot3;
    bool hasLot1, hasLot2, hasLot3;
    public:
    SystemInterface() : hasLot1(false), hasLot2(false), hasLot3(false) {}
    void runMenu();
};
void SystemInterface::runMenu() {
    int n = 0;
    do {
    cout << "danh sach chuc nang:" << endl
         << "1: tao bai do xe moi" << endl
         << "2: them xe vao bai do" << endl
         << "3: xoa mot bai do xe" << endl
         << "4: lay xe ra khoi bai" << endl
         << "5: hien thi danh sach tat ca bai do xe" << endl
         << "6: hien thi danh sach xe theo bai cu the" << endl
         << "7: liet ke theo phuong tien" << endl
         << "8: xem bao cao tom tat chi phi xe trung binh" << endl
         << "9: thoat chuong trinh" << endl
         << "nhap chuc nang muon dung: ";
    cin >> n;
    switch (n)
    {
    case 1:
        cout << "in progress 1" << endl;
        break;
    case 2:
        cout << "in progress 2" << endl;
        break;
    case 3:
        cout << "in progress 3" << endl;
        break;
    case 4:
        cout << "in progress 4" << endl;
        break;
    case 5:
        cout << "in progress 5" << endl;
        break;
    case 6:
        cout << "in progress 6" << endl;
        break;
    case 7:
        cout << "in progress 7" << endl;
        break;
    case 8:
        cout << "in progress 8" << endl;
        break;
    case 9:
        cout << "Da thoat chuong trinh" << endl;
        return;
    default:
        cout << "chuc nang khong ton tai" << endl;
        break;
    }
    } while (n != 9);
}
int main () {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
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
    Vehicle(int ID, int time, int dur, string type, double fee, bool occupied): vehicleID(0), entryTime(0), parkingDuration(0), vehicleType(""),parkingFee(0.0), isOccupied(false) {setVehicleID(ID); setEntryTime(time); setParkingDuration(dur); setVehicleType(type); setParkingFee(fee); setIsOccupied(occupied); calculateFee();}
    void calculateFee();
    void display();
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
    ParkingLot(int ID, char kichthuoc): parkID(0), size('S'), hasVehicle1(false), hasVehicle2(false), hasVehicle3(false) {setParkID(ID); setSize(kichthuoc);}
    int getParkID() const {return parkID;}
    void setParkID(int ID) { parkID = ID;}
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
};
void Vehicle::calculateFee(){
}
void Vehicle::display(){
}
bool ParkingLot::addVehicle(const Vehicle& v) {
    
}
bool ParkingLot::removeVehicle(int vID){

}
void ParkingLot::displayLotInfo(){

}
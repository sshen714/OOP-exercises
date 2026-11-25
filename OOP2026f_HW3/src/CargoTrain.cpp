#include "CargoTrain.hpp"

CargoTrain::CargoTrain(int fuelLimit,
                       int cargoLimit,
                       TrainType type,
                       int trainNumber,
                       int speedLimit
                       ):Train(type, trainNumber, speedLimit),
                        fuelLimit(fuelLimit),
                        fuel(0),
                        cargoLimit(cargoLimit),
                        cargo(0){}

int CargoTrain::GetFuelLimit(){ return fuelLimit; }

int CargoTrain::GetCargoLimit(){ return cargoLimit; }

void CargoTrain::SetFuelLimit(int fuelLimit) {

    if (fuelLimit<=0 ||fuelLimit>1200) { throw std::invalid_argument(""); }
    this->fuelLimit=fuelLimit;
}

int CargoTrain::GetFuel(){ return fuel;}

int CargoTrain::GetCargo(){ return cargo;}

void CargoTrain::AddCargo(int cargo) {

    if (GetCargo()+cargo>cargoLimit){ throw std::invalid_argument(""); }
    this->cargo+=cargo;
}

void CargoTrain::AddFuel(int fuel) {

    if (GetFuel()+fuel>fuelLimit){ throw std::invalid_argument(""); }
    this->fuel+=fuel;
}

void CargoTrain::PowerUp() {

    if (fuel< 5){ throw std::invalid_argument(""); }
    open=true;
    fuel -=5 ;
}

void CargoTrain::SpeedUp() {

    if (!open || fuel<10){ throw std::invalid_argument(""); }

    fuel-=10 ;
    float check= float (cargo) / float (cargoLimit);

    if (check< 0.3) {

        if (15 + speed / 20 + speed > GetSpeedLimit() ){ speed=GetSpeedLimit(); }
        else{ speed  = 15 + speed / 20 + speed; }

    }else if (check>=0.3 && check<=0.7) {

        if (15 + speed / 25 + speed > GetSpeedLimit() ){ speed=GetSpeedLimit(); }
        else{ speed  = 15 + speed / 25 + speed; }

    }else {

        if (15 + speed / 30 + speed > GetSpeedLimit() ){ speed=GetSpeedLimit(); }
        else{ speed  = 15 + speed / 30 + speed; }
    }

}

void CargoTrain::SpeedDown() {

    if (!open || fuel==0) {throw std::invalid_argument(""); }

    if (speed<15) {
        speed =0;
    }else {
        speed = speed - 15;
    }
}
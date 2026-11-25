#include "MaglevTrain.hpp"

MaglevTrain::MaglevTrain(int powerLimit,
                         int seatLimit,
                         TrainType type,
                         int trainNumber,
                         int speedLimit
                         )
                        :Train(type, trainNumber, speedLimit),
                        powerLimit(powerLimit),
                        power(0),
                        seatLimit(seatLimit),
                        seat(0){}



int MaglevTrain::GetPowerLimit(){ return powerLimit; }

int MaglevTrain::GetSeatLimit(){ return seatLimit; }

void MaglevTrain::SetPowerLimit(int powerLimit) {
    if (powerLimit<=0 || powerLimit>120) {
        throw std::invalid_argument("");
    }
    this-> powerLimit=powerLimit;
}

int MaglevTrain::GetPower(){ return power; }

int MaglevTrain::GetSeat(){ return seat;}

void MaglevTrain::AddSeat() {

    if (seat>=seatLimit) {
        throw std::invalid_argument("");
    }
    seat+=1;
}

void MaglevTrain::Charge(int hour) {
    power+=hour*16;
    if (power>powerLimit){ power=powerLimit; }
}

void MaglevTrain::PowerUp() {

    if (power==0){ throw std::invalid_argument(""); }
    open=true;
    power-=1;
}

void MaglevTrain::SpeedUp() {

    if (!open || power<3){ throw std::invalid_argument(""); }
    if (25 + speed / 15 + speed >GetSpeedLimit()){ speed = GetSpeedLimit(); }
    else{ speed=25 + speed / 15 + speed;}
    power-=3;
}

void MaglevTrain::SpeedDown() {

    if (!open || power == 0){ throw std::invalid_argument(""); }
    if (speed<25){ speed= 0; }
    else{ speed=speed-25; }
}
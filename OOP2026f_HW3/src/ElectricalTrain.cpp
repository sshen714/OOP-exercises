#include "ElectricalTrain.hpp"

ElectricalTrain::ElectricalTrain(int powerLimit,
                int seatLimit,
                TrainType type,
                int trainNumber,
                int speedLimit
                )
                : Train(type, trainNumber, speedLimit),
                    powerLimit(powerLimit),
                    power(0),
                    seatLimit(seatLimit),
                    seat(0) {}

int ElectricalTrain::GetPowerLimit() { return powerLimit; }

int ElectricalTrain::GetSeatLimit() { return seatLimit; }

void ElectricalTrain::SetPowerLimit(int powerLimit) {

    if (powerLimit<=0 || powerLimit>120) {
        throw std::invalid_argument("");
    }

    this->powerLimit=powerLimit;
}

int ElectricalTrain::GetPower() { return power; }

int ElectricalTrain::GetSeat() { return  seat; }

void ElectricalTrain::AddSeat() {

    if (seat>=seatLimit){ throw std::invalid_argument(""); }
    seat+=1;
}

void ElectricalTrain::Charge(int hour) {
    power+=hour*20;
    if (power>powerLimit){ power=powerLimit; }
}

void ElectricalTrain::PowerUp() {

    if (power==0) {
        throw std::invalid_argument("");
    }
    open=true;
    power-=1;
}

void ElectricalTrain::SpeedUp() {

    if (!open){ throw std::invalid_argument(""); }
    if (power<3) { throw std::invalid_argument(""); }

    power-=3;
    speed= 12 + speed / 20 + speed;
    if (speed > GetSpeedLimit()) { speed=GetSpeedLimit(); }
}

void ElectricalTrain::SpeedDown() {

    if (!open || power == 0){ throw std::invalid_argument(""); }
    if (speed-12<0) {
        speed=0;
    }else {
        speed=speed-12;
    }
}
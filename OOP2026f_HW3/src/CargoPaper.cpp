#include "CargoPaper.hpp"

CargoPaper::CargoPaper(std::string dest,
                       std::string src,
                       int range,
                       int volume,
                       CargoType cargoType
                       ) : Ticket(dest, src, range, 0, TrainType::Cargo),
                        volume(volume),
                        cargoType(cargoType){}

int CargoPaper::GetVolume(){ return volume; }
CargoType CargoPaper::GetCargoType(){ return cargoType; }

void CargoPaper::CalculateTicketPrice() {

    price=range*5;
    switch (cargoType) {

        case CargoType::Vehicle :
            price+= volume*60;
            price*=1.25;
            break;

        case CargoType::Drink:
        case CargoType::Food:
            price+= volume/100*60;
            price*=1.08;
            break;

        case CargoType::Electronics:
        case CargoType::Furniture:
            price+= volume/100*60;
            price*=1.15;
            break;


    }
}
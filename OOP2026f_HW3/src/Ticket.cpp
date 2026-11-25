#include "Ticket.hpp"

Ticket::Ticket(std::string dest, std::string src, int range, int trainNumber, TrainType type) {

    this->dest=dest;
    this->src=src;
    this->range=range;
    this->trainNumber=trainNumber;
    this->type=type;
    price = 0;
}

std::string Ticket::GetDest(){ return dest; }
std::string Ticket::GetSrc(){ return src; }
int Ticket::GetPrice() { return price; }
int Ticket::GetTrainNumber(){ return trainNumber; }
TrainType Ticket::GetTrainType(){ return type;}

void Ticket::CalculateTicketPrice() {

    price=range*3;
    if (GetTrainType() == TrainType::Express ) {

        price*=1.5;
        if (range>=100){ price+=(range/100)*30; }

    }else if (GetTrainType() == TrainType::Limited){ price*=1.25; }

}
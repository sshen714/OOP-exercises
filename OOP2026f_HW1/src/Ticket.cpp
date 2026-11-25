#include "Ticket.hpp"
#include <stdexcept>


int getter_price(TicketType type) {

    switch (type) {
        case TicketType::First: return 450;
        case TicketType::Business: return 325;
        case TicketType::Economy: return 200;
        default: throw std::invalid_argument("");
    }

}

Ticket MakeTicketOrder(TicketType type) {

    Ticket t;
    t.type=type;
    t.count=getter_price(type);
    return t;

}

int CheckTicketPrice(Ticket ticket) {
    if ( ticket.count!= getter_price(ticket.type)) {throw std::invalid_argument("");}
    return getter_price(ticket.type);
}
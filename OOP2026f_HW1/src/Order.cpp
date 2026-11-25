#include "Order.hpp"
#include "Ticket.hpp"

Order MakeOrder(std::vector<Ticket> tickets) {

    Order o;
    o.totalCount=0;
    o.tickets = tickets;

    for (int i=0; i < tickets.size() ;i++) { o.totalCount += CheckTicketPrice(tickets[i]); }
    return o;
}

int CheckSpecificTicketSales(TicketType type,Order order) {

    int todaysales=0;

    for (int i=0 ;i < order.tickets.size();i++) {
        if (order.tickets[i].type == type) { todaysales += CheckTicketPrice(order.tickets[i]); }
    }

    return todaysales;
}
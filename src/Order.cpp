#include "../include/Action.h"
#include "../include/Table.h"
#include "../include/Restaurant.h"
//
// Created by USER on 11/7/2018.
//
Order::Order(int id): tableId(id){}
void Order::act(Restaurant &restaurant) {
    Table * t =restaurant.getTable(tableId);
    int custId;

    if(t == nullptr || !t->isOpen())
        error("Table does not exist or is not open");
    else{
        t->order(restaurant.getMenu());
        for(int i = 0;i< t->getOrders().size();i++){
            custId = t->getOrders().at(i).first;
            std::cout <<t->getCustomer(custId)->getName() + "ordered" + t->getOrders().at(i).second.getName();
        }
        complete();
    }
}
BaseAction * Order:: clone() {
    return new Order(tableId);
}
std::string Order::toString() const {
    std::string output = "open" + tableId + this->getStatus();
}

#include "../include/Action.h"

//
// Created by USER on 11/7/2018.
//
Order::Order(int id): tableId(id){}
void Order::act(Restaurant &restaurant) {}
std::string Order::toString() const {
    std::string output = "open" + tableId + this->getStatus();

}
“Table does not exist or is not open”.
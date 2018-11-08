//
// Created by liad on 11/8/18.
//
#include "../include/Action.h"
#include "../include/Restaurant.h"
extern Restaurant * backup;
RestoreResturant::RestoreResturant() {}
void RestoreResturant :: act(Restaurant &restaurant){
    restaurant = *backup; //copy operator
}
std::string RestoreResturant:: toString() const{}
BaseAction * RestoreResturant :: clone(){}
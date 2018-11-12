//
// Created by liad on 11/8/18.
//
#include "../include/Action.h"
#include "../include/Restaurant.h"
extern Restaurant * backup;
void RestoreResturant :: act(Restaurant &restaurant){
    if(backup == nullptr)
        error("No backup available");
    else {
        restaurant.operator=(*backup); //copy operator
        complete();
    }
}
std::string RestoreResturant:: toString() const{
    std::string output = "restore";
    if( getStatus() == COMPLETED){
        output = output + "Completed";
    }
    if(getStatus() == ERROR){
        output = output + getErrorMsg();
    }
}
BaseAction * RestoreResturant:: clone() {
    BaseAction * restore = new RestoreResturant();
    restore  -> CloneBase(getErrorMsg(), getStatus());
    return restore;
}
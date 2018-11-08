//
// Created by liad on 11/8/18.
//
#include "../include/Action.h"
#include "../include/Restaurant.h"
extern Restaurant * backup;
BackupRestaurant :: BackupRestaurant(){}
void BackupRestaurant :: act(Restaurant &restaurant){
    backup = new Restaurant(restaurant);
    complete();
}
std::string BackupRestaurant :: toString() const{
    return "backup Completed";
}
BaseAction * BackupRestaurant :: clone(){}

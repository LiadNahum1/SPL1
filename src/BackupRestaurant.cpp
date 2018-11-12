//
// Created by liad on 11/8/18.
//
#include "../include/Action.h"
#include "../include/Restaurant.h"
extern Restaurant * backup;

void BackupRestaurant :: act(Restaurant &restaurant){
    if(backup== nullptr)
        backup = new Restaurant(restaurant);
    else
        backup->operator=(restaurant);
    complete();
}
std::string BackupRestaurant :: toString() const{
    return "backup Completed";
}
BaseAction * BackupRestaurant:: clone() {
    BaseAction * backupC = new BackupRestaurant();
    backupC  -> CloneBase(getErrorMsg(), getStatus());
    return backupC;
}
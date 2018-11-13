//
// Created by USER on 11/6/2018.
//
#include "../include/Action.h"
#include "../include/Restaurant.h"

PrintActionsLog::PrintActionsLog() {}
void PrintActionsLog::act(Restaurant &restaurant) {
    std::vector<BaseAction*> actions = restaurant.getActionsLog();
    for (int i = 0; i < actions.size(); ++i) {
        std::cout << actions.at(i)->toString()<< endl;
    }
    complete();
}
BaseAction * PrintActionsLog:: clone() {
    BaseAction * actionsLog = new PrintActionsLog();
    actionsLog  -> CloneBase(getErrorMsg(), getStatus());
    return actionsLog ;
}
std::string PrintActionsLog::toString() const {
    return "log Completed";
}

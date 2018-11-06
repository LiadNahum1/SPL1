//
// Created by USER on 11/6/2018.
//
#include "../include/Action.h"
#include "../include/Restaurant.h"

PrintActionsLog::PrintActionsLog() {}
void PrintActionsLog::act(Restaurant &restaurant) {
    std::vector<BaseAction*> actions = restaurant.getActionsLog(); //should it be refrens TODO
    for (int i = 0; i < actions.size(); ++i) {
        std::cout << actions.at(i)->toString();
    }
}
std::string PrintActionsLog::toString() const {}

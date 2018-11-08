//
// Created by liad on 11/5/18.
//
#include <string>
#include <iostream>
#include "../include/Action.h"
#include "../include/Restaurant.h"

PrintMenu :: PrintMenu(){}
void PrintMenu :: act(Restaurant &restaurant) {
    vector<Dish> &menu = restaurant.getMenu();
    for (int i = 0; i < menu.size() ; ++i) {
        cout << menu.at(i).getName() + " " ;
        cout << menu.at(i).getType() + " " ;
        cout << menu.at(i).getPrice() + "NIS" << endl;
    }
}
std::string PrintMenu :: toString() const {
    return "PrintMenu Completed" ;

}

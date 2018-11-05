//
// Created by liad on 11/5/18.
//



#include "../include/Customer.h"
#include <iostream>
using namespace std;

AlchoholicCustomer ::AlchoholicCustomer(std::string name, int id): Customer(name, id), prevPrice(0){}
std::vector<int> AlchoholicCustomer :: order(const std::vector<Dish> &menu){
    vector<int> orderId;
    int id(-1);
    bool findAlc = false;
    for (int i = 0; i < menu.size(); ++i) {
        if (menu.at(i).getType() == ALC & menu.at(i).getPrice() > prevPrice) {
            if (!findAlc) {
                id = menu.at(i).getId();
                prevPrice = menu.at(i).getPrice();
                findAlc = true;
            }
            else {
                if (menu.at(i).getPrice() == prevPrice & menu.at(i).getId() < id)
                    id = menu[i].getId();
            }
        }
    }

    if(findAlc){
        orderId.push_back(id);
    }
    return orderId;
}
std::string AlchoholicCustomer :: toString() const{
    return getName() + "," + "alc";
}


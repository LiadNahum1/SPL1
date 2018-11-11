//
// Created by liad on 11/5/18.
//



#include "../include/Customer.h"
#include <iostream>
using namespace std;

AlchoholicCustomer ::AlchoholicCustomer(std::string name, int id): Customer(name, id), prevId(-1),prevPrice(0){}
std::vector<int> AlchoholicCustomer :: order(const std::vector<Dish> &menu){
    vector<int> orderId;
    int idNextCheapest(-1);
    bool findAlc = false;
    int nextPrice(0);
    //find the next alchoholic beverage that is more expensive than prevPrice
    //for the first order prevPrice = 0 ;
    for (int i = 0; i < menu.size() & !findAlc; ++i) {
        if (menu.at(i).getType() == ALC & menu.at(i).getPrice() > prevPrice & menu.at(i).getId() != prevId) {
            idNextCheapest = menu.at(i).getId();
            nextPrice = menu.at(i).getPrice();
            findAlc = true;
        }
    }
    if(idNextCheapest != -1) {//alchoholic beverage was found
        //find the cheapest one from the ones who are more expensive than prevPrice
        for (int j = 0; j < menu.size(); ++j) {
            if(menu.at(j).getType() == ALC & menu.at(j).getPrice() == prevPrice & menu.at(j).getId() > prevId){
                idNextCheapest = menu.at(j).getId();
                nextPrice = prevPrice;
            }
            else if (menu.at(j).getType() == ALC & menu.at(j).getPrice() > prevPrice & menu.at(j).getPrice() < nextPrice) {
                idNextCheapest = menu.at(j).getId();
                nextPrice = menu.at(j).getPrice();
            }
           else if (menu.at(j).getType() == ALC & menu.at(j).getPrice() == nextPrice) {
                if (menu.at(j).getId() < idNextCheapest) {
                    idNextCheapest = menu.at(j).getId();
                }
            }
        }
        prevPrice = nextPrice;
        prevId = idNextCheapest;
        orderId.push_back(idNextCheapest);
    }
    return orderId;
}

Customer* AlchoholicCustomer::clone() {
    AlchoholicCustomer *al = new AlchoholicCustomer(this->getName(),this->getId());
    al->prevPrice = this->prevPrice;
    return al;
}
std::string AlchoholicCustomer :: toString() const{
    return getName() + "," + "alc";
}


//
// Created by liad on 11/5/18.
//

#include "../include/Customer.h"
#include <iostream>
using namespace std;

CheapCustomer :: CheapCustomer(std::string name, int id): Customer(name, id), orderOnce(false){}
std::vector<int> CheapCustomer :: order(const std::vector<Dish> &menu) {
    vector<int> orderId;
    if (!orderOnce) {
        int cheapestIdOrder(menu[0].getId());
        int cheapestPrice(menu[0].getPrice());
        for (int i = 0; i < (int)menu.size(); ++i) {
            if (menu[i].getPrice() < cheapestPrice) {
                cheapestIdOrder = menu[i].getId();
                cheapestPrice = menu[i].getPrice();
            }
        }
        orderId.push_back(cheapestIdOrder);
        orderOnce = true;
    }
    return orderId;

}

Customer* CheapCustomer::clone() {
    CheapCustomer *ch = new CheapCustomer(this->getName(),this->getId());
    ch->orderOnce = this->orderOnce;
    return ch;
}
std::string CheapCustomer :: toString() const{
    return getName() + "," + "chp";
}
//
// Created by liad on 11/4/18.
//

#include "Customer.h"
#include <iostream>
using namespace std;

CheapCustomer :: CheapCustomer(std::string name, int id): Customer(name, id), orderOnce(false){}
std::vector<int> CheapCustomer :: order(const std::vector<Dish> &menu) {
    vector<int> orderId(1);
    if (!orderOnce) {
        int cheapestIdOrder(menu[0].getId());
        int cheapestPrice(menu[0].getPrice());
        for (int i = 0; i < menu.size(); ++i) {
            if (menu[i].getPrice() < cheapestPrice) {
                cheapestIdOrder = menu[i].getId();
                cheapestPrice = menu[i].getPrice();
            }
        }
        orderId.push_back(cheapestIdOrder);
    }
        return orderId;

}
std::string CheapCustomer :: toString() const{

}

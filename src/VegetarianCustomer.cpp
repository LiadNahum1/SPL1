//
// Created by liad on 11/5/18.
//

#include "../include/Customer.h"
#include <iostream>
using namespace std;


VegetarianCustomer :: VegetarianCustomer(std::string name, int id): Customer(name, id){}

std::vector<int> VegetarianCustomer :: order(const std::vector<Dish> &menu){
    vector<int> orders(2); // assign two orders
    //vegetarian dish with the smallest id in the menu
    int minId(-1);
    bool findFirstVeg(false);
    for (int i = 0; i < menu.size(); ++i) {
        if (menu[i].getType() == VEG) {
            if (!findFirstVeg) {
                findFirstVeg = true;
                minId= menu[i].getId();
            }
            else {
                if (menu[i].getId() < minId)
                    minId = menu[i].getId();
            }
        }
    }
    if(findFirstVeg) {
        orders.push_back(minId);
        //the most expensive beverage (Non-alcoholic)
        int id(-1);
        int expensive(0);
        bool findFirstBev(false);
        for (int i = 0; i < menu.size(); ++i) {
            if (menu[i].getType() == BVG) {
                if (!findFirstBev) {
                    findFirstBev = true;
                    id = menu[i].getId();
                    expensive = menu[i].getPrice();
                } else {
                    if (menu[i].getPrice() > expensive) {
                        id = menu[i].getId();
                        expensive = menu[i].getPrice();
                    }
                    if (menu[i].getPrice() == expensive & menu[i].getId() < id) {
                        id = menu[i].getId();
                        expensive = menu[i].getPrice();
                    }

                }
            }
        }
        orders.push_back(id);
    }
    return orders;
}
std::string VegetarianCustomer :: toString() const{
    string customerDetails = Customer :: toString();
    customerDetails = customerDetails +"/n" + "Orders: ";


}
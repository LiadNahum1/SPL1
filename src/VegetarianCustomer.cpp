//
// Created by liad on 11/5/18.
//

#include "../include/Customer.h"
#include <iostream>
using namespace std;


VegetarianCustomer :: VegetarianCustomer(std::string name, int id): Customer(name, id){}

std::vector<int> VegetarianCustomer :: order(const std::vector<Dish> &menu){
    vector<int> orders;
    //vegetarian dish with the smallest id in the menu
    int minId(-1);
    bool findFirstVeg(false);
    for (int i = 0; i < (int)menu.size(); ++i) {
        if (menu.at(i).getType() == VEG) {
            if (!findFirstVeg) {
                findFirstVeg = true;
                minId= menu.at(i).getId();
            }
            else {
                if (menu.at(i).getId() < minId)
                    minId = menu.at(i).getId();
            }
        }
    }
    if(findFirstVeg) {
        orders.push_back(minId);
        //the most expensive beverage (Non-alcoholic)
        int id(-1);
        int expensive(0);
        bool findFirstBev(false);
        for (int i = 0; i < (int)menu.size(); ++i) {
            if (menu.at(i).getType() == BVG) {
                if (!findFirstBev) {
                    findFirstBev = true;
                    id = menu.at(i).getId();
                    expensive = menu.at(i).getPrice();
                } else {
                    if (menu.at(i).getPrice() > expensive) {
                        id = menu.at(i).getId();
                        expensive = menu.at(i).getPrice();
                    }
                    if ((menu.at(i).getPrice() == expensive) & (menu.at(i).getId() < id)) {
                        id = menu.at(i).getId();
                        expensive = menu.at(i).getPrice();
                    }

                }
            }
        }
        if(findFirstBev)
            orders.push_back(id);
    }
    return orders;
}
Customer* VegetarianCustomer::clone() {
    VegetarianCustomer *ve = new VegetarianCustomer(this->getName(),this->getId());
    return ve;}
std::string VegetarianCustomer :: toString() const{
    return getName() + "," + "veg";


}
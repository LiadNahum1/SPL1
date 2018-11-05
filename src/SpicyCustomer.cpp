//
// Created by liad on 11/4/18.
//

#include "Customer.h"
#include <iostream>
using namespace std;

SpicyCustomer :: SpicyCustomer(std::string name, int id): Customer(name, id), orderOnce(false){}
std::vector<int> SpicyCustomer :: order(const std::vector<Dish> &menu){
    vector<int> orderId(1);
    //the first time that the SpicyCustomer orders
    if(!orderOnce) {
        int id(-1);
        int expensive(0);
        bool findFirstSpc(false);
        for (int i = 0; i < menu.size(); ++i) {
            if (menu[i].getType() == SPC) {
                if (!findFirstSpc) {
                    findFirstSpc = true;
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
        if (findFirstSpc) {
            orderId.push_back(id);
        }
    }
    //next times
    else{
        int id(-1);
        int cheapest(menu[0].getPrice());
        bool findFirstBvg(false);
        for (int i = 0; i < menu.size(); ++i) {
            if (menu[i].getType() == BVG) {
                if (!findFirstBvg) {
                    findFirstBvg = true;
                    id = menu[i].getId();
                    cheapest = menu[i].getPrice();
                } else {
                    if (menu[i].getPrice() > cheapest) {
                        id = menu[i].getId();
                        cheapest = menu[i].getPrice();
                    }
                    if (menu[i].getPrice() == cheapest & menu[i].getId() < id) {
                        id = menu[i].getId();
                        cheapest = menu[i].getPrice();
                    }

                }
            }
        }
        if (findFirstBvg) {
            orderId.push_back(id);
        }

    }
    return orderId;
}
std::string SpicyCustomer :: toString() const{

}




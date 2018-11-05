//
// Created by liad on 11/4/18.
//

#include "Customer.h"
#include <iostream>
using namespace std;

AlchoholicCustomer ::AlchoholicCustomer(std::string name, int id): Customer(name, id){}
std::vector<int> AlchoholicCustomer :: order(const std::vector<Dish> &menu){
    vector<int> orderId(1);
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
    if(findFirstSpc){
        orderId.push_back(id);
    }
    return orderId;
}
std::string AlchoholicCustomer :: toString() const{

}



//
// Created by liad on 11/5/18.
//

#include <unordered_map>
#include <algorithm>
#include "../include/Table.h"
using namespace std;


Table :: Table(int t_capacity): capacity(t_capacity), open(false){}
int Table :: getCapacity() const{return capacity;};
void Table :: addCustomer(Customer* customer) {
    if(!isOpen()) {
        if (customersList.size() < getCapacity()) {
            customersList.push_back(customer);
        }
    }
}
Table::Table(const Table &other): open(other.open),capacity(other.capacity) {}
void Table :: removeCustomer(int id) {
    //remove customer
    for (int i = 0; i < customersList.size(); ++i) {
        if (customersList.at(i)->getId() == id) {
            //memory leak
            delete customersList.at(i);
            customersList.erase(customersList.begin() + i);
        }
    }

    //remove orders of this customer
    //for (int j = 0; j < orderList.size(); ++j) {
   //     if(orderList.at(j).first == id) {
     //       customersList.erase(customersList.begin() + j);
       //     j = j - 1;
        //}
    //}

        for (auto i = orderList.begin(); i != orderList.end(); ++i) {
            if((*i).first== id) {
                orderList.erase(i);
                i--;
            }
        }

    }

Customer* Table :: getCustomer(int id) {
    for (int i = 0; i < customersList.size(); ++i) {
        if(customersList.at(i)->getId() == id)
            return customersList.at(i);
    }
    return nullptr;
}
std::vector<Customer*>& Table :: getCustomers(){ return customersList;}

std::vector<OrderPair>& Table :: getOrders(){ return orderList;}
void Table :: order(const std::vector<Dish> &menu){
    vector<int>orders;
    for (int i = 0; i < customersList.size(); ++i) {
        orders = customersList.at(i)->order(menu); // orders of customer
        for (int j = 0; j < orders.size(); ++j) {
            for (int k = 0; k < menu.size(); ++k) {
                if(orders.at(j) == menu.at(i).getId()){
                    orderList.push_back(OrderPair(customersList.at(i)->getId(), menu.at(i)));
                }
            }

        }
    }
}
void Table :: openTable(){open = true;}
void Table :: closeTable(){
    open = false;
 //TODO should i erase the pointers themselves ?
        
   customersList.clear();
   orderList.clear();
}


int Table :: getBill(){
    int bill(0);
    for (int i = 0; i < orderList.size(); ++i) {
        bill = bill + orderList.at(i).second.getPrice();
    }
    return bill;
}
bool Table :: isOpen() { return open;}


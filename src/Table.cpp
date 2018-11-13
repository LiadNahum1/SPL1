//
// Created by liad on 11/5/18.
//


#include "../include/Table.h"
using namespace std;
#include <iostream>


Table :: Table(int t_capacity): capacity(t_capacity), open(false){}
int Table :: getCapacity() const{return capacity;}
void Table :: addCustomer(Customer* customer) {
        if (customersList.size() < getCapacity()) {
            customersList.push_back(customer->clone());
        }
}
//copy constructor
Table::Table(const Table &other): open(other.open),capacity(other.capacity),orderList(other.orderList) {
    for(int i = 0; i< other.customersList.size() ; i++){
        customersList.push_back(other.customersList.at(i)->clone());
    }
}

Table& Table::operator=(const Table &other)   {
    if(this != &other) {
        open = other.open;
        capacity = other.capacity;
        orderList = other.orderList;
        for (int i = 0; i < customersList.size(); i++) {
            delete (customersList.at(i));
            customersList.at(i) = nullptr;
        }
        customersList.clear();
        for (int i = 0; i < other.customersList.size(); i++) {
            customersList.push_back(other.customersList.at(i)->clone());
        }
    }
    return *this;
}
Table::~Table() {
    for(int i = 0; i< customersList.size() ; i++) {
        delete(customersList.at(i));
        customersList.at(i) = nullptr;
    }
    orderList.clear();
    customersList.clear();
}
Table::Table(Table &&other) : open(other.open),capacity(other.capacity),orderList(other.orderList),customersList(other.customersList){
    other.getCustomers().clear();

}
Table& Table::operator=(Table &&other) {
    if(this != &other) {
        for (int i = 0; i < customersList.size(); i++) {
            delete (customersList.at(i));
            customersList.at(i) = nullptr;
        }
        orderList.clear();
        customersList.clear();
        open = other.open;
        capacity = other.capacity;
        orderList = other.orderList;
        customersList = other.customersList;
        other.customersList.clear();
    }
    return *this;
}
void Table :: removeCustomer(int id) {
    //remove customer
    for (int i = 0; i < customersList.size(); i = i+1) {
        if (customersList.at(i)->getId() == id) {
            delete customersList.at(i);
            customersList.at(i) = nullptr;
            customersList.erase(customersList.begin() + i);
        }
    }
    //remove orders of this customer
    vector<OrderPair> ordersTemp; 
    for (int j = 0; j < orderList.size(); j=j+1) {
        if (orderList.at(j).first != id) {
          ordersTemp.push_back(orderList.at(j));
        }
    }
    orderList.clear();
    for (int l = 0; l < ordersTemp.size(); ++l) {
        orderList.push_back(ordersTemp.at(l));
    }

}

Customer* Table :: getCustomer(int id) {
    for (int i = 0; i < customersList.size(); ++i) {
        if(customersList.at(i)->getId() == id)
            return customersList.at(i);
    }
    return nullptr;
}
vector<Customer *> & Table :: getCustomers() { return customersList;}

std::vector<OrderPair>& Table :: getOrders(){ return orderList;}

void Table :: order(const std::vector<Dish> &menu){
    vector<int>orders;
    for (int i = 0; i < customersList.size(); ++i) {
        orders = customersList.at(i)->order(menu); // id of orders of customer
        for (int j = 0; j < orders.size(); ++j) {
            for (int k = 0; k < menu.size(); ++k) {
                if(orders.at(j) == menu.at(k).getId()) {
                    orderList.push_back(OrderPair(customersList.at(i)->getId(), menu.at(k)));
                    std::cout << customersList.at(i)->getName() + " ordered " + menu.at(k).getName() << endl;
                }

            }

        }
    }
}
void Table :: openTable(){open = true;}
void Table :: closeTable(){
    open = false;
    for (int i = 0; i < customersList.size(); ++i) {
        delete customersList.at(i);
        customersList.at(i) = nullptr;
    }
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


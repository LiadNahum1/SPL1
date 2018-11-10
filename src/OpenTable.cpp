//
// Created by USER on 11/5/2018.
//

#include "../include/Action.h"
#include "../include/Table.h"
#include "../include/Restaurant.h"
using namespace std;
OpenTable::OpenTable(int id, std::vector<Customer *> &customersList) : tableId(id),customers(customersList){}
//OpenTable::OpenTable(const OpenTable &other) {
  //  BaseAction * orderC = new Order(tableId);
    //orderC ->CloneBase(getErrorMsg(), getStatus());
//}

void OpenTable::act(Restaurant &restaurant) {
    Table * t =restaurant.getTable(tableId);
    if(t == nullptr || t->isOpen()) {
        error("Table does not exist or is already open");
    }
    else{
        for(int i = 0;i<customers.size();i++){
            t->addCustomer(customers[i]);
        }

        t->openTable();
        complete();
    }

}

BaseAction * OpenTable:: clone() {
    vector<Customer *> customersNew;
    for (int i = 0; i < customers.size(); ++i) {
        customersNew.push_back(customers.at(i)->clone());
    }
    BaseAction * openC =  new OpenTable(tableId, customersNew);
    openC -> CloneBase(getErrorMsg(), getStatus());
    return openC;

}
OpenTable::OpenTable(const OpenTable &other):tableId(other.tableId) { //whay not working
    for (int i = 0; i < other.customers.size(); ++i) {
        customers.push_back(other.customers.at(i)-> clone()); // how to deal with the const
    }
}
OpenTable::~OpenTable() {
    for (int j = 0; j < customers.size(); ++j) {
        delete customers.at(j);
    }
    this->customers.clear();//is it must
}
OpenTable& OpenTable::operator=(const OpenTable &other) {
    if(this != &other) {
        this->tableId = other.tableId; //const problem
        for (int i = 0; i < customers.size(); ++i) {
            delete customers.at(i);
        }
        customers.clear();
        for (int i = 0; i < other.customers.size(); ++i) {
            customers.push_back(other.customers.at(i)-> clone()); // how to deal with the const
        }
    }

}
std::string OpenTable::toString() const {
    std::string output = "open";
    output = output + std::to_string(tableId) + " ";
    for(int i = 0; i<customers.size(); i++){
        output = output + customers[i]->toString() + ",";
    }
    output.substr(0,output.size()-2);
    if( getStatus() == COMPLETED){
        output = output + "Completed";
    }
    if(getStatus() == ERROR){
        output = output + getErrorMsg();
    }
    return output;
}

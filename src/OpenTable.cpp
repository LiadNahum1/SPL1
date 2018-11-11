//
// Created by USER on 11/5/2018.
//

#include "../include/Action.h"
#include "../include/Table.h"
#include "../include/Restaurant.h"
using namespace std;
OpenTable::OpenTable(int id, std::vector<Customer *> &customersList) : tableId(id),customers(customersList){

}

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

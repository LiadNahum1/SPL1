//
// Created by liad on 11/5/18.
//

#include "../include/Action.h"
#include "../include/Table.h"
#include <iostream>
using namespace std;


MoveCustomer :: MoveCustomer(int src, int dst, int customerId): srcTable(src), dstTable(dst), id(customerId){}
void MoveCustomer :: act(Restaurant &restaurant){
    Table * tableSrc = restaurant.getTable(srcTable);
    Table * tableDst = restaurant.getTable(dstTable);
    if((tableSrc == nullptr | tableDst == nullptr) ||!tableSrc->isOpen() | !tableDst->isOpen()){
        error("Cannot move customer");
    }
    else {
        Customer *customer = tableSrc->getCustomer(id);
        if(customer == nullptr | tableDst->getCustomers().size() == tableDst->getCapacity()){
            error("Cannot move customer");
        }
        else {
            tableDst->addCustomer(customer);
            vector<OrderPair> &ordersSrc = tableSrc->getOrders();
            vector<OrderPair> &ordersDst = tableDst->getOrders();

            for (int i = 0; i < ordersSrc.size(); ++i) {
                if(ordersSrc.at(i).first == id) {

                    ordersDst.push_back(ordersSrc.at(i));
                }
            }

            tableSrc->removeCustomer(id); //should erase the orders of him
            if (tableSrc->getCustomers().size() == 0) { //empty table
                tableSrc->closeTable();
            }
            complete();
        }
    }
}
std::string MoveCustomer :: toString() const{
    std:string output = "MoveCustomer" + std::to_string(srcTable) + " " + std::to_string(dstTable)+ " " + std::to_string(id) + " ";
    if( getStatus() == COMPLETED){
        output = output + "Completed";
    }
    if(getStatus() == ERROR){
        output = output + getErrorMsg();
    }

}

//
// Created by liad on 11/6/18.
//

#include "../include/Action.h"
#include "../include/Table.h"

PrintTableStatus :: PrintTableStatus(int id):tableId(id){}
void PrintTableStatus  :: act(Restaurant &restaurant){
    Table * t = restaurant.getTable(i);
    //status
    cout << "Table " << tableId<< " status: ";
    if(t->isOpen()){
        cout << "open"<< endl;
    }
    else
        cout<< "close"<< endl;
    //customers
    cout<< "Customers:"<< endl;
    vector<Customer *>& customers = t->getCustomers();
    for (int i = 0; i < customers.size(); ++i) {
        cout << customers.at(i)->getId() + " " + customers.at(i)->getName()<< endl;
    }
    //orders
    cout<< "Orders:"<< endl;
    vector<OrderPair>& orders = t->getOrders();
    for (int i = 0; i < orders.size(); ++i) {
        cout << orders.at(i).second.getName() + " " << orders.at(i).second.getPrice()<< "NIS" + orders.at(i).first << endl;
    }
    complete();
}
std::string PrintTableStatus :: toString() const{
    return "PrintTableStatus Completed" ;
}

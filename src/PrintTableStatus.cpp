//
// Created by liad on 11/6/18.
//

#include "../include/Action.h"
#include "../include/Table.h"
#include "../include/Restaurant.h"

PrintTableStatus :: PrintTableStatus(int id):tableId(id){}
void PrintTableStatus  :: act(Restaurant &restaurant){
    Table * t = restaurant.getTable(tableId);
    //status
    cout << "Table " << tableId<< " status: ";
    if(t->isOpen()){
        cout << "open"<< endl;
        //customers
        cout<< "Customers:"<< endl;
        vector<Customer *>& customers = t->getCustomers();
        for (int i = 0; i < customers.size(); ++i) {
            cout << std::to_string(customers.at(i)->getId()) + " " + customers.at(i)->getName()<< endl;
        }
        //orders
        cout<< "Orders:"<< endl;
        vector<OrderPair>& orders = t->getOrders();
        for (int i = 0; i < orders.size(); ++i) {
            cout << orders.at(i).second.getName() + " " << orders.at(i).second.getPrice()<< "NIS "<< orders.at(i).first << endl;
        }
        //print bill
        cout<< "Current Bill: "<< t->getBill()<< "NIS"<<endl;
    }
    else
        cout<< "closed"<< endl ;

    complete();
}
BaseAction * PrintTableStatus:: clone() {
    BaseAction * tableStatus = new PrintTableStatus(tableId);
    tableStatus  -> CloneBase(getErrorMsg(), getStatus());
    return tableStatus ;
}
std::string PrintTableStatus :: toString() const{
    return "status " + std::to_string(tableId)+ " Completed";
}

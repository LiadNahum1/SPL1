//
// Created by liad on 11/5/18.
//

#include "../include/Action.h"
#include "../include/Table.h"
#include "../include/Restaurant.h"




Close :: Close(int id): tableId(id){}
void Close :: act(Restaurant &restaurant)
{
    Table * table = restaurant.getTable(tableId);
    if(table == nullptr || !table->isOpen()){
        error("Table does not exist or is not open.");
    }
    else
    {
        cout << "Table "<< tableId << " was closed. Bill " << table->getBill() <<"NIS" <<endl;
        table->closeTable();
        complete();
    }

}
BaseAction * Close:: clone() {
    BaseAction * closeC =  new Close(tableId);
    closeC-> CloneBase(getErrorMsg(), getStatus());
    return closeC;

}

std::string Close :: toString() const{
    string output = "close " + to_string(tableId) + " ";
    if( getStatus() == COMPLETED){
        output = output + "Completed";
    }
    if(getStatus() == ERROR){
        output = output + getErrorMsg();
    }
    return output;
}

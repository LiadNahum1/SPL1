//
// Created by liad on 11/5/18.
//

#include "../include/Action.h"
#include "../include/Table.h"



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

}

std::string Close :: toString() const{
    std:string output = "close " + std::to_string(tableId) + " ";
    if( getStatus() == COMPLETED){
        output = output + "Completed";
    }
    if(getStatus() == ERROR){
        output = output + getErrorMsg();
    }
    return output;
}

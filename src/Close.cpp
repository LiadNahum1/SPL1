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
        table->closeTable();
    }
}
std::string Close :: toString() const{
}
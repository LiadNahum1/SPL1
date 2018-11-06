//
// Created by liad on 11/5/18.
//

#include "../include/Action.h"


Close :: Close(int id): tableId(id){}
void Close :: act(Restaurant &restaurant)
{
    Table * table = restaurant.getTable(tableId);
    if(table == nullptr || !table->isOpen()){
        error("Table does not exist or is not open.");
        //need to continue 
    }
}
std::string Close :: toString() const{
    return "Table " + std::to_string(tableId) + " was closed. " + "Bill: " +  "NIS";
}
class Close : public BaseAction {
public:
    Close(int id);


private:
    const int tableId;
};
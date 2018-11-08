//
// Created by liad on 11/6/18.
//

#include "../include/Action.h"
#include "../include/Table.h"
#include "../include/Restaurant.h"


CloseAll :: CloseAll(){}
void CloseAll :: act(Restaurant &restaurant){
    for (int i = 0; i < restaurant.getNumOfTables(); ++i) {
        Table *t = restaurant.getTable(i);
        if (t->isOpen()) {
            Close closeO(i);
            closeO.act(restaurant); //TODO earse from heap?
        }
    }

    delete &restaurant;
complete();
}
BaseAction * CloseAll:: clone() {
    BaseAction * closeAllC =  new CloseAll();
    closeAllC -> CloneBase(getErrorMsg(), getStatus());
    return closeAllC;

}
std::string CloseAll :: toString() const {
    return "CloseAll Completed" ;

}

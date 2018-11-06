//
// Created by liad on 11/5/18.
//

#ifndef SPL_1_RESTAURANT_H
#define SPL_1_RESTAURANT_H


#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"


class Restaurant{
public:
    Restaurant();;
    Restaurant(const std::string &configFilePath);
    Restaurant(const Restaurant & other) ;
    virtual ~Restaurant();
    Restaurant &operator=(const Restaurant &other);
    Restaurant(Restaurant && other);
    Restaurant & operator=(Restaurant && other);
    void start();
    int getNumOfTables() const;
    Table* getTable(int ind) const;
    const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Dish>& getMenu();


private:
    bool open;
    std::vector<Table*> tables;
    std::vector<Dish> menu;
    std::vector<BaseAction*> actionsLog
    void openTable(std::string a , int tableNum);
};

#endif
//
// Created by lishay on 11/2/18.
//
#include <iostream>
#include "../include/Restaurant.h"
#include <fstream>

using namespace std;


Restaurant::Restaurant(const std::string &configFilePath):open(true)
{   int numTables = 0;
    int dishNum = 0;
    bool tableDe = false;
    bool tableNum = false;
    bool menuDe = false;
    ifstream nameFileout;
    nameFileout.open(configFilePath);
    string line;
    while(std::getline(nameFileout, line))
    {
        if(tableDe & !line.empty()) {
            openTable(line , numTables);
            tableDe = false;
        }
        if(tableNum & !line.empty()) {
            numTables = atoi(line.c_str());
            tableNum = false;
        }
        if(menuDe & !line.empty()) {
            DishType ty();//check if is the right way
            string dish []  = line.split(",");
            if(dish[2] == "VEG")
                ty = VEG;
            if(dish[2] == "SPC")
                ty = SPC;
            if(dish[2] == "BVG")
                ty = BVG;
            if(dish[2] == "ALC")
                ty = ALC;
            menu.push_back(Dish(dishNum,dish[0], atoi(dish[1].c_str())), ty)//how to convert an enum to string
        }

        if(line == "#Menu")
            menuDe = true;

        if(line == "#number of tables")
            tableNum = true;

        if(line == "#tables description")
            tableDe = true;
    }
}
//copy constructor
Restaurant :: Restaurant(const Restaurant & other) : open(other.open), menu(other.menu) {
    for (int i = 0; i < other.getNumOfTables(); ++i) {
        tables.push_back(new Table(* other.getTable(i)));
    }
    for (int i = 0; i < other.getActionsLog().size(); ++i) {
        actionsLog.push_back(other.getActionsLog().at(i)-> clone()); //TODO
    }
}
//destruction
 Restaurant :: ~Restaurant(){
    menu.clear();
     for (int i = 0; i < tables.size(); ++i) {
         delete tables.at(i);
     }
     tables.clear();
     for (int j = 0; j < actionsLog.size(); ++j) {
         delete actionsLog.at(i);
     }
     actionsLog.clear();

}
//copy = operator
Restaurant & Restaurant ::operator=(const Restaurant &other){
    if(this != &other){
        open = other.open;
        menu = other.menu;
        for (int i = 0; i < tables.size(); ++i) {
            delete tables.at(i);
        }
        tables.clear();
        for (int j = 0; j < actionsLog.size(); ++j) {
            delete actionsLog.at(i);
        }
        actionsLog.clear();

        for (int i = 0; i < other.getNumOfTables(); ++i) {
            tables.push_back(new Table( * other.getTable(i)));
        }
        for (int i = 0; i < other.getActionsLog().size(); ++i) {
            actionsLog.push_back(other.getActionsLog().at(i)-> clone()); //TODO
        }
    }
}
//move constructor
Restaurant :: Restaurant(Restaurant && other): open(other.open), menu(other.menu), tables(other.tables), actionsLog(other.actionsLog){
    other.tables.clear();
    other.actionsLog.clear();
}
Restaurant & Restaurant :: operator=(Restaurant && other){

}
void Restaurant::start() {
}
void Restaurant::openTable(std::string input , int tableNum) { //dane
    std::vector<std::string> v;

    split( "This  is a  test", v, "," );
    dump( cout, v );
    for (int i = 0; i < nums.lenght; i++) { //this will create tables
        tableSize  = atoi(nums[i].c_str());
        tables.push_back( new Table(tableSize));
    }
}
Table* Restaurant::getTable(int ind) const{
    return tables[ind];//dane
}

int Restaurant::getNumOfTables() const { return tables.size();} //dane

const std::vector<BaseAction *> & Restaurant::getActionsLog() const { return actionsLog;}//dane

std::vector<Dish> & Restaurant::getMenu() { return menu;}//dane


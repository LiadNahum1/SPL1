//
// Created by lishay on 11/2/18.
//

#include "../include/Restaurant.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


Restaurant::Restaurant(const std::string &configFilePath):open(true)
{

    int numTables(0);
    int dishNum(0);
    bool tableDe(false);
    bool tableNum(false);
    bool menuDe(false);
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
            DishType ty; //check if is the right way
            int firstCommaInd(line.find_first_of(","));
            int lastCommaInd(line.find_last_of(","));
            string d_name(line.substr(0, firstCommaInd));
            string d_type(line.substr(lastCommaInd));
            if(d_type == "VEG")
                ty = VEG;
            if(d_type == "SPC")
                ty = SPC;
            if(d_type == "BVG")
                ty = BVG;
            if(d_type == "ALC")
                ty = ALC;

            menu.push_back(Dish(dishNum,d_name, atoi((line.substr(firstCommaInd + 1, lastCommaInd)).c_str()), ty));
            dishNum = dishNum + 1;
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
            delete actionsLog.at(j);
        }
        actionsLog.clear();

        for (int i = 0; i < other.getNumOfTables(); ++i) {
            tables.push_back(new Table( * other.getTable(i)));
        }
        for (int i = 0; i < other.getActionsLog().size(); ++i) {
            actionsLog.push_back(other.getActionsLog().at(i)-> clone()); //TODO
        }
    }
    return *this;
}
//move constructor
Restaurant :: Restaurant(Restaurant && other): open(other.open), menu(other.menu), tables(other.tables), actionsLog(other.actionsLog){
    other.tables.clear();
    other.actionsLog.clear();
}

//move operator
Restaurant & Restaurant :: operator=(Restaurant && other){
    if(this != &other){
        open = other.open;
        menu = other.menu;
        other.menu.clear();
        for (int i = 0; i < tables.size(); ++i) {
            delete tables.at(i);
        }
        tables.clear();
        tables = other.tables;
        other.tables.clear();

        for (int j = 0; j < actionsLog.size(); ++j) {
            delete actionsLog.at(i);
        }
        actionsLog.clear();
        actionsLog = other.actionsLog;
        other.actionsLog.clear();
    }
    return *this;

}
void Restaurant::start() {
    cout<<"Restaurant is now open!"<< endl;

    std::string actionToExecute("");
    std::string action("");
    while(action != "closeall"){
        getline (cin, actionToExecute);
        BaseAction * act = nullptr;
        std::istringstream tokens (actionToExecute);
        tokens>> action;
        int t_id;
        if(action == "open"){
            tokens >> t_id;
            vector<Customer *> customers;
            int c_id(0);
            while(tokens){
                std:: string c_details;
                std::string c_name;
                std :: string strategy;
                tokens >> c_details;
                if(c_details != "") {
                    c_name = c_details.substr(0, c_details.find(","));
                    strategy = c_details.substr(c_details.find(",") + 1);
                    if (strategy == "VEG")
                        customers.push_back(new VegetarianCustomer(c_name, c_id));
                    if (strategy == "SPC")
                        customers.push_back(new SpicyCustomer(c_name, c_id));
                    if (strategy == "CHP")
                        customers.push_back(new CheapCustomer(c_name, c_id));
                    if (strategy == "ALC")
                        customers.push_back(new AlchoholicCustomer(c_name, c_id));
                    c_id = c_id + 1;
                }
            }
            act = new OpenTable(t_id, customers);

        }
        if(action == "order"){
            tokens >> t_id;
            act = new Order(t_id);
        }

        if(action == "move"){
            int origin_id;
            int dst_id;
            int c_id;
            tokens >> origin_id;
            tokens >> dst_id;
            tokens >> c_id;
            act = new MoveCustomer(origin_id, dst_id, c_id);
        }

        if(action == "close"){
            tokens >> t_id;
            act = new Close(t_id);
        }

        if(action == "menu"){
            act = new PrintMenu();
        }
        if(action == "status"){
            tokens >> t_id;
            act = new PrintTableStatus(t_id);
        }
        if(action == "log"){
            act = new PrintActionsLog();
        }
        if(action == "backup"){
            act = new BackupRestaurant();
        }
        if(action == "restore"){
            act = new RestoreResturant();
        }
        actionsLog.push_back(act);
        act->act(*this);


    }

}
void Restaurant::openTable(std::string input , int numTables) { //dane
    tables.resize(numTables);
    int beginInd(0);
    int commaInd;
    int capacity;
    while(input != "") {

        commaInd = input.find_first_of(",");
        capacity = atoi(input.substr(beginInd, commaInd).c_str());
        tables.push_back(new Table(capacity));
        input = input.substr(commaInd + 1);
        beginInd = commaInd + 1;
    }
}
Table* Restaurant::getTable(int ind){
    return tables[ind];//dane
}

int Restaurant::getNumOfTables() const { return tables.size();} //dane

const std::vector<BaseAction *> & Restaurant::getActionsLog() const { return actionsLog;}//dane

std::vector<Dish> & Restaurant::getMenu() { return menu;}//done


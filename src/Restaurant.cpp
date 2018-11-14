//
// Created by lishay on 11/2/18.
//

#include "../include/Restaurant.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>

using namespace std;


Restaurant::Restaurant(const std::string &configFilePath):open(false), tables(), menu(),actionsLog()
{
    int numTables(0);
    int dishNum(0);

    string line;
    vector < string > lines;
    ifstream file;
    file.open (configFilePath);
    int i(1);
    if (file.is_open( )) {
        while (getline(file, line)) {
            if (!line.empty() && line[0] == '#') {
                if (i == 1) {// number of tables

                    getline(file, line);
                    numTables = atoi(line.c_str());
                    i = i + 1;
                }
                else if (i == 2) { //tables description
                    getline(file, line);
                    openTable(line, numTables);
                    i = i + 1;
                }
                else if (i == 3) {//Menu
                    while (getline(file, line)) {
                        DishType ty; //check if is the right way
                        int firstCommaInd(line.find_first_of(','));
                        int lastCommaInd(line.find_last_of(','));
                        string d_name(line.substr(0, firstCommaInd));
                        string d_type(line.substr(firstCommaInd + 1, lastCommaInd-firstCommaInd-1));
                        if (d_type == "VEG")
                            ty = VEG;
                        if (d_type == "SPC")
                            ty = SPC;
                        if (d_type == "BVG")
                            ty = BVG;
                        if (d_type == "ALC"){
                            ty = ALC;
                        }


                        Dish dish1 = Dish(dishNum, d_name, atoi((line.substr(lastCommaInd+1)).c_str()),ty);
                        menu.push_back(dish1);
                        dishNum = dishNum + 1;
                    }

                }
            }
        }
    }

    file.close();
}
//copy constructor
Restaurant :: Restaurant(const Restaurant & other) : open(other.open), tables(), menu(other.menu), actionsLog() {
    for (int i = 0; i < other.getNumOfTables(); ++i) {
        tables.push_back(new Table(*other.tables.at(i)));
    }
    for (int i = 0; i < (int)other.getActionsLog().size(); ++i) {
        actionsLog.push_back(other.getActionsLog().at(i)-> clone());
    }
}
//destruction
 Restaurant :: ~Restaurant(){
    menu.clear();
     for (int i = 0; i < (int)tables.size(); ++i) {
         delete tables.at(i);
     }
     tables.clear();
     for (int j = 0; j < (int)actionsLog.size(); ++j) {
         delete actionsLog.at(j);
     }
     actionsLog.clear();

}
//copy = operator
Restaurant & Restaurant ::operator=(const Restaurant &other){
    if(this != &other){
        open = other.open;
        menu.clear();
        for (int k = 0; k <(int)other.menu.size() ; ++k) {
            menu.push_back(Dish(other.menu.at(k).getId(),other.menu.at(k).getName(), other.menu.at(k).getPrice(), other.menu.at(k).getType()));
        }
        for (int i = 0; i < (int)tables.size(); ++i) {
            delete tables.at(i);
        }
        tables.clear();
        for (int j = 0; j < (int)actionsLog.size(); ++j) {
            delete actionsLog.at(j);
        }
        actionsLog.clear();
        for (int i = 0; i < other.getNumOfTables(); ++i) {
            tables.push_back(new Table( * other.tables.at(i)));
        }
        for (int i = 0; i < (int)other.getActionsLog().size(); ++i) {
            actionsLog.push_back(other.getActionsLog().at(i)-> clone());
        }
    }
    return *this;
}
//move constructor
Restaurant :: Restaurant(Restaurant && other): open(other.open),tables(other.tables), menu(other.menu), actionsLog(other.actionsLog){
    other.tables.clear();
    other.actionsLog.clear();
}
//move operator
Restaurant & Restaurant :: operator=(Restaurant && other){
    if(this != &other){
        open = other.open;
        menu.clear();
        for (int k = 0; k <(int)other.menu.size() ; ++k) {
            menu.push_back(Dish(other.menu.at(k).getId(),other.menu.at(k).getName(), other.menu.at(k).getPrice(), other.menu.at(k).getType()));
        }
        other.menu.clear();
        for (int i = 0; i < (int)tables.size(); ++i) {
            delete tables.at(i);
        }
        tables.clear();
        tables = other.tables;
        other.tables.clear();

        for (int j = 0; j < (int)actionsLog.size(); ++j) {
            delete actionsLog.at(j);
        }
        actionsLog.clear();
        actionsLog = other.actionsLog;
        other.actionsLog.clear();
    }
    return *this;

}
void Restaurant::start() {
    open = true;
    cout<<"Restaurant is now open!"<< endl;

    std::string actionToExecute("");
    std::string action("");
    int c_id(0);
    //ask for actions from the user
    while(action != "closeall"){
        getline (cin, actionToExecute);
        BaseAction * act = nullptr;
        std::istringstream tokens (actionToExecute);
        tokens>> action ;
        int t_id;

        if(action == "open") {
            tokens >> t_id;
            vector<Customer *> customers;
            while (tokens) {
                std::string c_details;
                std::string c_name;
                std::string strategy;
                tokens >> c_details;
                //creates the customers
                if (!c_details.empty()) {
                    c_name = c_details.substr(0, c_details.find(","));
                    strategy = c_details.substr(c_details.find(",") + 1);
                    Customer * customer;
                    if (strategy.compare("veg") == 0)
                        customer = new VegetarianCustomer(c_name, c_id);
                    else if (strategy.compare("spc") == 0)
                        customer = new SpicyCustomer(c_name, c_id);
                    else if (strategy.compare("chp") == 0)
                        customer = new CheapCustomer(c_name, c_id);
                    else
                        customer = new AlchoholicCustomer(c_name, c_id);
                    customers.push_back(customer);
                    c_id = c_id + 1;
                }

            }

            act = new OpenTable(t_id, customers);
            act->act(*this);
            actionsLog.push_back(act);
            if(act->getStatus() == ERROR){
                c_id = c_id - (int)customers.size();
            }

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
        if(action == "closeall") {
            act = new CloseAll();
        }
        if((act != nullptr) & (action != "open")) {
            act->act(*this);
            actionsLog.push_back(act);
        }
    }

}
void Restaurant::openTable(std::string input , int numTables) { //dane
    int commaInd(0);
    int beginInd(0);
    int capacity(0);
    for (int i = 0; i < (int)input.length(); ++i) {
        if(input[i] == ','){
            commaInd = i;
            capacity = atoi(input.substr(beginInd, commaInd-beginInd).c_str());
            tables.push_back(new Table(capacity));
            beginInd = commaInd + 1;
        }
    }
    //last capacity
    capacity = atoi(input.substr(commaInd + 1).c_str());
    tables.push_back(new Table(capacity));

}
Table* Restaurant::getTable(int ind){
    if(ind < getNumOfTables()) {
        return tables.at(ind);
    }
    return nullptr;
}
int Restaurant::getNumOfTables() const { return tables.size();} //dane
const std::vector<BaseAction *> & Restaurant::getActionsLog() const { return actionsLog;}//dane
std::vector<Dish> & Restaurant::getMenu() { return menu;}//done


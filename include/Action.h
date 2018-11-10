//
// Created by liad on 11/5/18.
//

#ifndef SPL_1_ACTION_H
#define SPL_1_ACTION_H

#include <string>
#include <iostream>
#include "Customer.h"

enum ActionStatus{
    PENDING, COMPLETED, ERROR
};

//Forward declaration
class Restaurant;

class BaseAction{ //dane
public:
    BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Restaurant& restaurant)=0;
    virtual std::string toString() const=0;
    virtual BaseAction * clone() = 0;
    void CloneBase(std::string errorMsg, ActionStatus status);
protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
private:
    std::string errorMsg;
    ActionStatus status;
};


class OpenTable : public BaseAction { //dane sholud i add error message in to string? TODO
public:
    OpenTable(int id, std::vector<Customer *> &customersList);
    void act(Restaurant &restaurant);
    //rule of 3
    OpenTable(const OpenTable & other) ;
    virtual ~OpenTable();
    OpenTable &operator=(const OpenTable &other);
    //
    std::string toString() const;
    BaseAction * clone();
private:
    const int tableId;
    const std::vector<Customer *> customers; //lishay rule of 3
};


class Order : public BaseAction { //dane
public:
    Order(int id);
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction * clone();
private:
    const int tableId;
};


class MoveCustomer : public BaseAction { //dane ex to string
public:
    MoveCustomer(int src, int dst, int customerId);
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction * clone();
private:
    const int srcTable;
    const int dstTable;
    const int id;
};


class Close : public BaseAction { //liads  mission
public:
    Close(int id);
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction * clone();
private:
    const int tableId;
};


class CloseAll : public BaseAction { //liad
public:
    CloseAll();
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction * clone();
private:
};


class PrintMenu : public BaseAction { // dane ex tostring
public:
    PrintMenu();
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction * clone();
private:
};


class PrintTableStatus : public BaseAction { //liad
public:
    PrintTableStatus(int id);
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction * clone();
private:
    const int tableId;
};

class PrintActionsLog : public BaseAction { //lishay dane
public:
    PrintActionsLog();
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction * clone();

private:
};


class BackupRestaurant : public BaseAction {
public:
    BackupRestaurant();
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction * clone();
private:
};


class RestoreResturant : public BaseAction {
public:
    RestoreResturant();
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction * clone();

};


#endif
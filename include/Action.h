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
    virtual ~BaseAction();
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


class OpenTable : public BaseAction {
public:
    OpenTable(int id, std::vector<Customer *> &customersList);
    virtual void act(Restaurant &restaurant);
    virtual std::string toString() const;
    virtual BaseAction * clone();
    virtual ~OpenTable();
    OpenTable(const OpenTable &other);
    OpenTable(OpenTable &&other);
private:
    const int tableId;
     std::vector<Customer *> customers;
};


class Order : public BaseAction { //dane
public:
    Order(int id);
    virtual void act(Restaurant &restaurant);
    virtual std::string toString() const;
    virtual BaseAction * clone();
private:
    const int tableId;
};


class MoveCustomer : public BaseAction { //dane ex to string
public:
    MoveCustomer(int src, int dst, int customerId);
    virtual void act(Restaurant &restaurant);
    virtual std::string toString() const;
    virtual BaseAction * clone();
private:
    const int srcTable;
    const int dstTable;
    const int id;
};


class Close : public BaseAction { //liads  mission
public:
    Close(int id);
    virtual void act(Restaurant &restaurant);
    virtual std::string toString() const;
    virtual BaseAction * clone();
private:
    const int tableId;
};


class CloseAll : public BaseAction { //liad
public:
    CloseAll() = default;
    virtual void act(Restaurant &restaurant);
    virtual std::string toString() const;
    virtual BaseAction * clone();
private:
};


class PrintMenu : public BaseAction { // dane ex tostring
public:
    PrintMenu();
    virtual void act(Restaurant &restaurant);
    virtual std::string toString() const;
    virtual BaseAction * clone();
private:
};


class PrintTableStatus : public BaseAction { //liad
public:
    PrintTableStatus(int id);
    virtual void act(Restaurant &restaurant);
    virtual std::string toString() const;
    virtual BaseAction * clone();
private:
    const int tableId;
};

class PrintActionsLog : public BaseAction { //lishay dane
public:
    PrintActionsLog();
    virtual void act(Restaurant &restaurant);
    virtual std::string toString() const;
    virtual BaseAction * clone();

private:
};


class BackupRestaurant : public BaseAction {
public:
    BackupRestaurant()= default;
    virtual void act(Restaurant &restaurant);
    virtual std::string toString() const;
    virtual BaseAction * clone();
private:
};


class RestoreResturant : public BaseAction {
public:
    RestoreResturant() = default;
    virtual void act(Restaurant &restaurant);
    virtual std::string toString() const;
    virtual BaseAction * clone();

};


#endif
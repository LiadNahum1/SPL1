//
// Created by liad on 11/5/18.
//

#ifndef SPL_1_CUSTOMER_H
#define SPL_1_CUSTOMER_H


#include <vector>
#include <string>
#include "Dish.h"
using namespace std;

class Customer{
public:
    Customer(std::string c_name, int c_id);
    virtual std::vector<int> order(const std::vector<Dish> &menu)=0;
    virtual std::string toString() const = 0;
    std::string getName() const;
    int getId() const;
private:
    const std::string name;
    const int id;
};


class VegetarianCustomer : public Customer {
public:
    VegetarianCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
private:
};


class CheapCustomer : public Customer {
public:
    CheapCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
private:
    bool orderOnce;
};


class SpicyCustomer : public Customer {
public:
    SpicyCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
private:
    bool orderOnce;
    void firstOrder(const std::vector<Dish> &menu, vector<int> &orderId);
    void nextOrders(const std::vector<Dish> &menu, vector<int> &orderId);
};


class AlchoholicCustomer : public Customer {
public:
    AlchoholicCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;

private:
    int prevPrice;
};


#endif
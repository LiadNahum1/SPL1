
//
// Created by USER on 11/6/2018.
//
#include "../include/Dish.h"

Dish::Dish(int d_id ,std::string d_name , int d_price ,DishType d_type): id(d_id), name(d_name), price(d_price), type(d_type){}
Dish & Dish :: operator=(const Dish &other){
    if(this != &other) {
        *this = *(new Dish(other.getId(), other.getName(), other.getPrice(), other.getType()));
        //*this = dish;
    }
    return *this;
}
std::string Dish::getName() const { return name;}
int Dish::getId() const { return id;}
int Dish::getPrice() const { return price;}
DishType Dish::getType() const {return type;}


//
// Created by USER on 11/6/2018.
//
#include "../include/Dish.h"

Dish::Dish(int d_id ,std::string d_name , int d_price ,DishType d_type){}
std::string Dish::getName() const { return this->getName();}
int Dish::getId() const { return this->id;}
int Dish::getPrice() const { return this->price;}
DishType Dish::getType() const {return this->type;}


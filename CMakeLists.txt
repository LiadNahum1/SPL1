cmake_minimum_required(VERSION 3.12)
project(SPL_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(SPL_1 main.cpp include/Restaurant.h include/Table.h include/Customer.h include/Action.h include/Dish.h src/Customer.cpp src/VegetarianCustomer.cpp src/CheapCustomer.cpp src/SpicyCustomer.cpp src/AlchoholicCustomer.cpp src/Restaurant.cpp src/MoveCustomer.cpp src/Table.cpp src/Close.cpp src/PrintMenu.cpp)
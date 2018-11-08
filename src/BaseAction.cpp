//
// Created by USER on 11/5/2018.
//
#include "../include/Action.h"
BaseAction::BaseAction():errorMsg("") {}
void BaseAction::complete() {status = COMPLETED; }
void BaseAction::error(std::string errorMsg) {
    status = ERROR;
    this->errorMsg = errorMsg;
    std::cout << errorMsg;
}
std::string BaseAction::getErrorMsg() const { return errorMsg;}
ActionStatus BaseAction::getStatus() const {return status;}
void BaseAction :: CloneBase(std::string errorMsg, ActionStatus status){
    this->errorMsg = errorMsg;
    this->status = status;
}
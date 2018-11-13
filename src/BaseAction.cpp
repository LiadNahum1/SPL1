//
// Created by USER on 11/5/2018.
//
#include "../include/Action.h"
BaseAction::BaseAction():errorMsg(""), status(PENDING) {}
void BaseAction::complete() {status = COMPLETED; }
void BaseAction::error(std::string errorMsg) {
    status = ERROR;
    this->errorMsg = "Error: " + errorMsg;
    std::cout << this->errorMsg<<endl;
}
std::string BaseAction::getErrorMsg() const { return errorMsg;}
ActionStatus BaseAction::getStatus() const {return status;}
void BaseAction :: CloneBase(std::string errorMsg, ActionStatus status){
    this->errorMsg = errorMsg;
    this->status = status;
}
BaseAction::~BaseAction() {}
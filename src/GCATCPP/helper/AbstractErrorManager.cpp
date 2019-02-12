//
// Created by Martin on 17.07.2018.
//

#include "AbstractErrorManager.h"

#include <iostream>

using namespace err;

AbstractErrorManager::AbstractErrorManager() {
    this->reset_msg();
}

void AbstractErrorManager::suppress_errors() {
    this->is_suppressed = true;
}

void AbstractErrorManager::print_errors() {
    if(!this->_has_error) { return;}
    std::cerr << (std::string) *this << std::endl;
    std::cerr << "---- Messages: ----" << std::endl;
    for(const auto &msgs : this->msg) {
        std::cerr << " " << msgs << std::endl;
    }

    std::cerr << "-------------------------"  << std::endl;

    std::cerr.flush();
    this->reset_msg();
}


void AbstractErrorManager::add_error_msges(std::vector<std::string> msges) {
    for(const std::string &msg : msges) {
        this->add_error_msg(msg);
    }
}

void AbstractErrorManager::add_error_msg(std::string err_msg) {
    if(this->is_suppressed) {
        this->_has_error = true;
        this->msg.push_back(err_msg);
    }
}

void AbstractErrorManager::reset_msg() {
    this->_has_error = false;
    this->msg = {};
}

std::vector<std::string> AbstractErrorManager::get_error_msg() {
    auto copy = this->msg;
    this->reset_msg();
    return copy;
}

//
// Created by Martin on 17.07.2018.
//

#ifndef GCATCPP_ABSTRACTERRORMANAGER_H
#define GCATCPP_ABSTRACTERRORMANAGER_H


#include <vector>
#include <string>

namespace err {

    class AbstractErrorManager {
    public:
        void print_errors();
        void suppress_errors();
        std::vector<std::string> get_error_msg();
        void add_error_msg(std::string);

    protected:
        bool is_suppressed = false;

        virtual ~AbstractErrorManager() {
            this->print_errors();
        };

        bool _has_error;
        std::vector<std::string> msg;


        void add_error_msges(std::vector<std::string>);
        void reset_msg();

        virtual operator std::string() const { return "-"; }

        AbstractErrorManager();
    };

}


#endif //GCATCPP_ANSTRACTERRORMANAGER_H

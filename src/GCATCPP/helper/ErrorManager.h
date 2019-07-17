//
// Created by martins on 17.07.19.
//

#ifndef GCATCPP_ERRORMANAGER_H
#define GCATCPP_ERRORMANAGER_H

#include "AbstractErrorManager.h"

namespace err {

    class ErrorManager : public AbstractErrorManager {
    public:
        ErrorManager() : AbstractErrorManager() {}
    };

}
#endif //GCATCPP_ERRORMANAGER_H

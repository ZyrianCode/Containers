#pragma once
#include "Includes/Src/Zyrian/CustomContainers/Definition/SingleDirectionalNode.h"

namespace ccl {
    template<class T>
    SingleDirectionalNode<T>::SingleDirectionalNode(T value, SingleDirectionalNode* pNext) {
        this->Value = value;
        this->PNext = pNext;
    }
}

#pragma once

namespace ccl {
    template<class T>
    class SingleDirectionalNode
    {
    public:
        T Value;
        SingleDirectionalNode* PNext;
        SingleDirectionalNode(T value = T(), SingleDirectionalNode* pNext = nullptr);
    };
}

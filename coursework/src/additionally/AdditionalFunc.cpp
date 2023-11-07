#include "../../include/additionally/AdditionalFunc.hpp"

namespace AdditionalFunc {
    namespace InnerLogic {
        std::mt19937 gen(std::random_device{}());
    }
    
    int getRandom(std::uniform_int_distribution<> &distribution) {
        return distribution(InnerLogic::gen);
    }
}

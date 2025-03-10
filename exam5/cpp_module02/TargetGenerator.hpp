#pragma once

#include <iostream>
#include <vector>
#include "ATarget.hpp"

class TargetGenerator
{
    private:
        std::vector<ATarget *> target;
        TargetGenerator(TargetGenerator const &copy);
		TargetGenerator &operator=(TargetGenerator const &src);
    public:
        TargetGenerator();
        ~TargetGenerator();

        void learnTargetType(ATarget *newTarget);
        void forgetTargetType(std::string const &target);
        ATarget *createTarget(std::string const &target);
};

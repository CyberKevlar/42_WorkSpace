#pragma once

#include <iostream>
#include <vector>
#include "ATarget.hpp"

class TargetGenerator
{
    private:
        std::vector<ATarget *> target;

        TargetGenerator(TargetGenerator const &copy) = delete;
		TargetGenerator &operator=(TargetGenerator const &src) = delete;

    public:
        TargetGenerator();
        virtual ~TargetGenerator();

        void learnTargetType(ATarget *target);
        void forgetTargetType(std::string const &target);
        ATarget *createTarget(std::string const &target);
};

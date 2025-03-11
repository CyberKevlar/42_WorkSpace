#pragma once

#include <iostream>
#include "ASpell.hpp"

class ASpell;

class ATarget
{
    protected:
        std::string type;

        ATarget() = delete;
    public:
        ATarget(const std::string &type);
        ATarget(const ATarget &copy);
        virtual ~ATarget();
        ATarget &operator=(const ATarget &src);

        std::string const &getType(void) const;

        void getHitBySpell(const ASpell &spell) const;

        virtual ATarget *clone(void) const = 0;
};
#pragma once

#include "ASpell.hpp"
#include <iostream>

class ASpell;

class ATarget
{
    protected:
        std::string type;
        ATarget();
    public:
        ATarget(const std::string &type);
        virtual ~ATarget();
        ATarget(const ATarget &copy);
        ATarget &operator=(const ATarget &src);

        std::string const &getType(void) const;

        void getHitBySpell(const ASpell &spell) const;

        virtual ATarget *clone(void) const = 0;
};
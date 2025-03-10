#pragma once

#include "ATarget.hpp"
#include <iostream>

class ATarget;

class ASpell
{
    protected:
        std::string name;
        std::string effects;
    public:
        ASpell();

        ASpell(const std::string &name, const std::string &effects);
        virtual ~ASpell();
        ASpell(const ASpell &copy);
        ASpell &operator=(const ASpell &src);

        std::string const &getName(void) const;
        std::string const &getEffects(void) const;
        
        virtual ASpell *clone(void) const = 0;

        void launch(const ATarget &target);
};
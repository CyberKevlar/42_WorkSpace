#pragma once

#include "ATarget.hpp"
#include <iostream>

class ASpell: public ATarget
{
    protected:
        std::string name;
        std::string effects;
        ASpell();
    public:
        ASpell(const std::string &name, const std::string &effects);
        ~ASpell();
        ASpell(const ASpell &copy);
        ASpell &operator=(const ASpell &src);

        std::string const &getName(void) const;
        std::string const &getEffects(void) const;
        
        virtual ASpell *clone(void) const = 0;

        void launch(const ATarget &target);
};
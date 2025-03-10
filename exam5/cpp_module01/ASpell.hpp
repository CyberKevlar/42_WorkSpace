#pragma once

#include <iostream>
#include "ATarget.hpp"

class ATarget;

class ASpell
{
    protected:
        std::string name;
        std::string effects;

        ASpell() = delete;
    public:
        ASpell(const std::string &name, const std::string &effects);
        ASpell(const ASpell &copy);
        virtual ~ASpell();
        ASpell &operator=(const ASpell &src);

        std::string const &getName(void) const;
        std::string const &getEffects(void) const;
        
        virtual ASpell *clone(void) const = 0;

        void launch(const ATarget &target);
};
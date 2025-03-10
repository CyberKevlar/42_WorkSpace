#pragma once

#include <iostream>
#include <vector>
#include "ASpell.hpp"
#include "SpellBook.hpp"

class Warlock
{
    private:
        std::string name;
        std::string title;

        SpellBook spellbook;
    public:
        std::vector<ASpell *> attacks;

        Warlock(const std::string &name, const std::string &title);
        ~Warlock();
        Warlock(const Warlock &copy);
        Warlock &operator=(const Warlock &src);

        const std::string &getName(void) const;
        const std::string &getTitle(void) const;

        void setTitle(const std::string &newTitle);
        
        void introduce(void) const;

        void learnSpell(ASpell *newSpell);
        void forgetSpell(std::string spell);
        void launchSpell(std::string spell, ATarget &target);
};
#pragma once

#include <iostream>
#include <vector>
#include "ASpell.hpp"

class SpellBook
{
    private:
        std::vector<ASpell *> book;

        SpellBook(SpellBook const &copy) = delete;
		SpellBook &operator=(SpellBook const &src) = delete;
    public:
        SpellBook();
        virtual ~SpellBook();

        void learnSpell(ASpell *newSpell);
        void forgetSpell(std::string const &spell);
        ASpell *createSpell(std::string const &spell);
};
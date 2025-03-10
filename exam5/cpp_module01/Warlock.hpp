#pragma once

#include <iostream>
#include <vector>
#include "ASpell.hpp"
#include "ATarget.hpp"

class Warlock
{
    private:
        std::string name;
        std::string title;

        Warlock() = delete;
        Warlock(const Warlock &copy) = delete;
        Warlock &operator=(const Warlock &src) = delete;
    public:
        std::vector<ASpell *> attacks;

        Warlock(std::string &name, std::string &title);
        ~Warlock();

        const std::string &getName(void) const;
        const std::string &getTitle(void) const;

        void setTitle(const std::string &newTitle);
        
        void introduce(void) const;

        void learnSpell(ASpell *newSpell);
        void forgetSpell(std::string spell);
        void launchSpell(std::string spell, ATarget &target);
};
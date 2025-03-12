#include "Warlock.hpp"

Warlock::Warlock(const std::string &name, const std::string &title)
{
    this->name = name;
    this->title = title;
    std::cout << this->name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock() {
    std::cout << this->name << ": My job here is done!" << std::endl;
}

const std::string &Warlock::getName(void) const
{
    return this->name;
}

const std::string &Warlock::getTitle(void) const
{
    return this->title;
}

void Warlock::setTitle(const std::string &title)
{
    this->title = title;
    return ;
}

void Warlock::introduce(void) const
{
    std::cout << this->name << ": I am " << this->name << ", " << this->title << "!" << std::endl;
    return ;
}

void Warlock::learnSpell(ASpell *spell)
{
    this->spellbook.learnSpell(spell);
    return ;
}

void Warlock::forgetSpell(std::string spell)
{
    this->spellbook.forgetSpell(spell);
    return ;
}

void Warlock::launchSpell(std::string spell, ATarget &target)
{
    ATarget const *tmp1 = 0;
    if (tmp1 == &target)
        return ;
    ASpell *tmp2 = spellbook.createSpell(spell);
    if (tmp2)
        tmp2->launch(target);
    return ;
}

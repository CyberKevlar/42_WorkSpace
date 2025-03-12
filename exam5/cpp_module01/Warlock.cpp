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
}

void Warlock::introduce(void) const
{
    std::cout << this->name << ": I am " << this->name << ", " << this->title << "!" << std::endl;
}

void Warlock::learnSpell(ASpell *spell)
{
    std::vector<ASpell *>::iterator it = this->spells.begin();
    while (it != this->spells.end())
    {
        if ((*it)->getName() == spell->getName())
            return ;
        it++;
    }
    this->spells.push_back(spell->clone());
    return ;
}

void Warlock::forgetSpell(std::string spell)
{
    std::vector<ASpell *>::iterator it = this->spells.begin();
    while (it != this->spells.end())
    {
        if ((*it)->getName() == spell)
        {
            this->spells.erase(it);
            return ;
        }
        it++;
    }
    return ;
}

void Warlock::launchSpell(std::string spell, ATarget &target)
{
    std::vector<ASpell *>::iterator it = this->spells.begin();
    while (it != this->spells.end())
    {
        if ((*it)->getName() == spell)
        {
            (*it)->launch(target);
            return ;
        }
        it++;
    }
    return ;
}

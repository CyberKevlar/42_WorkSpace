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

Warlock::Warlock(const Warlock &copy) : name(copy.name), title(copy.title) {}

Warlock &Warlock::operator=(const Warlock &src)
{
    if (this != &src) {
        this->name = src.name;
        this->title = src.title;
    }
    return *this;
}

const std::string &Warlock::getName(void) const
{
    return this->name;
}

const std::string &Warlock::getTitle(void) const
{
    return this->title;
}

void Warlock::setTitle(const std::string &newTitle)
{
    this->title = newTitle;
}

void Warlock::introduce(void) const
{
    std::cout << this->name << ": I am " << this->name << ", " << this->title << "!" << std::endl;
}

void Warlock::learnSpell(ASpell *newSpell)
{
    std::vector<ASpell *>::iterator it = attacks.begin();
    while (it != attacks.end()) {
        if ((*it)->getName() == newSpell->getName())
            return ;
        it++;
    }
    attacks.push_back(newSpell->clone());
    return ;
}

void Warlock::forgetSpell(std::string spell)
{
    std::vector<ASpell *>::iterator it = attacks.begin();
    while (it != attacks.end()) {
        if ((*it)->getName() == spell) {
            attacks.erase(it);
            return ;
        }
        it++;
    }
    return ;
}

void Warlock::launchSpell(std::string spell, ATarget &target)
{
    std::vector<ASpell *>::iterator it = attacks.begin();
    while (it != attacks.end()) {
        if ((*it)->getName() == spell) {
            (*it)->launch(target);
            return ;
        }
        it++;
    }
    return ;
}
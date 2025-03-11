#include "ASpell.hpp"

ASpell::ASpell(const std::string &name, const std::string &effects)
{
    this->name = name;
    this->effects = effects;
}

ASpell::ASpell(const ASpell &copy) : name(copy.name), effects(copy.effects) {}

ASpell::~ASpell() {}

ASpell &ASpell::operator=(const ASpell &src)
{
    if (this != &src) {
        this->name = src.name;
        this->effects = src.effects;
    }
    return *this;
}

std::string const &ASpell::getName(void) const
{
    return this->name;
}

std::string const &ASpell::getEffects(void) const
{
    return this->effects;
}

void ASpell::launch(const ATarget &target)
{
    target.getHitBySpell(*this);
}
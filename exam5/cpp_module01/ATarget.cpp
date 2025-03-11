#include "ATarget.hpp"

ATarget::ATarget(const std::string &type)
{
    this->type = type;
}

ATarget::ATarget(const ATarget &copy) : type(copy.type) {}

ATarget::~ATarget() {}

ATarget &ATarget::operator=(const ATarget &src)
{
    if (this != &src) {
        this->type = src.type;
    }
    return *this;
}

std::string const &ATarget::getType(void) const
{
    return this->type;
}

void ATarget::getHitBySpell(const ASpell &spell) const
{
    std::cout << this->type << " has been " << spell.getEffects() << "!" << std::endl;
}
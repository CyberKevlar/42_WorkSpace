#include "SpellBook.hpp"

SpellBook::SpellBook() {}

SpellBook::~SpellBook() {}

void SpellBook::learnSpell(ASpell *newSpell)
{
    std::vector<ASpell*>::iterator ite = this->book.end();
		for (std::vector<ASpell*>::iterator it = this->book.begin(); it != ite; ++it) {
			if ((*it)->getName() == newSpell->getName())
				return ;
		}
		this->book.push_back(newSpell->clone());
    return ;
}

void SpellBook::forgetSpell(std::string const &spell)
{
    std::vector<ASpell*>::iterator ite = this->book.end();
		for (std::vector<ASpell*>::iterator it = this->book.begin(); it != ite; ++it) {
			if ((*it)->getName() == spell)
            {
				delete (*it);
			    it = this->book.erase(it);
                return ;
		    }
        }        
    return ;
}

ASpell *SpellBook::createSpell(std::string const &spell)
{
    std::vector<ASpell*>::iterator ite = this->book.end();
		for (std::vector<ASpell*>::iterator it = this->book.begin(); it != ite; ++it) {
			if ((*it)->getName() == spell)
                return (*it);
        }        
    return NULL;
}

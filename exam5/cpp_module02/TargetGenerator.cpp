#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() {}

TargetGenerator::~TargetGenerator() {}

void TargetGenerator::learnTargetType(ATarget *newTarget)
{
    std::vector<ATarget*>::iterator ite = this->target.end();
		for (std::vector<ATarget*>::iterator it = this->target.begin(); it != ite; ++it) {
			if ((*it)->getType() == newTarget->getType())
				return ;
		}
		this->target.push_back(newTarget->clone());
    return ;
}

void TargetGenerator::forgetTargetType(std::string const &spell)
{
    std::vector<ATarget*>::iterator ite = this->target.end();
		for (std::vector<ATarget*>::iterator it = this->target.begin(); it != ite; ++it) {
			if ((*it)->getType() == spell)
            {
				delete (*it);
			    it = this->target.erase(it);
                return ;
		    }
        }        
    return ;
}

ATarget *TargetGenerator::createTarget(std::string const &spell)
{
    std::vector<ATarget*>::iterator ite = this->target.end();
		for (std::vector<ATarget*>::iterator it = this->target.begin(); it != ite; ++it) {
			if ((*it)->getType() == spell)
                return (*it);
        }        
    return NULL;
}

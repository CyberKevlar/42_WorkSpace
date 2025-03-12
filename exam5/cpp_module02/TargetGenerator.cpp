#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() {}

TargetGenerator::~TargetGenerator() {}

void TargetGenerator::learnTargetType(ATarget *target)
{
    std::vector<ATarget *>::iterator it = this->target.begin();
		while (it != this->target.end())
		{
			if ((*it)->getType() == target->getType())
				return ;
			it++;
		}	
	this->target.push_back(target->clone());
    return ;
}

void TargetGenerator::forgetTargetType(std::string const &spell)
{
	std::vector<ATarget *>::iterator it = this->target.begin();
	while (it != this->target.end())
	{
		if ((*it)->getType() == spell)
		{
			this->target.erase(it);
			return ;
		}
		it++;
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

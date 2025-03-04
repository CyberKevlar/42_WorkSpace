#pragma once

#include <iostream>

class Warlock
{
    private:
        std::string name;
        std::string title;
    public:
        Warlock(const std::string &name, const std::string &title);
        ~Warlock();
        Warlock(const Warlock &copy);
        Warlock &operator=(const Warlock &src);

        const std::string &getName(void) const;
        const std::string &getTitle(void) const;

        void setTitle(const std::string &newTitle);
        
        void introduce(void) const;
    };
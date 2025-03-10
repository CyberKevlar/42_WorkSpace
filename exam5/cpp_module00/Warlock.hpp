#pragma once

#include <iostream>

class Warlock
{
    private:
        std::string name;
        std::string title;

        Warlock() = delete;
        Warlock(const Warlock &copy) = delete;
        Warlock &operator=(const Warlock &src) = delete;
    public:
        Warlock(std::string &name, std::string &title);
        ~Warlock();

        const std::string &getName(void) const;
        const std::string &getTitle(void) const;

        void setTitle(const std::string &newTitle);
        
        void introduce(void) const;
};
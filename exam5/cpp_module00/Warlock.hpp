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
        Warlock(const std::string &name, const std::string &title);
        ~Warlock();

        const std::string &getName(void) const;
        const std::string &getTitle(void) const;

        void setTitle(const std::string &title);
        
        void introduce(void) const;
};
#include <iostream>

class Warlock
{
    private:
        std::string name;
        std::string title;
    public:
        Warlock();
        ~Warlock();
        Warlock(const Warlock &copy);
        Warlock &operator=(const Warlock &src);
        const std::string &getName(void);
        const std::string &getTitle(void);

}

#include <iostream>  // std::cout std::endl
class Singleton {
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& getInstance()
    {
        static Singleton instance;
        return instance;
    }

    void action() const
    {
        std::cout << __func__ << std::endl;
    }

private:
    Singleton() = default;
};

int main()
{
    auto& singleton = Singleton::getInstance();
    singleton.action();
}

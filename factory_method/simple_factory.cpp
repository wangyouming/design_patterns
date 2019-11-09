
#include <iostream>  // std::cout std::endl
#include <memory>    // std::make_shared std::shared_ptr
#include <string>    // std::string

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::string;

class Pizza {
public:
    virtual ~Pizza() = default;
    virtual string name() const = 0;
};

class PizzaX : public Pizza {
public:
    string name() const override
    {
        return "PizzaX";
    }
};

class PizzaY : public Pizza {
public:
    string name() const override
    {
        return "PizzaY";
    }
};

class PizzaFactory {
public:
    shared_ptr<Pizza> createPizza(const string& name)
    {
        if (name == "PizzaX") {
            return make_shared<PizzaX>();
        } else if (name == "PizzaY") {
            return make_shared<PizzaY>();
        }
        return nullptr;
    }
};

int main()
{
    PizzaFactory pizza_factory;
    auto         pizza = pizza_factory.createPizza("PizzaX");
    cout << pizza->name() << endl;
}

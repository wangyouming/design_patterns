
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

class PizzaStore {
public:
    virtual ~PizzaStore() = default;
    virtual shared_ptr<Pizza> createPizza() = 0;
};

class PizzaStoreX : public PizzaStore {
public:
    shared_ptr<Pizza> createPizza() override
    {
        return make_shared<PizzaX>();
    }
};

class PizzaStoreY : public PizzaStore {
public:
    shared_ptr<Pizza> createPizza() override
    {
        return make_shared<PizzaY>();
    }
};

int main()
{
    PizzaStoreX pizza_store_x;
    PizzaStore* pizza_store{&pizza_store_x};
    auto        pizza = pizza_store->createPizza();
    cout << pizza->name() << endl;
}

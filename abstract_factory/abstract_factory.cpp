
#include <iostream>  // std::cout std::endl
#include <memory>    // std:::shared_ptr std::make_shared
#include <string>    // std::string

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::string;

class Sauce {
public:
    virtual ~Sauce() = default;
    virtual string name() const = 0;
};

class SauceX : public Sauce {
public:
    string name() const override
    {
        return "SauceX";
    }
};

class SauceY : public Sauce {
public:
    string name() const override
    {
        return "SauceY";
    }
};

class Sugar {
public:
    virtual ~Sugar() = default;
    virtual string test() const = 0;
};

class SugarX : public Sugar {
public:
    string test() const override
    {
        return "Sweet";
    }
};

class SugarY : public Sugar {
    string test() const override
    {
        return "Bitter";
    }
};

class IngredientFactory {
public:
    virtual ~IngredientFactory() = default;
    virtual shared_ptr<Sauce> createSauce() = 0;
    virtual shared_ptr<Sugar> createSugar() = 0;
};

class IngredientFactoryX : public IngredientFactory {
public:
    shared_ptr<Sauce> createSauce() override
    {
        return make_shared<SauceX>();
    }
    shared_ptr<Sugar> createSugar() override
    {
        return make_shared<SugarX>();
    }
};

class IngredientFactoryY : public IngredientFactory {
public:
    shared_ptr<Sauce> createSauce() override
    {
        return make_shared<SauceY>();
    }
    shared_ptr<Sugar> createSugar() override
    {
        return make_shared<SugarY>();
    }
};

int main()
{
    IngredientFactoryX factory_x;
    IngredientFactory* factory = &factory_x;

    cout << factory->createSauce()->name() << endl;
    cout << factory->createSugar()->test() << endl;

    IngredientFactoryY factory_y;
    factory = &factory_y;

    cout << factory->createSauce()->name() << endl;
    cout << factory->createSugar()->test() << endl;
}

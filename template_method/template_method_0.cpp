
#include <iostream>  // std::cout std::endl
#include <random>  // std::default_random_engine std::bernoulli_distribution

using std::bernoulli_distribution;
using std::cout;
using std::default_random_engine;
using std::endl;

class CaffeinBeverage {
public:
    virtual ~CaffeinBeverage() = default;

    void prepareRecipe()
    {
        boilWater();
        brew();
        pourInCup();
        if (customerWantsCondiments()) {
            addCondiments();
        }
    }

private:
    void boilWater()
    {
        cout << "Boiling water" << endl;
    }

    void pourInCup()
    {
        cout << "Pouring into cup" << endl;
    }

    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    virtual bool customerWantsCondiments()
    {
        return true;
    }
};

class Coffee : public CaffeinBeverage {
private:
    void brew() override
    {
        cout << "Coffee " << __func__ << endl;
    }

    void addCondiments() override
    {
        cout << "Coffee " << __func__ << endl;
    }

    bool customerWantsCondiments() override
    {
        static default_random_engine e;
        bernoulli_distribution       d{0.5};
        return d(e);
    }
};

class Tea : public CaffeinBeverage {
private:
    void brew() override
    {
        cout << "Tea " << __func__ << endl;
    }

    void addCondiments() override
    {
        cout << "Tea " << __func__ << endl;
    }
};

int main()
{
    Coffee coffee;
    Tea    tea;

    CaffeinBeverage* beverage{&coffee};
    for (int i = 0; i < 5; ++i) {
        beverage->prepareRecipe();
    }

    beverage = &tea;
    for (int i = 0; i < 5; ++i) {
        beverage->prepareRecipe();
    }
}

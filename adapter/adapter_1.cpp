
#include <iostream>  // std::cout std::endl

using std::cout;
using std::endl;

class Duck {
public:
    virtual ~Duck() = default;
    virtual void quack() = 0;
    virtual void fly() = 0;
};

class MallardDuck : public Duck {
public:
    void quack() override
    {
        cout << "MallardDuck " << __func__ << endl;
    }

    void fly() override
    {
        cout << "MallardDuck " << __func__ << endl;
    }
};

class Turkey {
public:
    virtual ~Turkey() = default;
    virtual void gobble() = 0;
    virtual void fly() = 0;
};

class WildTurkey : public Turkey {
public:
    void gobble() override
    {
        cout << "WildTurkey " << __func__ << endl;
    }

    void fly() override
    {
        cout << "WildTurkey " << __func__ << endl;
    }
};

class DuckAdapter : public MallardDuck, public Turkey {
public:
    void gobble() override
    {
        cout << "DuckAdapter " << __func__ << endl;
    }

    void fly() override
    {
        MallardDuck::fly();
    }
};

class TurkeyAdapter : public WildTurkey, public Duck {
public:
    void quack() override
    {
        cout << "TurkeyAdapter " << endl;
    }

    void fly() override
    {
        WildTurkey::fly();
    }
};

int main()
{
    DuckAdapter duck_adapter;
    duck_adapter.gobble();
    duck_adapter.fly();

    TurkeyAdapter turkey_adapter;
    turkey_adapter.quack();
    turkey_adapter.fly();
}

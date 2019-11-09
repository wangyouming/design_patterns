
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

class DuckAdapter : public Turkey {
public:
    explicit DuckAdapter(Duck& duck)
        : duck_{duck}
    {
    }

    void gobble() override
    {
        duck_.quack();
    }

    void fly() override
    {
        if (count_ % 5 == 0) {
            duck_.fly();
        }
        count_ += 1;
    }

private:
    Duck& duck_;
    int   count_{0};
};

class TurkeyAdapter : public Duck {
public:
    explicit TurkeyAdapter(Turkey& turkey)
        : turkey_{turkey}
    {
    }

    void quack() override
    {
        turkey_.gobble();
    }

    void fly() override
    {
        for (int i = 0; i < 5; ++i) {
            turkey_.fly();
        }
    }

private:
    Turkey& turkey_;
};

int main()
{
    MallardDuck duck;
    DuckAdapter duck_adapter{duck};
    duck_adapter.gobble();
    duck_adapter.fly();

    WildTurkey    turkey;
    TurkeyAdapter turkey_adapter{turkey};
    turkey_adapter.quack();
    turkey_adapter.fly();
}

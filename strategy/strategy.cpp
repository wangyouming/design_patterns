
#include <iostream>  // std::cout std::endl
#include <memory>    // std::shared_ptr std::make_shared

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

class FlyBehavior {
public:
    virtual ~FlyBehavior() = default;
    virtual void fly() = 0;
};

class FlyNoWay : public FlyBehavior {
public:
    void fly() override
    {
        cout << "I can't fly" << endl;
    }
};

class FlyRocketPowered : public FlyBehavior {
public:
    void fly() override
    {
        cout << "I'm flying with a rocket" << endl;
    }
};

class FlyWithWings : public FlyBehavior {
public:
    void fly() override
    {
        cout << "Im flying" << endl;
    }
};

class QuackBehavior {
public:
    virtual ~QuackBehavior() = default;
    virtual void quack() = 0;
};

class Quack : public QuackBehavior {
public:
    void quack() override
    {
        cout << "Quack" << endl;
    }
};

class Duck {
public:
    virtual ~Duck() = default;

    void set_flyBehavior(shared_ptr<FlyBehavior> fly_behavior)
    {
        fly_behavior_ = fly_behavior;
    }

    void set_quackBehavior(shared_ptr<QuackBehavior> quack_behavior)
    {
        quack_behavior_ = quack_behavior;
    }

    virtual void display() = 0;

    void performFly()
    {
        fly_behavior_->fly();
    }

    void performQuack()
    {
        quack_behavior_->quack();
    }

    void swim()
    {
        cout << "Duck " << __func__ << endl;
    }

private:
    shared_ptr<FlyBehavior>   fly_behavior_;
    shared_ptr<QuackBehavior> quack_behavior_;
};

class RedHeadDuck : public Duck {
public:
    RedHeadDuck()
    {
        set_flyBehavior(make_shared<FlyWithWings>());
        set_quackBehavior(make_shared<Quack>());
    }

    void display() override
    {
        cout << "RedHeadDuck " << __func__ << endl;
    }
};

int main()
{
    RedHeadDuck red_head_duck;
    Duck&       duck{red_head_duck};

    duck.display();
    duck.performQuack();
    duck.performFly();

    auto fly_behavior = make_shared<FlyRocketPowered>();
    duck.set_flyBehavior(fly_behavior);
    duck.performFly();
}

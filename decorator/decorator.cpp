
#include <iostream>  // std::cout std::endl
#include <string>    // std::string

class Beverage {
public:
    enum Size { TALL, GRANDE, VENT };

    virtual ~Beverage() = default;

    Size size() const
    {
        return size_;
    }

    void set_size(Size size)
    {
        size_ = size;
    }

    virtual std::string desc() const = 0;

    virtual double cost() const = 0;

private:
    Size size_{TALL};
};

class DarkRoast : public Beverage {
public:
    std::string desc() const override
    {
        return "Dark Roast Coffee";
    }

    double cost() const override
    {
        return 0.99;
    }
};

class Decaf : public Beverage {
public:
    std::string desc() const override
    {
        return "Decaf Coffee";
    }

    double cost() const override
    {
        return 1.05;
    }
};

class CondimentDecorator : public Beverage {
public:
    explicit CondimentDecorator(Beverage* beverage)
        : _beverage(beverage)
    {
    }

    const Beverage* beverage() const
    {
        return _beverage;
    }

private:
    Beverage* _beverage;
};

class Milk : public CondimentDecorator {
public:
    using CondimentDecorator::CondimentDecorator;

    std::string desc() const override
    {
        return beverage()->desc() + ", Milk";
    }

    double cost() const override
    {
        double cost = beverage()->cost();
        switch (beverage()->size()) {
        case TALL:
            cost += 0.1;
            break;
        case GRANDE:
            cost += 0.2;
            break;
        case VENT:
            cost += 0.3;
            break;
        }
        return cost;
    }
};

class Mocha : public CondimentDecorator {
public:
    using CondimentDecorator::CondimentDecorator;

    std::string desc() const override
    {
        return beverage()->desc() + ", Mocha";
    }

    double cost() const override
    {
        return beverage()->cost() + 0.2;
    }
};

int main()
{
    DarkRoast dark_roast;
    Beverage* beverage = &dark_roast;
    std::cout << beverage->desc() << " " << beverage->cost() << std::endl;

    Mocha mocha{beverage};
    Milk  milk{&mocha};
    beverage = &milk;
    std::cout << beverage->desc() << " " << beverage->cost() << std::endl;
}

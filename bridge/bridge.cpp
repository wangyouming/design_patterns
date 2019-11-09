
#include <iostream>  // std::cout std::endl

using std::cout;
using std::endl;

class Implementor {
public:
    virtual ~Implementor() = default;
    virtual void action() = 0;
};

class ImplementorX : public Implementor {
public:
    void action() override
    {
        cout << "ImplementorX " << __func__ << endl;
    }
};

class ImplementorY : public Implementor {
public:
    void action() override
    {
        cout << "ImplementorY " << __func__ << endl;
    }
};

class Abstraction {
public:
    virtual ~Abstraction() = default;
    explicit Abstraction(Implementor* implementor)
        : implementor_{implementor}
    {
    }
    virtual void operation() = 0;

protected:
    Implementor* implementor_;
};

class AbstractionX : public Abstraction {
public:
    using Abstraction::Abstraction;
    void operation() override
    {
        implementor_->action();
    }
};

int main()
{
    ImplementorX implementor_x;
    Implementor* implementor = &implementor_x;
    AbstractionX abstraction_x{implementor};
    Abstraction* abstraction = &abstraction_x;
    abstraction->operation();
}

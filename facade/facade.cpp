
#include <iostream>  // std::cout std::endl
#include <memory>    // std::make_unique std::unique_ptr

using std::make_unique;
using std::unique_ptr;

class SubsystemA {
public:
    void operation()
    {
        std::cout << "SubsystemA " << __func__ << std::endl;
    }
};

class SubsystemB {
public:
    void action()
    {
        std::cout << "SubsystemB " << __func__ << std::endl;
    }
};

class SubsystemC {
public:
    void handle()
    {
        std::cout << "SubsystemC " << __func__ << std::endl;
    }
};

class Facade {
public:
    Facade()
        : subsystem_a_{make_unique<SubsystemA>()}
        , subsystem_b_{make_unique<SubsystemB>()}
        , subsystem_c_{make_unique<SubsystemC>()}
    {
    }

    void operation()
    {
        subsystem_a_->operation();
        subsystem_b_->action();
    }

    void action()
    {
        subsystem_b_->action();
        subsystem_c_->handle();
    }

private:
    unique_ptr<SubsystemA> subsystem_a_;
    unique_ptr<SubsystemB> subsystem_b_;
    unique_ptr<SubsystemC> subsystem_c_;
};

int main()
{
    Facade facade;
    facade.operation();
    facade.action();
}

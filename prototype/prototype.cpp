
#include <iostream>  // std::cout std::endl
#include <memory>    // std::make_shared std::shared_ptr

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

class Prototype {
public:
    virtual ~Prototype() = default;

    shared_ptr<Prototype> clone()
    {
        shared_ptr<Prototype> clone = doClone();
        assert(typeid(*clone) == typeid(*this) &&
               "doClone incorrectly overriden");
        return clone;
    }

    virtual void action() = 0;

private:
    virtual shared_ptr<Prototype> doClone() = 0;
};

class PrototypeX : public Prototype {
public:
    void action() override
    {
        std::cout << "PrototypeX " << __func__ << std::endl;
    }

private:
    shared_ptr<Prototype> doClone() override
    {
        return make_shared<PrototypeX>(*this);
    }
};

class PrototypeY : public Prototype {
public:
    void action() override
    {
        std::cout << "PrototypeY " << __func__ << std::endl;
    }

private:
    shared_ptr<Prototype> doClone() override
    {
        return make_shared<PrototypeY>(*this);
    }
};

class Maker {
public:
    static void init()
    {
        types_[0] = make_shared<PrototypeX>();
        types_[1] = make_shared<PrototypeY>();
    }

    static void remove()
    {
        types_[0] = nullptr;
        types_[1] = nullptr;
    }

    static shared_ptr<Prototype> create(size_t index)
    {
        if (index >= count_) {
            return nullptr;
        } else {
            return types_[index]->clone();
        }
    }

private:
    static shared_ptr<Prototype> types_[2];
    static constexpr int         count_{2};
};

shared_ptr<Prototype> Maker::types_[];

int main()
{
    Maker::init();

    auto prototype = Maker::create(0);
    prototype->action();

    prototype = Maker::create(1);
    prototype->action();

    Maker::remove();
}


#include <iostream>  // std::cout std::endl
#include <memory>    // std::make_unique std::unique_ptr
#include <stack>     // std::stack

using std::make_unique;
using std::unique_ptr;

class Memento {
public:
    explicit Memento(int state)
        : state_{state}
    {
    }

    int state() const
    {
        return state_;
    }

private:
    int state_;
};

class Originator {
public:
    int state() const
    {
        return state_;
    }

    void set_state(int state)
    {
        state_ = state;
    }

    unique_ptr<Memento> createMemento()
    {
        return make_unique<Memento>(state_);
    }

    void set_memento(Memento* memento)
    {
        state_ = memento->state();
    }

private:
    int state_;
};

class CareTaker {
public:
    explicit CareTaker(Originator* originator)
        : originator_{originator}
    {
    }

    void store()
    {
        std::cout << "CareTaker " << __func__ << std::endl;
        history_.push(originator_->createMemento());
    }

    void restore()
    {
        if (history_.empty()) {
            std::cout << "CareTaker history empty, restore failed!"
                      << std::endl;
            return;
        }

        auto& memento = history_.top();
        originator_->set_memento(memento.get());
        history_.pop();
        std::cout << "CareTaker " << __func__ << std::endl;
    }

private:
    Originator*                     originator_;
    std::stack<unique_ptr<Memento>> history_;
};

int main()
{
    Originator originator;
    CareTaker  care_taker{&originator};

    originator.set_state(1);
    care_taker.store();

    originator.set_state(2);
    care_taker.store();

    originator.set_state(3);
    care_taker.store();

    care_taker.restore();
    std::cout << originator.state() << std::endl;

    care_taker.restore();
    std::cout << originator.state() << std::endl;

    care_taker.restore();
    std::cout << originator.state() << std::endl;
}

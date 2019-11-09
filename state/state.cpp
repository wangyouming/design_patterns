
#include <iostream>  // std::cout std::endl
#include <memory>    // std::make_unique std::unique_ptr

using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;

class Context;

class State {
public:
    virtual ~State() = default;

    explicit State(Context* context)
        : context_{context}
    {
    }
    virtual void action() = 0;

protected:
    Context* context_;
};

class StateX : public State {
public:
    using State::State;
    void action() override;
};

class StateY : public State {
public:
    using State::State;
    void action() override;
};

class StateZ : public State {
public:
    using State::State;
    void action() override;
};

class Context {
public:
    Context()
        : state_x_{make_unique<StateX>(this)}
        , state_y_{make_unique<StateY>(this)}
        , state_z_{make_unique<StateZ>(this)}
    {
        state_ = state_x_.get();
    }

    void action()
    {
        state_->action();
    }

    void switchStateX()
    {
        state_ = state_x_.get();
    }

    void switchStateY()
    {
        state_ = state_y_.get();
    }

    void switchStateZ()
    {
        state_ = state_z_.get();
    }

private:
    unique_ptr<StateX> state_x_;
    unique_ptr<StateY> state_y_;
    unique_ptr<StateZ> state_z_;
    State*             state_;
};

void StateX::action()
{
    cout << "StateX " << __func__ << endl;
    context_->switchStateY();
}

void StateY::action()
{
    cout << "StateY " << __func__ << endl;
    context_->switchStateZ();
}

void StateZ::action()
{
    cout << "StateZ " << __func__ << endl;
    context_->switchStateX();
}

int main()
{
    Context context;

    context.action();
    context.action();
    context.action();
}

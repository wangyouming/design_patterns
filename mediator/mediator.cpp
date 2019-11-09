
#include <iostream>  // std::cout std::endl
#include <string>    // std::string
#include <vector>    // std::vector

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Mediator;

class Colleague {
public:
    virtual ~Colleague() = default;

    Colleague(Mediator* mediator, int id)
        : mediator_{mediator}
        , id_{id}
    {
    }

    int id()
    {
        return id_;
    }

    virtual void send(const string&) = 0;

    virtual void receive(const string&) = 0;

protected:
    Mediator* mediator_;
    int       id_;
};

class ColleagueX : public Colleague {
public:
    using Colleague::Colleague;

    void send(const string& message) override;

    void receive(const string& message) override
    {
        cout << "ColleagueX " << id_ << " " << __func__ << " " << message
             << endl;
    }
};

class Mediator {
public:
    virtual ~Mediator() = default;

    virtual void add(Colleague* colleague) = 0;
    virtual void distribute(Colleague*    colleadgue,
                            const string& message) = 0;
};

class MediatorX : public Mediator {
public:
    void add(Colleague* colleague) override
    {
        colleagues_.push_back(colleague);
    }

    void distribute(Colleague* colleague, const string& message) override
    {
        for (auto a_colleague : colleagues_) {
            if (a_colleague->id() != colleague->id()) {
                a_colleague->receive(message);
            }
        }
    }

private:
    vector<Colleague*> colleagues_;
};

void ColleagueX::send(const string& message)
{
    cout << "ColleagueX " << id_ << " " << __func__ << " " << message
         << endl;
    mediator_->distribute(this, message);
}

int main()
{
    MediatorX  mediator;
    ColleagueX colleague_0{&mediator, 1};
    ColleagueX colleague_1{&mediator, 2};
    ColleagueX colleague_2{&mediator, 3};

    mediator.add(&colleague_0);
    mediator.add(&colleague_1);
    mediator.add(&colleague_2);

    colleague_0.send("Hi");
    colleague_2.send("Hello");
}

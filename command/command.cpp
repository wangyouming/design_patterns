
#include <iostream>  // std::cout std::endl
#include <utility>   // std::move
#include <vector>    // std::vector

using std::cout;
using std::endl;
using std::vector;

class ReceiverX {
public:
    void increase()
    {
        number_ += 1;
        cout << "ReceiverX " << __func__ << endl;
    }

    void decrease()
    {
        number_ -= 1;
        cout << "ReceiverX " << __func__ << endl;
    }

private:
    int number_ = 0;
};

class ReceiverY {
public:
    void push()
    {
        numbers_.emplace_back();
        cout << "ReceiverY " << __func__ << endl;
    }

    void pop()
    {
        numbers_.pop_back();
        cout << "ReceiverY " << __func__ << endl;
    }

private:
    vector<int> numbers_;
};

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class CommandX : public Command {
public:
    explicit CommandX(ReceiverX& receiver)
        : receiver_{receiver}
    {
    }

    void execute() override
    {
        count_ += 1;
        receiver_.increase();
    }

    void undo() override
    {
        if (count_ == 0)
            return;

        receiver_.decrease();
        count_ -= 1;
    }

private:
    ReceiverX& receiver_;
    int        count_ = 0;
};

class CommandY : public Command {
public:
    explicit CommandY(ReceiverY& receiver)
        : receiver_{receiver}
    {
    }

    void execute() override
    {
        receiver_.push();
    }

    void undo() override
    {
        receiver_.pop();
    }

private:
    ReceiverY& receiver_;
};

class MacroCommand : public Command {
public:
    explicit MacroCommand(const vector<Command*>& commands)
        : commands_{commands}
    {
    }
    explicit MacroCommand(vector<Command*>&& commands)
        : commands_{std::move(commands)}
    {
    }

    void execute() override
    {
        for (auto command : commands_) {
            command->execute();
        }
    }

    void undo() override
    {
        for (auto command : commands_) {
            command->undo();
        }
    }

private:
    vector<Command*> commands_;
};

class Invoker {
public:
    void addCommand(Command* command)
    {
        commands_.push_back(command);
    }

    void invokeAll()
    {
        for (auto command : commands_) {
            command->execute();
        }
    }

private:
    vector<Command*> commands_;
};

int main()
{
    ReceiverX receiver_x;
    CommandX  command_x{receiver_x};

    ReceiverY receiver_y;
    CommandY  command_y{receiver_y};

    vector<Command*> commands{&command_x, &command_y};
    MacroCommand     macro_command{std::move(commands)};

    Invoker invoker;
    invoker.addCommand(&command_x);
    invoker.addCommand(&command_y);
    invoker.addCommand(&macro_command);
    invoker.invokeAll();
}


#include <iostream>  // std::cout std::endl

using std::cout;
using std::endl;

class Handler {
public:
    virtual ~Handler() = default;

    void set_successor(Handler* successor) noexcept
    {
        successor_ = successor;
    }

    virtual void handleRequest()
    {
        if (successor_) {
            successor_->handleRequest();
        }
    }

private:
    Handler* successor_;
};

class HandlerX : public Handler {
public:
    bool canHandle()
    {
        return false;
    }

    void handleRequest() override
    {
        if (canHandle()) {
            cout << "HandlerX " << __func__ << endl;
        } else {
            cout << "HandlerX can't " << __func__ << endl;
            Handler::handleRequest();
        }
    }
};

class HandlerY : public Handler {
public:
    bool canHandle()
    {
        return true;
    }

    void handleRequest() override
    {
        if (canHandle()) {
            cout << "HandlerY " << __func__ << endl;
        } else {
            cout << "HandlerY can't " << __func__ << endl;
            Handler::handleRequest();
        }
    }
};

int main()
{
    HandlerX handler_x;
    HandlerY handler_y;

    handler_x.set_successor(&handler_y);
    handler_x.handleRequest();
}

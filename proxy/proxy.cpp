
#include <iostream>  // std::cout std::endl
#include <memory>    // std::make_unique std::unique_ptr

using std::make_unique;
using std::unique_ptr;

class Subject {
public:
    virtual ~Subject() = default;

    virtual void request() = 0;
};

class SubjectX : public Subject {
public:
    void request() override
    {
        std::cout << "SubjectX " << __func__ << std::endl;
    }
};

class Proxy : public Subject {
public:
    Proxy()
        : subject_{make_unique<SubjectX>()}
    {
    }

    void request() override
    {
        subject_->request();
    }

private:
    unique_ptr<Subject> subject_;
};

int main()
{
    Proxy proxy;
    proxy.request();
}

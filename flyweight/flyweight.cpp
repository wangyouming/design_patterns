
#include <iostream>  // std::cout std::endl
#include <map>       // std::map
#include <memory>    // std::make_unique std::unique_ptr

using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;

class FlyWeight {
public:
    virtual ~FlyWeight() = default;
    virtual void operation() = 0;
};

class FlyWeightX : public FlyWeight {
public:
    explicit FlyWeightX(int state)
        : state_{state}
    {
    }

    void operation() override
    {
        cout << "FlyWeightX " << state_ << endl;
    }

private:
    int state_;
};

class FlyWeightY : public FlyWeight {
public:
    explicit FlyWeightY(int state)
        : state_{state}
    {
    }

    void operation() override
    {
        cout << "FlyWeightY " << state_ << endl;
    }

private:
    int state_;
};

class FlyWeightManager {
public:
    FlyWeight* getFlyWeight(int key)
    {
        if (flies_.find(key) != flies_.end()) {
            return flies_[key].get();
        }

        auto fly = make_unique<FlyWeightY>(key);
        return fly.get();
    }

private:
    std::map<int, unique_ptr<FlyWeight>> flies_;
};

int main()
{
    FlyWeightManager manager;
    manager.getFlyWeight(1)->operation();
    manager.getFlyWeight(2)->operation();
}

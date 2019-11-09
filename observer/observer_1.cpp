
#include <iostream>       // std::cout std::endl
#include <unordered_set>  // std::unordered_set

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

class Subject {
public:
    virtual ~Subject() = default;
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void clearObservers() = 0;
    virtual void notifyObservers() const = 0;
    virtual void set_changed(bool changed) = 0;
};

class SubjectX : public Subject {
public:
    void registerObserver(Observer* observer) override
    {
        observers_.insert(observer);
    }

    void removeObserver(Observer* observer) override
    {
        auto iter = observers_.find(observer);
        if (iter != observers_.end()) {
            observers_.erase(iter);
        }
    }

    void clearObservers() override
    {
        observers_.clear();
    }

    void notifyObservers() const override
    {
        if (!changed_)
            return;

        changed_ = false;
        for (auto observer : observers_) {
            observer->update();
        }
    }

    void set_changed(bool changed) override
    {
        changed_ = changed;
    }

    int value() const
    {
        return value_;
    }

    void set_value(int value)
    {
        value_ = value;
        set_changed(true);
        notifyObservers();
    }

private:
    std::unordered_set<Observer*> observers_;
    mutable bool                  changed_{false};
    int                           value_{0};
};

class ObserverX : public Observer {
public:
    explicit ObserverX(SubjectX* subject)
        : subject_(subject)
    {
        subject_->registerObserver(this);
    }

    ~ObserverX()
    {
        subject_->removeObserver(this);
    }

    void update() override
    {
        std::cout << subject_->value() << std::endl;
    }

private:
    SubjectX* subject_;
};

int main()
{
    SubjectX  subject;
    ObserverX observer(&subject);

    subject.set_value(5);
    subject.removeObserver(&observer);
    subject.set_value(4);
}

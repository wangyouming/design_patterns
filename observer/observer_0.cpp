
#include <iostream>       // std::cout std::endl
#include <unordered_set>  // std::unordered_set

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

class Subject {
public:
    void registerObserver(Observer* observer)
    {
        observers_.insert(observer);
    }

    void removeObserver(Observer* observer)
    {
        auto iter = observers_.find(observer);
        if (iter != observers_.end()) {
            observers_.erase(iter);
        }
    }

    void clearObservers()
    {
        observers_.clear();
    }

    void notifyObservers()
    {
        if (!changed_)
            return;

        set_changed(false);
        for (auto observer : observers_) {
            observer->update();
        }
    }

protected:
    void set_changed(bool changed)
    {
        changed_ = changed;
    }

    bool changed() const
    {
        return changed_;
    }

private:
    std::unordered_set<Observer*> observers_;
    bool                          changed_ = false;
};

class SubjectX : public Subject {
public:
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
    int value_ = 0;
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

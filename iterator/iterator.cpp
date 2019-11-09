
#include <iostream>   // std::cout std::cout
#include <memory>     // std::shared_ptr std::make_shared
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::string;

class MenuItem {
public:
    MenuItem(string name, string desc, bool vegetarian, double price)
        : name_{name}
        , desc_{desc}
        , vegetarian_{vegetarian}
        , price_{price}
    {
    }

    string name() const
    {
        return name_;
    }

    string desc() const
    {
        return desc_;
    }

    bool vegetarian() const
    {
        return vegetarian_;
    }

    double price() const
    {
        return price_;
    }

private:
    string name_;
    string desc_;
    bool   vegetarian_;
    double price_;
};

std::ostream& operator<<(std::ostream& os, const MenuItem& item)
{
    return os << item.name() << ", $" << item.price() << "\n  "
              << item.desc();
}

class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool                 hasNext() = 0;
    virtual shared_ptr<MenuItem> next() = 0;
};

class Menu {
public:
    virtual ~Menu() = default;
    virtual shared_ptr<Iterator> createIterator() = 0;
};

class DinerMenuIterator : public Iterator {
public:
    DinerMenuIterator(shared_ptr<MenuItem>* items, int count)
        : items_{items}
        , count_{count}
    {
    }

    shared_ptr<MenuItem> next()
    {
        auto item = items_[index_];
        index_ += 1;
        return item;
    }

    bool hasNext()
    {
        return index_ < count_;
    }

private:
    shared_ptr<MenuItem>* items_;
    int                   count_;
    int                   index_ = 0;
};

class DinerMenu : public Menu {
public:
    void addItem(string name, string desc, bool vegetarian, double price)
    {
        if (numOfItems_ >= MAX_ITEMS) {
            throw std::runtime_error{"Sorry, menu is full!"};
        } else {
            menuItems_[numOfItems_] =
                make_shared<MenuItem>(name, desc, vegetarian, price);
            numOfItems_ += 1;
        }
    }

    shared_ptr<Iterator> createIterator() override
    {
        return make_shared<DinerMenuIterator>(menuItems_, numOfItems_);
    }

private:
    static constexpr int MAX_ITEMS = 6;
    int                  numOfItems_ = 0;
    shared_ptr<MenuItem> menuItems_[MAX_ITEMS];
};

int main()
{
    DinerMenu diner_menu;
    diner_menu.addItem("X", "desc_x", true, 0.5);
    diner_menu.addItem("Y", "desc_y", true, 0.6);
    diner_menu.addItem("Z", "desc_z", true, 0.7);

    Menu* menu = &diner_menu;
    auto  iter = menu->createIterator();
    while (iter->hasNext()) {
        auto item = iter->next();
        cout << *item << endl;
    }
}


#include <iostream>  // std::cout std::endl
#include <vector>    // std::vector

class Component {
public:
    virtual ~Component() = default;

    virtual Component* operator[](size_t /* index */)
    {
        return nullptr;
    }

    virtual void add(Component* /* component */)
    {
    }

    virtual void remove(size_t /* index */)
    {
    }

    virtual void operation() = 0;
};

class Composite : public Component {
public:
    Component* operator[](size_t index) override
    {
        return components_[index];
    }

    void add(Component* component) override
    {
        components_.push_back(component);
    }

    void remove(size_t index) override
    {
        components_.erase(components_.begin() + index);
    }

    void operation() override
    {
        for (auto component : components_) {
            component->operation();
        }
    }

private:
    std::vector<Component*> components_;
};

class Leaf : public Component {
public:
    explicit Leaf(int id)
        : id_{id}
    {
    }

    void operation() override
    {
        std::cout << "Leaf "
                  << "id " << id_ << " " << __func__ << std::endl;
    }

private:
    int id_;
};

int main()
{
    Composite composite;

    Leaf leaf_0{0};
    Leaf leaf_1{1};
    Leaf leaf_2{2};

    composite.add(&leaf_0);
    composite.add(&leaf_1);
    composite.add(&leaf_2);

    composite.remove(2);

    composite.operation();
}

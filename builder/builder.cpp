
#include <iostream>  // std::cout std::endl
#include <memory>    // std::shared_ptr std::make_shared
#include <string>    // std::string

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::string;

class Product {
public:
    void makeA(const string& part)
    {
        part_a_ = part;
    }

    void makeB(const string& part)
    {
        part_b_ = part;
    }

    void makeC(const string& part)
    {
        part_c_ = part;
    }

    string get()
    {
        return part_a_ + " " + part_b_ + " " + part_c_;
    }

private:
    string part_a_;
    string part_b_;
    string part_c_;
};

class Builder {
public:
    virtual ~Builder() = default;

    Builder()
        : product_{make_shared<Product>()}
    {
    }

    shared_ptr<Product> get()
    {
        return product_;
    }

    virtual void buildPartA() = 0;

    virtual void buildPartB() = 0;

    virtual void buildPartC() = 0;

protected:
    shared_ptr<Product> product_;
};

class BuilderX : public Builder {
public:
    void buildPartA() override
    {
        product_->makeA("A-X");
    }

    void buildPartB() override
    {
        product_->makeB("B-X");
    }

    void buildPartC() override
    {
        product_->makeC("C-X");
    }
};

class BuilderY : public Builder {
public:
    void buildPartA() override
    {
        product_->makeA("A-Y");
    }

    void buildPartB() override
    {
        product_->makeB("B-Y");
    }

    void buildPartC() override
    {
        product_->makeC("C-Y");
    }
};

class Director {
public:
    void set_builder(Builder* builder)
    {
        builder_ = builder;
    }

    shared_ptr<Product> get()
    {
        return builder_->get();
    }

    void construct()
    {
        builder_->buildPartA();
        builder_->buildPartB();
        builder_->buildPartC();
    }

private:
    Builder* builder_;
};

int main()
{
    Director director;
    BuilderX builder_x;
    director.set_builder(&builder_x);
    director.construct();

    auto product = director.get();
    cout << product->get() << endl;

    BuilderY builder_y;
    director.set_builder(&builder_y);
    director.construct();

    product = director.get();
    cout << product->get() << endl;
}

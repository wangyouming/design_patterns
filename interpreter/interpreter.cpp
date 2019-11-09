
#include <iostream>  // std::cout std::endl
#include <map>       // std::map

using std::cout;
using std::endl;
using std::string;

class Context {
public:
    void set(const string& key, bool value)
    {
        map_.insert({key, value});
    }

    bool get(const string& key)
    {
        return map_[key];
    }

private:
    std::map<string, bool> map_;
};

class Expression {
public:
    virtual ~Expression() = default;

    virtual bool interpret(Context*) = 0;
};

class TerminalExpression : public Expression {
public:
    explicit TerminalExpression(const string& value)
        : value_{value}
    {
    }

    bool interpret(Context* context)
    {
        return context->get(value_);
    }

private:
    string value_;
};

class NonterminalExpression : public Expression {
public:
    NonterminalExpression(Expression* lhs, Expression* rhs)
        : lhs_{lhs}
        , rhs_{rhs}
    {
    }

    bool interpret(Context* ctx)
    {
        return lhs_->interpret(ctx) && rhs_->interpret(ctx);
    }

private:
    Expression* lhs_;
    Expression* rhs_;
};

int main()
{
    TerminalExpression    ternimal_expression_a{"A"};
    TerminalExpression    ternimal_expression_b{"B"};
    NonterminalExpression nonterminal_expression{&ternimal_expression_a,
                                                 &ternimal_expression_b};

    Context context;
    context.set("A", true);
    context.set("B", false);

    cout << ternimal_expression_a.interpret(&context) << " "
         << ternimal_expression_b.interpret(&context) << " "
         << nonterminal_expression.interpret(&context) << endl;
}

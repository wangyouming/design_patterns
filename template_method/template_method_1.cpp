
#include <iostream>       // std::cout std::endl
#include <unordered_set>  // std::unordered_set

using std::cout;
using std::endl;
using std::unordered_set;

class X {
public:
    explicit X(int id)
        : id_{id}
    {
    }

    int id() const
    {
        return id_;
    }

    bool operator==(const X& other) const
    {
        return id_ == other.id_;
    }

private:
    int id_ = 0;
};

namespace std {
template <>
struct hash<X> {
    size_t operator()(const X& x) const noexcept
    {
        return hash<int>()(x.id());
    }
};
}  // namespace std

int main()
{
    unordered_set<X> set;
    set.insert(X(1));
    set.insert(X(1));
    set.insert(X(2));
    set.insert(X(2));

    cout << set.size() << endl;
}

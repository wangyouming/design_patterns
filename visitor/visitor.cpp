
#include <iostream>  // std::cout std::endl
#include <string>    // std::string
#include <vector>    // std::vector

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Visitor;
class File;
class Directory;

class FileComponent {
public:
    virtual ~FileComponent() = default;
    virtual void   accept(const Visitor& visitor, size_t level) const = 0;
    virtual string name() const = 0;
};

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(const File& file, size_t level) const = 0;
    virtual void visit(const Directory& directory, size_t level) const = 0;
};

class File : public FileComponent {
public:
    explicit File(string name)
        : name_{name}
    {
    }

    string name() const override
    {
        return name_;
    }

    void accept(const Visitor& visitor, size_t level) const override
    {
        visitor.visit(*this, level);
    }

private:
    string name_;
};

class Directory : public FileComponent {
public:
    explicit Directory(string name)
        : name_{name}
    {
    }

    string name() const override
    {
        return name_;
    }

    void accept(const Visitor& visitor, size_t level) const override
    {
        visitor.visit(*this, level);
    }

    void addFileComponent(FileComponent* file_component)
    {
        file_components_.push_back(file_component);
    }

    auto begin() const
    {
        return file_components_.cbegin();
    }

    auto end() const
    {
        return file_components_.cend();
    }

private:
    string                 name_;
    vector<FileComponent*> file_components_;
};

class VisitorX : public Visitor {
public:
    void visit(const File& file, size_t level) const override
    {
        cout << string(level, ' ') << file.name() << endl;
    }

    void visit(const Directory& directory, size_t level) const override
    {
        cout << string(level, ' ') << directory.name() << endl;
        for (auto file_component : directory) {
            file_component->accept(*this, level + 1);
        }
    }
};

int main()
{
    Directory directory_a{"directory_a"};

    File file_a{"file_a"};
    directory_a.addFileComponent(&file_a);

    File file_b{"file_b"};
    directory_a.addFileComponent(&file_b);

    Directory directory_b{"directory_b"};

    File file_c{"file_c"};
    directory_b.addFileComponent(&file_c);

    File file_d{"file_d"};
    directory_b.addFileComponent(&file_d);

    directory_a.addFileComponent(&directory_b);

    VisitorX visitor;
    directory_a.accept(visitor, 0);
}

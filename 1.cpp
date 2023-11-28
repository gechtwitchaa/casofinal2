#include <iostream>
#include <vector>
#include <functional>


class VariantValue {
public:
    virtual ~VariantValue() {}
    virtual void print() const = 0;
};

class VariantInt : public VariantValue {
private:
    int value;

public:
    VariantInt(int val) : value(val) {}

    void print() const override {
        std::cout << "Integer: " << value << std::endl;
    }
};

class VariantString : public VariantValue {
private:
    std::string value;

public:
    VariantString(const std::string& val) : value(val) {}

    void print() const override {
        std::cout << "String: " << value << std::endl;
    }
};

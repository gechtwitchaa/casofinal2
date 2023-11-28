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

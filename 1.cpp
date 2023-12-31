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

class VariantList : public VariantValue {
private:
    std::vector<VariantValue*> value;

public:
    void addValue(VariantValue* val) {
        value.push_back(val);
    }

    void print() const override {
        std::cout << "List: [";
        for (const auto& elem : value) {
            elem->print();
        }
        std::cout << "]" << std::endl;
    }

    ~VariantList() {
        for (auto& elem : value) {
            delete elem;
        }
    }
};
class VariantProcedure : public VariantValue {
private:
    std::function<void()> value;

public:
    VariantProcedure(const std::function<void()>& val) : value(val) {}

    void print() const override {
        std::cout << "Procedure" << std::endl;
    }

    void execute() const {
        value();
    }
};


class Variant {
private:
    VariantValue* data;

public:
    Variant() : data(nullptr) {}

    void setData(VariantValue* newData) {
        data = newData;
    }

    void printData() const {
        if (data) {
            data->print();
        } else {
            std::cout << "No data" << std::endl;
        }
    }

    ~Variant() {
        delete data;
    }
};

int main() {
    Variant v;

    VariantInt* intValue = new VariantInt(42);
    VariantString* stringValue = new VariantString("Hello, world!");
    VariantList* listValue = new VariantList();
    listValue->addValue(new VariantInt(1));
    listValue->addValue(new VariantString("Two"));
    VariantProcedure* procValue = new VariantProcedure([]() { std::cout << "Executing procedure" << std::endl; });

    v.setData(intValue);
    v.printData();

    v.setData(stringValue);
    v.printData();

    v.setData(listValue);
    v.printData();

    v.setData(procValue);
    v.printData();
    procValue->execute();

    delete intValue;
    delete stringValue;
    delete listValue;
    delete procValue;

    return 0;
}



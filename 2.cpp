#include <iostream>
#include <vector>
#include <string>
#include <functional>

class VariantValue {
public:
    virtual ~VariantValue() {}
    virtual std::string to_string() const = 0;
};

class VariantInt : public VariantValue {
private:
    int value;

public:
    VariantInt(int val) : value(val) {}

    std::string to_string() const override {
        return "Integer: " + std::to_string(value);
    }
};

class VariantString : public VariantValue {
private:
    std::string value;

public:
    VariantString(const std::string& val) : value(val) {}

    std::string to_string() const override {
        return "String: " + value;
    }
};

class VariantList : public VariantValue {
private:
    std::vector<VariantValue*> value;

public:
    void addValue(VariantValue* val) {
        value.push_back(val);
    }

    std::string to_string() const override {
        std::string result = "List: [";
        for (const auto& elem : value) {
            result += elem->to_string() + " ";
        }
        result += "]";
        return result;
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

    std::string to_string() const override {
        return "Procedure";
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

    std::string to_string() const {
        if (data) {
            return data->to_string();
        } else {
            return "No data";
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
    std::cout << v.to_string() << std::endl;

    v.setData(stringValue);
    std::cout << v.to_string() << std::endl;

    v.setData(listValue);
    std::cout << v.to_string() << std::endl;

    v.setData(procValue);
    std::cout << v.to_string() << std::endl;
    procValue->execute();

    delete intValue;
    delete stringValue;
    delete listValue;
    delete procValue;

    return 0;
}

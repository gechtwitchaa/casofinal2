#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Definición de la clase base para representar diferentes tipos de datos
class VariantValue {
public:
    virtual ~VariantValue() {}
    virtual json to_json() const = 0;
};

// Clases para almacenar números, cadenas, listas y procedimientos
class VariantInt : public VariantValue {
private:
    int value;

public:
    VariantInt(int val) : value(val) {}

    json to_json() const override {
        return json(value);
    }
};

class VariantString : public VariantValue {
private:
    std::string value;

public:
    VariantString(const std::string& val) : value(val) {}

    json to_json() const override {
        return json(value);
    }
};

class VariantList : public VariantValue {
private:
    std::vector<VariantValue*> value;

public:
    void addValue(VariantValue* val) {
        value.push_back(val);
    }

    json to_json() const override {
        json result = json::array();
        for (const auto& elem : value) {
            result.push_back(elem->to_json());
        }
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

    json to_json() const override {
        return "Procedure";
    }

    void execute() const {
        value();
    }
};

// Clase Variant que puede almacenar cualquier tipo de dato
class Variant {
private:
    VariantValue* data;

public:
    Variant() : data(nullptr) {}

    void setData(VariantValue* newData) {
        data = newData;
    }

    json to_json() const {
        if (data) {
            return data->to_json();
        } else {
            return nullptr; // O cualquier otro valor nulo para representar "No data"
        }
    }

    ~Variant() {
        delete data;
    }
};


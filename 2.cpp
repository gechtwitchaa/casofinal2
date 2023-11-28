
class VariantValue {
public:
    virtual ~VariantValue() {}
    virtual std::string to_string() const = 0;
};

class VariantInt : public VariantValue {
    // ... resto del código

public:
    std::string to_string() const override {
        return "Integer: " + std::to_string(value);
    }
};

class VariantString : public VariantValue {

public:
    std::string to_string() const override {
        return "String: " + value;
    }
};

class VariantList : public VariantValue {
    // ... resto del código

public:
    std::string to_string() const override {
        std::string result = "List: [";
        for (const auto& elem : value) {
            result += elem->to_string() + " ";
        }
        result += "]";
        return result;
    }
};

class VariantProcedure : public VariantValue {
    // ... resto del código

public:
    std::string to_string() const override {
        return "Procedure";
    }
};


class

public:
    std::string to_string() const {
        if (data) {
            return data->to_string();
        } else {
            return "No data";
        }
    }
};

// Clase base para representar diferentes tipos de datos
class VariantValue {
public:
    virtual ~VariantValue() {}
    virtual std::string to_string() const = 0;
};


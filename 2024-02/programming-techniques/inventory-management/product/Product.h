#include <unordered_map>
#include <string>

#ifndef PRODUCT_H
#define PRODUCT_H

class Product
{
private:
    unsigned int id{};
    std::string name{};
    unsigned int quantity{};
    time_t created_at{};
    time_t updated_at{};

    const void setId(const unsigned int& id) { this->id = id; };
public:
    // static members
    static unsigned int lastId;
    static std::unordered_map<unsigned int, Product*> products;

    // getters
    const unsigned int getId() const { return this->id; }
    const std::string getName() const { return this->name; }
    const unsigned int getQuantity() const { return this->quantity; }

    // setters
    const void setName(const std::string& name) { this->name = name; };
    const void setQuantity(const unsigned int& quantity) { this->quantity = quantity; };

    // static members function
    static const void list(const bool& full);
    static const unsigned int askForId();
    static const void createOne();
    static const void use();
    static const void restock();
    static const void updateOne();
    static const void deleteOne();
    static const void deleteAll();

    // constructor
    Product(const std::string& name, const unsigned int& quantity);
};

#endif

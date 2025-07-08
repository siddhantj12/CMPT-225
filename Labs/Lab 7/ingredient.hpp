/*
Header file for an ingredient.
Very simple so we define everything here.
*/
#ifndef _INGREDIENT_HPP_
#define _INGREDIENT_HPP_

#include <string>

class Ingredient {
    private:
        std::string brand;
        std::string name;
    public:
        //parameterized constructor forcing creation of an object with brand & name
        Ingredient(std::string b, std::string n) {
            brand = b;
            name = n;
        }
        //getters and setters
        std::string getBrand() const { return brand; }
        std::string getName() const { return name; }
        void setBrand(std::string b) { brand = b; }
        void setName(std::string n) { name = n; }

        //needed by the unordered_map to figure out if this is equal to another Ingredient object
        //if they are equal, the second one will not be inserted
        bool operator==(const Ingredient& other) const {
            return name == other.name;
        }
};

//needed by the unordered_map to perform the hashing process
//only have to implement 1 method (like the comparator class in Heap): the operator()
class HashFunctionForIngredient {
    public:
        //this hashing function is *very* simple, which often means easy to cause
        // collision. Not a good one but serves the demo purpose. Try other ways.
        //return type is an unsigned int for general uses in C++
        size_t operator()(const Ingredient& ingred) const {
            return ingred.getName().length();
        }
};

#endif
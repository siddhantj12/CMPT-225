#include "ingredient.hpp"
#include "measurement.hpp"

#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;

int main() {
    // create an unordered_map with Ingredient as key and custom hash
    unordered_map<Ingredient, Measurement, HashFunctionForIngredient> recipe;

    // populate the recipe using different insert methods
    Ingredient butter("Land O Lakes", "unsalted butter");
    recipe.insert(make_pair(butter, Measurement{1, "cup"})); // copy insertion

    // move insert (map acquires the temporary pair)
    recipe.insert(make_pair(Ingredient("Domino", "powdered sugar"), Measurement{0.75f, "cup"}));

    // initializer-list insertion
    recipe.insert({
        {Ingredient("McCormick", "vanilla extract"), {1, "teaspoon"}},
        {Ingredient("King Arthur", "all-purpose flour"), {2, "cups"}},
        {Ingredient("Generic", "cornstarch"), {1, "tablespoon"}}, // mistakenly 1 instead of 2
        {Ingredient("Morton", "table salt"), {0.5f, "teaspoon"}}
    });

    // print all the content in the recipe
    for (const auto& p : recipe) {
        cout << p.second.quantity << " " << p.second.unit
             << " of " << p.first.getBrand() << " " << p.first.getName() << endl;
    }
    cout << endl;

    // use the [] operator to update the quantity of cornstarch from 1 to 2
    recipe[Ingredient("Generic", "cornstarch")].quantity = 2;

    // print all the content in the recipe again
    for (const auto& p : recipe) {
        cout << p.second.quantity << " " << p.second.unit
             << " of " << p.first.getBrand() << " " << p.first.getName() << endl;
    }
    cout << endl;

    // print some information about the unordered_map
    cout << "empty? " << recipe.empty() << endl;
    cout << "size: " << recipe.size() << endl;
    Ingredient search("Land O Lakes", "unsalted butter");
    auto got = recipe.find(search);
    if (got == recipe.end()) cout << "No need for " << search.getName() << endl;
    else cout << "Need " << got->second.quantity << " " << got->second.unit
             << " of " << search.getBrand() << " " << search.getName() << endl;
    cout << "bucket count: " << recipe.bucket_count() << endl;
    cout << "load factor: " << recipe.load_factor() << endl;

    return 0;
}

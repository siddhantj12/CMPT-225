/*
The C++ STL offers a Hash Table ADT called unordered_map,
which has all the standard operations (e.g., insert, remove -- called erase, find)
plus a few more (e.g., load_factor, direct access via []).
It requires that each key has to be unique, otherwise insert will fail.
*/

#include "ingredient.hpp"
#include "measurement.hpp"

#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;

int main() {

    //create an unordered_map object storing a recipe
    unordered_map<string, Measurement> shortBreadCookies;

    //populate the recipe with ingredients using different ways of insert
    pair<string, Measurement> butter ("unsalted butter", {1, "cup"});
    shortBreadCookies.insert(butter); //copy insertion (copy from a pair object)

    //move insert (unorder_map object acquires the pair object)
    shortBreadCookies.insert(make_pair<string, Measurement>("powered sugar", {0.75, "cup"}));

    //initializer list insertion
    shortBreadCookies.insert({{"vanilla extract", {1, "teaspoon"}},
                                {"all-purpose flour", {2, "cups"}},
                                {"cornstarch", {1, "tablespoons"}}, //mistakenly used 1 instead of 2
                                {"table salt", {0.5, "teaspoon"}}});


    //print all the content in the recipe
    for (auto& p : shortBreadCookies) { //let the compiler infer the type using auto
        cout << p.second.quantity << " " << p.second.unit << " of " << p.first << endl;
    }
    cout << endl;

    //use the [] operator to update the quantity of cornstach from 1 to 2
    //***your code***
     shortBreadCookies["cornstarch"].quantity = 2;

    //print all the content in the recipe again
    for (auto& p : shortBreadCookies) { //let the compiler infer the type using auto
        cout << p.second.quantity << " " << p.second.unit << " of " << p.first << endl;
    }
    cout << endl;

    //print all the content in the recipe again
    for (auto& p : shortBreadCookies) { //let the compiler infer the type using auto
        cout << p.second.quantity << " " << p.second.unit << " of " << p.first << endl;
    }
    cout << endl;

    //print some information about the unordered_map (i.e., hashtable)
    //feel free to try more by referencing the API at
    //https://cplusplus.com/reference/unordered_map/unordered_map/
    cout << "empty? " << shortBreadCookies.empty() << endl;
    cout << "size: " << shortBreadCookies.size() << endl;
    string ingredient = "unsalted butter"; //replace this with "butter" and try again
    auto got = shortBreadCookies.find("unsalted butter");
    if (got == shortBreadCookies.end()) cout << "No need for " << ingredient << endl;
    else cout << "Need " << got->second.quantity << " " << got->second.unit 
            << " of " << ingredient << endl;
    cout << "bucket count: " << shortBreadCookies.bucket_count() << endl;
    cout << "load factor: " << shortBreadCookies.load_factor() << endl;

    return 0;
}
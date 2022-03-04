// https://github.com/nlohmann/json

#include <iostream>
#include "json.hpp"

using nlohmann::json;

int main() {
    json object;
    object["Key"] = "Value";
    object["OtherKey"]["NestedKey"] = json();
    auto as_string = object.dump(4);
    std::cout << as_string << std::endl;
    auto other_object = json::parse(as_string);
    std::cout << other_object.dump(2) << std::endl;
    for (auto item = object.begin(); item != object.end(); ++item) {
        std::cout << item.key() << ": " << item.value() << std::endl;
    }
    std::map<std::string, std::string> to_send = {
            {"first key", "first val"},
            {"second key", "second val"}
    };
    std::vector<int> numbers = {1, 3, 42, 5, 4};
    json from_map(to_send);
    json from_list(numbers);
    std::cout << from_map.dump(4) << std::endl;
    std::cout << from_list.dump() << std::endl;
}


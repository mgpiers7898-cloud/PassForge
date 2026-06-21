#include<iostream>
#include<string>
#include<random>
#include<string_view>

namespace CharactersPool
{
    constexpr std::string_view alphabets = "abcdefghijklmnopqrstuvwxyz";
    constexpr std::string_view capitalAlphabets{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    constexpr std::string_view numbers{"0123456789"};
    constexpr std::string_view symbols{"~`!@#$%^&*()_-+={}[];:\"\'<>,?/|\\"};
};
// charset will use in switch for the specify the using of Str's
enum class Charset{
    Alpha,
    CapAlpha,
    Digit,
    Symbol
};
constexpr std::string_view typeSpecify(Charset set){
    switch(set){

        case Charset::Alpha    :    return "Alpha";
        case Charset::CapAlpha :    return "CapAlpha";
        case Charset::Digit    :    return "Digit";
        case Charset::Symbol   :    return "Sign";
    }
    return {};
}

namespace GeneratorMethods
{
    
};

auto main() -> int
{

}
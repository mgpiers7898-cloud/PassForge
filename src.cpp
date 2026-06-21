#include<iostream>
#include<string>
#include<random>
#include<string_view>
//one we want the Alphabets and numbers and other Signs also we want operators and strange mix of these things !:
// so at the first we make the all of these in each var (array) for itration in each one :
// namespace required for this one is better:
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
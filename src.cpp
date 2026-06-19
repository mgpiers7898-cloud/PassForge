#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include<random>
//one we want the Alphabets and numbers and other Signs also we want operators and strange mix of these things !:
// so at the first we make the all of these in each var (array) for itration in each one :
// namespace required for this one is better:
namespace Characters
{
    std::vector<char> alphabets{
        'a', 'b', 'c', 'd', 'e',
        'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o',
        'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y',
        'z'};
    std::vector<char> capital_alphabets{
        'A', 'B', 'C', 'D', 'E',
        'F', 'G', 'H', 'I', 'J',
        'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X', 'Y',
        'Z'};
    std::vector<char> signs{
        '~', '!', '@', '#', '$',
        '%', '^', '&', '*', '(',
        ')', '_', '-', '+', '=',
        '[', ']', '{', '}', ';',
        ':', '"', ' ', '<', '>',
        '/', '|', ',', '.'
    };
    std::vector<int> numbers
    {1,2,3,4,5,6,7,8,9,0};
    
    // random iteration or memory pool for radomizing through the lower level -> bit by bit?
};

namespace MemoryPool
{
    
};

auto main() -> int
{

}
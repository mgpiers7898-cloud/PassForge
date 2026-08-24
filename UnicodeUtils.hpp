#include <iostream>
#include <string>
#include <cstdint>
#include <array>
// this is a future Update still working on it!
namespace Translator
{
    constexpr std::array<char32_t, 34> emojiPool{
        U'\U0001F600', U'\U0001F601', U'\U0001F602',
        U'\U0001F923', U'\U0001F603', U'\U0001F604',
        U'\U0001F605', U'\U0001F606', U'\U0001F609',
        U'\U0001F60A', U'\U0001F60E', U'\U0001F60D',
        U'\U0001F618', U'\U0001F610', U'\U0001F621',
        U'\U0001F480', U'\U0001F47D', U'\U0001F47E',
        U'\U0001F916', U'\U0001F3AE', U'\U0001F512',
        U'\U0001F511', U'\U0001F504', U'\U000126A1',
        U'\U0001F525', U'\U0001F4A7', U'\U0001F680',
        U'\U0001F6E1', U'\U00012694', U'\U0001F9E0',
        U'\U0001F4BB', U'\U0001F5A5', U'\U00012328',
        U'\U0001F5B1'};


    inline std::string toUTF8(char32_t codePoint)
    {
        std::uint8_t byte1{}, byte2{}, byte3{}, byte4{};
        byte1 = 0xF0 | ((codePoint >> 18) & 0x07);
        byte2 = 0x80 | ((codePoint >> 12) & 0x3F);
        byte3 = 0x80 | ((codePoint >> 6)  & 0x3F);
        byte4 = 0x80 | ((codePoint        & 0x3F));

        std::string res{};
        res.reserve(4);
        res.push_back(static_cast<char>(byte1));
        res.push_back(static_cast<char>(byte2));
        res.push_back(static_cast<char>(byte3));
        res.push_back(static_cast<char>(byte4));

        return res;
    }
}
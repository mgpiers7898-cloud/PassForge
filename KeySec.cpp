#include "KeySec.hpp"

void KeySec::setGlobPass(std::string_view pass)
{
    auto bytes = Hash::sha512Raw(pass);
    this->globKey_ = uint512_t::load512(bytes.data());
}

void KeySec::genTMPKey()
{
    auto token = SecUtils::xorVal(this->iter512());
    std::uint64_t token64 = uint512_t::load64(token.data());

    if (IsDebuggerPresent() || this->isRemoteDebuggerPresent())
    {
        this->tempKey_ = Pool::Utilities::kGA ^ SecUtils::kGB ^ Hash::kGC;
    }
    else
    {
        __asm__ volatile
        (
            "mov %1, %0" :
            "=m"(tempKey_) :
            "r"(token64)
        );
    }
    token64 = 0;
    std::fill(token.begin(), token.end(), 0);
}

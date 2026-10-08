#include "KeySec.hpp"

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

void KeySec::setGlobPass(std::string_view pass)
{
    if(pass.empty()) return;
    if(isLocked()) return;

    this->globKey_.key_ = 
        uint512_t::load512(Hash::sha512Raw(pass).data());

    genTMPKey();
}

bool KeySec::isLocked() const
{
    std::uint8_t result = 0;
    const std::uint64_t* p = this->globKey_.key_.parts_;

    __asm__ volatile
    (
        "mov (%1), %%rax\n\t"
        "or 8(%1), %%rax\n\t"
        "or 16(%1), %%rax\n\t"
        "or 24(%1), %%rax\n\t"
        "or 32(%1), %%rax\n\t"
        "or 40(%1), %%rax\n\t"
        "or 48(%1), %%rax\n\t"
        "or 56(%1), %%rax\n\t"
        "setnz %0\n\t"
        : "=r"(result)
        : "r"(p)
        : "rax", "cc"
    );
    return result != 0;
}

bool KeySec::showOnce()
{
    if(this->tempKey_ == 0)
        return false;

    this->globKey_.toHex();
    Obf::apply(this->tempKey_,Obf::getThreeRand());
    this->tempKey_ = 0;

    armWd();

    return true;
}
#include "KeySec.hpp"

void KeySec::setGlobPass(std::string_view pass)
{
    auto bytes = Hash::sha512Raw(pass);
    this->globKey_ = uint512_t::load512(bytes.data());
}

void KeySec::showOnce()
{
    
}


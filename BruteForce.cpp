#include "BruteForce.hpp"

[[nodiscard]]std::optional<BF::Result> BF::run(std::string_view hash, std::string_view mask, HashType type)
{
    // parse : 
    auto charsets = Entropy::BF_Details::parseMask(mask);
    if(charsets.empty()) return std::nullopt;
    // keySpace :
    auto keySpace = Entropy::BF_Details::keySpaceOf(charsets);
    if(keySpace == 0) return std::nullopt;
    // estimate:
    auto info = Entropy::estimateFor(keySpace, type);
    // display :
    std::cout << "KeySpace : " << info.keySpace_ << '\n';
    std::cout << "Entropy : " << info.EntropyBits_ << '\n';
    std::cout << "Rate : " << info.rate_ << '\n';
    std::cout << "ETA : " << info.estimatedTime_ <<'\n';
    //  confirm :
    std::cout << "Proceed ? (y/n) >";
    char c;
    std::cin >> c;
    if(c != 'y' && c != 'Y') return std::nullopt;
    // timer :
    auto start = std::chrono::steady_clock::now();
    auto lastUpdate = start;
    // loop :
    std::vector<std::size_t> indices(charsets.size(), 0);
    std::size_t combos{};

    BF::Result r;
    while(1)
    {
        std::string candidate{};
        candidate.reserve(charsets.size());
        for(std::size_t i = 0; i < charsets.size(); ++i)
        {
            candidate += charsets[i][indices[i]];
        }
        // hash + compare :
        if(Hash::hasher(candidate, type) == hash)
        {
            auto now = std::chrono::steady_clock::now();
            double elapsed = std::chrono::duration<double>
                (now - start).count();

            r.password_ = candidate;
            r.time_ = elapsed;
            r.rate_ = combos / elapsed;
            r.entropy_ = info.EntropyBits_;
            r.targetHash_ = std::string(hash);

            std::cout << "\nFound: " << candidate << '\n';
            return r;
        }
        ++combos;

        // countdown every 0.5 sec :
        auto now = std::chrono::steady_clock::now();
        if(std::chrono::duration<double>(now - lastUpdate).count() > 0.5)
        {
            double elapsed = std::chrono::duration<double>(now - start).count();
            Timers::countdown(combos, keySpace, elapsed);
            lastUpdate = now;
        }
        // cancel check :
        if(GetAsyncKeyState('Q') & 0x8000)
            return std::nullopt;
        // odemeter increment :
        std::size_t pos = charsets.size();
        bool done = false;
        while(pos > 0)
        {
            --pos;
            if(++indices[pos] < charsets[pos].size()) break;
            indices[pos] = 0;
            if(pos == 0) {done = true; break;}
        }
        if(done) break;
    }
    // exhausted :
    std::cout << "\nExhausted!\n";
    return std::nullopt;
}
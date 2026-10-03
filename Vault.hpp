#include "PassForge.hpp"
#include "Hash.hpp"
#include <iostream>
// FOR NOW THIS IS A SIMPLE VAULT NOT A REALLY HARD ONE BUT IT WILL BE A STRICT VAULT SOON!

inline constexpr std::uint64_t kGC = 0x0F0F0F0F0F0F0F0FULL;
class Vault
{
private:
    class SecureBuffer
    {
    private:
        std::string data_{};
    public:
        SecureBuffer() {}
        SecureBuffer(std::string_view sv) : data_(sv) {}

        inline ~SecureBuffer()
        {
            std::fill(data_.begin(), data_.end(), 0);
        }
        SecureBuffer(const SecureBuffer&) = delete; // no copy
        SecureBuffer& operator=(const SecureBuffer&) = delete;
        SecureBuffer(SecureBuffer&&) = default;
        SecureBuffer& operator=(SecureBuffer&&) = default;

        inline const std::string& str() const {return this->data_;}
        inline bool empty() const {return this->data_.empty();}
        inline std::size_t size() const {return this->data_.size();}

        inline void replace(std::string&& newData)
        {
            std::fill(data_.begin(), data_.end(), 0);
            this->data_ = std::move(newData);
        }
    };

    std::unordered_map<std::string, SecureBuffer> buffer_{};
    bool right{false};
    bool check();
    void hashInPlace(std::string& label, SecureBuffer& data);
    void insert(std::string label, SecureBuffer data);

public:
    void add(std::string label, std::string_view pass);
    void rmv(const std::string& label);

    std::string getHashedPass(const std::string& label);
    bool cmpr(std::string_view pass, const std::string& label);
};

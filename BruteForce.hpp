#pragma once

#include "Hash.hpp"
#include "PassForge.hpp"
#include <dxgi.h>
inline std::unordered_map<std::size_t, std::string> errHand
{
    {1, "Empty Hash"}
};

struct Result
{
    double entropy_;
    double rate_;
    bool GPUIsReady_;
    std::string targetHash_;
    Entropy::CheckTime estimatedTime_;
    
    Result() = default;
    Result(double e, double r, bool GIR, const std::string& tarH, 
        const Entropy::CheckTime eT) :
            entropy_(e), rate_(r), GPUIsReady_(GIR),
                targetHash_(tarH), estimatedTime_(eT)
    {
    }

    std::string out();

    static inline std::string GPUModRoN()
    {
        static std::string cached;
        if(!cached.empty()) return cached;

        IDXGIFactory* factory = nullptr;
        IDXGIAdapter* adapter = nullptr;

        if(FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory1),
            reinterpret_cast<void**>(&factory)
                )))
            return "";

        if(FAILED(factory->EnumAdapters(0, &adapter)))
        {
            factory->Release();
            return "";
        }
        DXGI_ADAPTER_DESC desc = {};
        if(FAILED(adapter->GetDesc(&desc)))
        {
            adapter->Release();
            factory->Release();
            return "";
        }
        char narrow[128] = {};
        WideCharToMultiByte(CP_UTF8, 0, desc.Description, -1, narrow, 
            sizeof(narrow), nullptr, nullptr);

        adapter->Release();
        factory->Release();

        cached.reserve(sizeof(narrow));
        cached = narrow;
        return cached;
    }
    inline bool check()
    {
        return this->targetHash_.empty();
    }
};


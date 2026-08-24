---------- PassForge ----------
DelPiera :

A C++20 password generation framework built for learning and real-world use.

What This Is?
PassForge generates strong passwords from configurable character pools with policy validation, entropy estimation, and SHA-256 hashing. It's built as a modular framework — each component has a single job, and they connect through a clean pipeline.


Current Status :
THIS IS NOT COMPLETE.

The core works. Generation, validation, hashing, entropy — all functional. But there are known gaps: error handling is inconsistent, Unicode/emoji support is deferred, and the code hasn't been battle-tested. This is a working prototype, not a finished product


Features That Work Now:

CSPRNG-based random generation (Windows BCrypt)

Pool builder with 10+ character sets (ASCII, Base64, Hex, Binary, etc.)

Policy system (TooStrong, Strong, Medium, Simple)

Pool validation and deduplication

SHA-256 hashing via native Windows Crypto API

Entropy estimation

Brute-force crack time estimation

Interactive terminal prompt

File output for hashcat integration (future)

CMake build system


Architecture :
PoolType (bit flags)
    │
    ▼
PoolBuilder → builds the character pool
    │
    ▼
PoolCompatibility → validates pool against policy
    │
    ▼
PoolAnalyzer → categorizes characters by type
    │
    ▼
Generator → generates the password
    │
    ▼
PassForge (Facade) → one entry point for everything

Each module is independent. PoolBuilder knows nothing about Generator. PasswordPolicy knows nothing about PoolBuilder. The facade wires them together. That separation is deliberate — it makes the system easier to test, extend, and understand.

Build :
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .

Requires:
CMake 3.20+
MinGW-w64 or MSVC
Windows (currently Windows-only, Linux planned)

Usage :

Run passforge.exe. The interactive prompt will ask:
Pool type — ASCII, Base64, Hex, Binary, etc.
Policy — TooStrong, Strong, Medium, Simple

The password, entropy, hash, and crack time are output to the terminal. Passwords can be saved to a file with the hash included.

About
Name: DelPiera
Goal: Making and earning knowledge happen at the same time!

If you want to use or build on this idea, no problem. Just tell me what you want to do with it first — I'd appreciate that.


THERE'S NO THE BEST SOLUTION , ONLY IS A BETTER ONE!
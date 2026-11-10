# PassForge v1.0

Modern C++ password generation and brute-force framework.

> **THIS PROJECT IS NOT DONE.**
> v1.0 is the first public checkpoint of a project that will keep growing
> for years. Error handling is incomplete, some modules are stubs, and
> several components exist in the codebase but are not yet connected to
> the main flow. Read "What's In Progress" before assuming anything works
> end-to-end.

## Who Am I

**Piera** — 21, displaced, self-taught. Building security tools and low-level
systems in a room that isn't mine, on a computer that barely keeps up, in a
country that doesn't want me here.

PassForge is the first project I'm shipping publicly. It is not a portfolio
piece. It is the first layer of a longer arc: cryptographic stack → network
stack → virtual CPU → a security-first operating environment.

The name **Piera** is my signature. **Del Piera Armando** is the full name I
chose for myself — not the one I was given. It carries the work.

This repository is the beginning of that work. Nothing more. Nothing less.

## What This Is

A password generation framework that grew into a security toolkit. It
generates passwords, hashes them, estimates their strength, and tries to
crack them — all in one process, all in C++.

It's built to learn, not to compete with commercial tools. Every module is
hand-built. Every design decision is documented in the code.

**What it is NOT:**
- Not production-ready
- Not audited
- Not error-handled properly
- Not thread-safe
- Not cross-platform (Windows only for now)
- Not the final version of anything

## Features (v1.0)

**Generation**
- 12 character pools (ASCII, HexLower, HexUpper, Binary, Octal, Base32,
  Base64, Base64URL, Vowels, Consonants, All, Default)
- 4 policy presets (TooStrong, Strong, Medium, Simple)
- CSPRNG via Windows BCrypt (`BCryptGenRandom`)
- Policy validation with pool compatibility check
- Pool deduplication

**Hashing**
- SHA-256 via Windows BCrypt
- SHA-512 via Windows BCrypt
- MD5 implemented from scratch (RFC 1321), verified against test vectors

**Analysis**
- Entropy estimation (bits, based on pool size and password length)
- Crack time estimation with CPU rate table
- GPU detection via DXGI (prepared for v1.1 GPU acceleration)

**Brute Force**
- Mask parser (`?l`, `?u`, `?d`, `?s`, `?a` tokens + literals)
- Keyspace calculation with overflow protection
- CPU-based candidate loop (~200k H/s SHA-256, ~500k H/s MD5)
- Live countdown display (rate, ETA, progress)
- Cancel via Q key

**Facade**
- Interactive menu connecting all modules
- Save last generated password + all three hashes to file

## What's In Progress (Higher Versions)

These modules exist in the codebase but are not connected or not fully
implemented yet. They will ship in v1.1, v1.5, or v2.0.

**KeySec**
- 5-layer key derivation from a global password
- SHA-512 based vault key
- Anti-debug layers (IsDebuggerPresent, remote debugger check)
- Token-based one-time key display
- Not yet connected to the main flow — the vault integration is v2.0+.

**BRN (Behavior-based Runtime Neutralizer)**
- Watchdog thread that checksums critical code regions every 3 seconds
- On tamper detection: silently neutralizes the vault keys (no crash, no
  obvious signal to the attacker)
- Currently arms via `showOnce()` but the vault itself isn't wired yet.

**Vault**
- Designed, not built. Will hold hashed labels and hashed passwords in an
  unordered_map. Encrypted storage and retrieval are v2.0 work.

**OBF (Obfuscation Layer)**
- `apply()` — rotate + XOR pipeline with random constants
- `getThreeRand()` — random triple for the pipeline
- `xorMask()`, `rotl64InP()`, `combineInP()` — primitive obfuscation ops
- Used by KeySec's Layer 4/5. Further integration in v1.1.

**GPU Acceleration**
- DXGI query and GPU tier detection are in place
- OpenCL kernel for SHA-256/MD5 will ship in v1.1
- Expected 5-6x speedup on the RX 580 target

## Known Limitations (Honest List)

**Error handling is not properly implemented yet.**
- Some paths throw exceptions, some return nullopt, some just crash.
- A consistent error strategy is v1.1 work.
- If something fails silently, that's expected in v1.0.

**Testing is minimal.**
- No unit tests yet.
- No CI pipeline.
- No test vectors for all hash types.
- v1.1 will add a proper test suite.

**Concurrency is not safe.**
- Static state in several modules.
- No thread synchronization.
- Not documented as thread-safe.
- Use as single-threaded only.

**Reverse-engineering defenses are basic.**
- KeySec and BRN exist but aren't connected.
- Anti-debug is `IsDebuggerPresent` + one remote check. Easy to bypass.
- Obfuscation is simple rotate/XOR. Recognizable by any RE.
- These are learning implementations, not hardened.

**Performance is CPU-only.**
- ~200k H/s SHA-256, ~500k H/s MD5 on CPU.
- No GPU path yet.
- Large keyspaces take hours or days.

**Memory safety is not audited.**
- No ASan/UBSan runs yet.
- Secure memory wiping is minimal.

**Not cross-platform.**
- Windows-only. Depends on BCrypt, DXGI, `CreateProcess`.
- Linux port is far future.

**Vault is not functional.**
- KeySec generates keys but doesn't store anything.
- No encrypted storage, no retrieval, no master password flow.
- The vault exists as a design, not as a working tool.

## Build

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .

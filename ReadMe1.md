                    PASSWORD GENERATOR LIBRARY
═══════════════════════════════════════════════════════════════

                    +----------------------+
                    |        Pool          |
                    |----------------------|
                    | charsetsPool         |
                    | custom pools...      |
                    +----------+-----------+
                               │
                               │ std::string_view
                               ▼
                    +----------------------+
                    | CharacterAnalyzer    |
                    |----------------------|
                    | pool_               |
                    | AnalyzeResults      |
                    |----------------------|
                    | constructor(pool)   |
                    | setPool()           |
                    | analyze() (private) |
                    | reset()             |
                    | size()              |
                    | getIndices()        |
                    | charsetSize()       |
                    +----------+-----------+
                               │
                               │ Cached Information
                               ▼
                +--------------------------------+
                |      AnalyzeResults            |
                |--------------------------------|
                | lowerIndices_                  |
                | upperIndices_                  |
                | digitIndices_                  |
                | symbolIndices_                 |
                +--------------------------------+

═══════════════════════════════════════════════════════════════

                  RANDOM GENERATION LAYER

                    +----------------------+
                    | Random Engine        |
                    |----------------------|
                    | mt19937              |
                    | random_device seed   |
                    | uniform_distribution |
                    +----------+-----------+
                               │
                               ▼
                    +----------------------+
                    | Algorithms           |
                    |----------------------|
                    | mixPasscode()        |
                    | morphicCascadePro()  |
                    | future: Botan        |
                    | future: OpenSSL      |
                    +----------+-----------+

═══════════════════════════════════════════════════════════════

                     PHASE 2

                +--------------------------+
                | PasswordPolicy           |
                |--------------------------|
                | minLength                |
                | maxLength                |
                | requireLower             |
                | requireUpper             |
                | requireDigit             |
                | requireSymbol            |
                | excludeAmbiguous         |
                | custom charset           |
                +-----------+--------------+
                            │
                            ▼
                +--------------------------+
                | CustomGenerator          |
                |--------------------------|
                | uses CharacterAnalyzer   |
                | validates policy         |
                | chooses random indices   |
                | builds password          |
                +-----------+--------------+
                            │
                            ▼
                    Final Password

═══════════════════════════════════════════════════════════════

                     FUTURE PHASES

Phase 3
├── Password Strength Estimator
├── Entropy Calculator
├── Pattern Detector

Phase 4
├── Secure Password Storage
├── Botan Hashing
├── Argon2
├── bcrypt
├── PBKDF2

Phase 5
├── Configuration System
├── JSON
├── Profiles
├── Export / Import

Phase 6
├── GUI (Win32)
├── Clipboard
├── Password History
├── Theme
├── Generator Presets

Phase 7
├── Unit Tests
├── Benchmarks
├── Documentation
├── Packaging
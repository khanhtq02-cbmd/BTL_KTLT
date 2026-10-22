# Mobile Subscriber Management System

C++11 command-line application for managing mobile subscribers, plans, contracts, devices, top-ups, CDR records, invoices, and complaints.

This course project simulates telecom workflows with local text files. It does not connect to a carrier network, EIR, payment provider, SMS gateway, or real radio infrastructure.

## Features

- Customer records with CCCD and phone validation
- Prepaid and postpaid subscriber management
- Mobile plan management
- Contract creation, search, update, renewal, suspension, and termination
- IMEI validation with the 3GPP Luhn checksum
- Simulated IMEI generation for demo data
- Device/SIM assignment and offline BTS registry lookup
- Top-up and CDR records for voice, SMS, and data
- Invoice and complaint management
- Repository-based CRUD with text-file persistence
- Staged file writes with rollback on persistence failure
- Vietnamese console menus

## Requirements

### Linux

Required tools:

- GCC/G++ or Clang with C++11 support
- GNU Make
- CMake 3.10 or newer
- Git, if cloning the repository

On Debian/Ubuntu:

```bash
sudo apt update
sudo apt install -y build-essential cmake git
```

On Fedora:

```bash
sudo dnf install -y gcc-c++ make cmake git
```

Verify the installation:

```bash
g++ --version
make --version
cmake --version
git --version
```

### Windows

Choose one supported setup:

1. **MinGW-w64 or MSYS2 MinGW-w64** — provides `g++`, `make`, and optionally CMake. Add the compiler's `bin` directory to `PATH` if using a regular Command Prompt or PowerShell.
2. **Visual Studio 2019/2022** — install the **Desktop development with C++** workload and the CMake tools component.
3. **Git for Windows** — recommended for cloning and for the Git Bash commands below.

The included `run_windows.bat` is the simplest MinGW path. It requires `g++` on `PATH`, compiles with C++11 and warnings enabled, then starts `quanlythuebao.exe`.

Check a MinGW/MSYS2 installation in Command Prompt or Git Bash:

```bat
g++ --version
cmake --version
git --version
```

## Get the source

Using Git:

```bash
git clone <repository-url>
cd KTLT
```

If the project was supplied as a ZIP archive, extract it and open a terminal in the extracted `KTLT` directory. Keep the `data/` directory beside the source tree; the application needs its text fixtures at startup.

## Build and run on Linux

### Option A: GNU Make

Run these commands from the repository root:

```bash
make clean
make all
./quanlythuebao
```

For the normal build-and-run shortcut:

```bash
make run
```

### Option B: CMake

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
./build/quanlythuebao
```

The program can also be launched from another working directory because it resolves `data/` relative to the executable, provided the complete data directory is present.

## Build and run on Windows

### Option A: MinGW/MSYS2 batch script

1. Open Command Prompt or Git Bash.
2. Change to the repository root.
3. Confirm `g++` is available.
4. Run the script:

```bat
run_windows.bat
```

The script creates `quanlythuebao.exe` in the repository root and starts it. Run it from the project root so the relative `data/` directory is available.

To build and run manually from Git Bash with MinGW:

```bash
g++ -std=c++11 -Wall -Wextra -Isrc -Isrc/lib -Isrc/lib/shared -Isrc/lib/models -Isrc/lib/menus \
  src/main.cpp src/lib/shared/*.cpp src/lib/models/*.cpp src/lib/menus/*.cpp \
  -o quanlythuebao.exe
./quanlythuebao.exe
```

### Option B: Visual Studio or CMake GUI

From a **Developer PowerShell for VS** or a terminal where CMake is available:

```powershell
cmake -S . -B build
cmake --build build --config Debug --parallel
.\build\Debug\quanlythuebao.exe
```

Alternatively, open the repository folder in Visual Studio, select the CMake target `quanlythuebao`, choose the `Debug` configuration, and run it. Keep the repository's `data/` directory available beside the source tree.

## Build with CMake on either platform

The CMake targets are:

- `quanlythuebao` — interactive application
- `test_runner` — direct assertion suite
- `stress_test_runner` — sanitizer stress runner

Linux:

```bash
cmake -S . -B build
cmake --build build --parallel
```

Windows with a multi-configuration generator:

```powershell
cmake -S . -B build
cmake --build build --config Debug --parallel
```

Useful targets:

```bash
make run       # build and run the application
make test      # build and run the direct assertion test runner
make stress    # build and run the 300-second ASan/UBSan stress test
make clean     # remove generated binaries and coverage files
```

## Run tests

### CTest

```bash
cmake -S . -B build
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

The CTest suite contains:

1. Direct unit/model/menu tests
2. A five-second stress test
3. Startup from a different working directory

### Direct assertion runner

```bash
./build/test_runner
```

### Strict C++11 build

```bash
cmake -S . -B build-strict \
  -DCMAKE_CXX_FLAGS='-std=c++11 -pedantic-errors -Wall -Wextra'
cmake --build build-strict --parallel
```

## Data files and startup behavior

The application uses local pipe-delimited text files in `data/`:

```text
data/CacGoiCuoc.txt
data/khachhang.txt
data/thuebao.txt
data/hopdong.txt
data/imei.txt
data/naptien.txt
data/ghicuocgoi.txt
data/hoadon.txt
data/khieunai.txt
```

`data/bts_vietnam.txt` and `data/bts_vietnam.csv` provide the offline BTS registry dataset.

The application requires the nine primary data files at startup. If the data directory is incomplete, it prints an error and exits with status `1`; it does not fabricate a successful empty startup.

Do not put real personal data into the repository. The checked-in examples are course/demo data.

## Project layout

```text
.
├── CMakeLists.txt
├── Makefile
├── data/                       # Local text fixtures and BTS datasets
├── src/
│   ├── main.cpp                # Application entry point and main menu
│   └── lib/
│       ├── shared/             # Entity, Repository, FileIO, validation, UI helpers
│       ├── models/             # Domain models
│       └── menus/              # Console workflow controllers
├── tests/
│   ├── test_runner.cpp         # Direct assertion suite
│   ├── stress_test_runner.cpp  # ASan/UBSan stress suite
│   └── repro/                  # Focused regression reproducers
└── docs/                       # Design, operational, user, and report documentation
```

The main production path is:

```text
main.cpp → menu controller → model and validation → Repository<T>/FileIO → data/*.txt
```

There are no separate `services/` or per-entity `repositories/` directories. `Repository<T>` is the shared generic storage component.

## Persistence behavior

`Repository<T>` provides:

- `loadFromFile()` and `saveToFile()`
- add, update, remove, find, filter, sort, and clear operations
- duplicate-ID rejection
- malformed-record skipping during deserialization
- rollback of in-memory mutation if saving fails

Writes are staged through the temporary area and committed by `FileIO`. On Linux, the project uses `/dev/shm` when available for temporary staging.

## Scope boundaries

The current project does not provide:

- Carrier-network or EIR integration
- Real payment processing or SMS delivery
- Enterprise authentication or role-based access control
- Multi-user transactional locking
- A complete CDR-to-invoice billing engine
- A complete global orphan-record scanner
- A complete guard preventing deletion of every referenced plan
- A dedicated statistics dashboard

These are possible future extensions, not runtime dependencies.

## Verification

Run these commands on the current checkout:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/test_runner
```

For repository-integrity checks, inspect the working tree before committing:

```bash
git status --short
git diff --check
```

## Further documentation

- `docs/UserGuide/USER_MANUAL.md`
- `docs/Overview/ARCHITECTURE_AND_REQUIREMENTS.md`
- `docs/Overview/lib.md`
- `docs/Operational/TECHNICAL_DESIGN_SPECIFICATION.md`
- `docs/Operational/FUNCTION_CALLFLOW_SPEC.md`
- `docs/Operational/USE_CASE_SPEC_DUCANH.md`
- `docs/Reports/IMEI_AND_SHARED_LIBRARIES_REPORT.md`
- `members/*/README.md`

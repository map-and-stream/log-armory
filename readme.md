<!-- Badges -->
<p align="left">
  <a href="https://github.com/map-and-stream/log-armory/actions">
    <img src="https://img.shields.io/github/actions/workflow/status/map-and-stream/log-armory/ci.yml?branch=main&label=CI&logo=github&style=flat-square" alt="CI Status">
  </a>
  <a href="https://github.com/map-and-stream/log-armory/blob/main/LICENSE">
    <img src="https://img.shields.io/badge/license-MIT-blue.svg?style=flat-square" alt="license: MIT" />
  </a>
  <a href="https://github.com/map-and-stream/log-armory/releases">
    <img src="https://img.shields.io/github/v/release/map-and-stream/log-armory?style=flat-square" alt="release" />
  </a>
  <img src="https://img.shields.io/badge/build-passing-brightgreen.svg?style=flat-square" alt="build" />
  <img src="https://img.shields.io/badge/platform-linux--64%20%7C%20windows--64-lightgrey?style=flat-square" alt="platform">
  <a href="https://github.com/map-and-stream/log-armory/commits/main">
    <img src="https://img.shields.io/github/last-commit/map-and-stream/log-armory?style=flat-square" alt="last commit" />
  </a>
  <a href="https://github.com/map-and-stream/log-armory/issues">
    <img src="https://img.shields.io/github/issues/map-and-stream/log-armory?style=flat-square" alt="open issues" />
  </a>
  <a href="https://github.com/map-and-stream/log-armory/discussions">
    <img src="https://img.shields.io/github/discussions/map-and-stream/log-armory?style=flat-square" alt="GitHub Discussions" />
  </a>
</p>

# Async Logging Example (with log-armory)

A C++ project demonstrating how to use the built-in asynchronous logging capabilities of [`loga-armory`](https://github.com/map-and-stream/log-armory).  
This README documents requirements, build process, setup, usage, contributing, license, and contact information.

---

## 🛠 Build Requirements

- **C++14** or newer compatible compiler (tested on GCC ≥ 9, Clang ≥ 10, MSVC 2019)
- **CMake** (≥ 3.15) for build configuration
- **make** or **ninja** build system (on Linux/macOS)
- **Git** for cloning and managing submodules
- **spdlog** (included as a submodule)
- Optionally: `g++`/`clang++`, Windows users: Visual Studio

> **Note:** All required dependencies, including spdlog, are managed by submodules.

---

## 🚀 Setup & Build

### 1. **Clone repository and initialize submodules**

```sh
git clone <your-repo-url>
cd <your-project-dir>
git submodule add https://github.com/map-and-stream/log-armory.git
git submodule update --init --recursive
```

### 2. **Configure and Build**

#### **Using Make (default)**
```sh
make build
```
- Compiles sources, tests, and examples, then copies executables and libraries to the `output` directory.

#### **Using CMake directly**
```sh
cmake -S . -B build
cmake --build build
```
- The output binaries will be available in the `output/` directory after building.

#### **Windows (MSVC)**
- Open a Developer Command Prompt and run:
    ```sh
    cmake -S . -B build -G "Visual Studio 16 2019"
    cmake --build build --config Release
    ```
- Outputs found in `output\`

---

## 📦 Usage

`log-armory` supports asynchronous logging via a built-in **async logger** system based on a lock-free queue.

### 1. **Enabling Asynchronous Logging**
Create an async logger:
```cpp
#include "log-armory/src/factory.h"

int main() {
    LogConfig cfg;
    cfg.general_config.fileName = "logs/app.log";
    cfg.rotate_config.max_count = 200;
    cfg.rotate_config.max_size = 1024;
    cfg.general_config.logLevel = LogLevel::info;
    cfg.workering_mode.mode = WorkingMode::SYNC;
    cfg.rotate_config.type = SinkType::Daily;

    ILogger* s = LoggerFactory::createLogger(LoggerType::Spdlog, cfg);
    s->info("Hello from async logger!");
}
```

### 2. **Using rotating Logger**
All loggers become async:
```cpp
#include "log-armory/src/factory.h"

int main() {
    LogConfig cfg;
    cfg.general_config.fileName = "logs/app.log";
    cfg.rotate_config.max_count = 200;
    cfg.rotate_config.max_size = 1024;
    cfg.general_config.logLevel = LogLevel::info;
    cfg.workering_mode.mode = WorkingMode::SYNC;
    cfg.rotate_config.type = SinkType::Hourly;

    ILogger* s = LoggerFactory::createLogger(LoggerType::Spdlog, cfg);

    s->info("This is an info message.");
    s->warn("This is a warning message.");
    s->error("This is an error message.");
}
```

### 3. **Async Modes: Blocking vs Non-Blocking**
- *Blocking (default):* Producer threads wait if the queue is full.
    ```cpp
    spdlog::init_thread_pool(8192, 1);
    auto logger = spdlog::create_async<...>();
    ```
- *Non-blocking (drops logs if full):*
    ```cpp
    auto logger = spdlog::create_async_nb<...>("name", ...);
    ```

### 4. **Change Queue Size & Thread Count**
```cpp
spdlog::init_thread_pool(queue_size, num_threads);
// Example
spdlog::init_thread_pool(32768, 2);
```

### 5. **Flushing**
- Manually:
    ```cpp
    logger->flush();
    ```
- Periodically every second:
    ```cpp
    spdlog::flush_every(std::chrono::seconds(1));
    ```

#### ℹ️ *Tip: If you see “async logger not initialized”*
Call `spdlog::init_thread_pool(...)` *before* creating async loggers!

---

## 🤝 Contribution

Contributions, issues, and feature requests are welcome!
- Fork the repo
- Create your feature branch (`git checkout -b feature/fooBar`)
- Commit your changes
- Push to the branch (`git push origin feature/fooBar`)
- Open a pull request

---

## 📣 Community & Q&A

Got a question, idea, or want to share your use case?  
Check out our [GitHub Discussions](https://github.com/map-and-stream/log-armory/discussions) for Q&A, tips, feature requests, and community support!

- For bugs and actionable issues, please [open an Issue](https://github.com/map-and-stream/log-armory/issues).

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

## 📬 Contact

For questions, support, or more examples (incl. integrating with Qt or performance notes):

- Author: [map and stream company]
- Email: [map-and-stream@example.com]
- [Open an Issue](https://github.com/map-and-stream/log-armory/issues)
- [Ask or discuss on GitHub Discussions](https://github.com/map-and-stream/log-armory/discussions)

---

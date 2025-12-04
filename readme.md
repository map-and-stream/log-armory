1- for compile only command 'make build' is needed
    this command compile source,test and exmaples
    finally copy executable files and library to output dir.
    git submodule add https://github.com/gabime/spdlog.git third-party/spdlog
    git submodule update --init --recursive
    
    `spdlog` supports asynchronous logging via a built-in **async logger** system based on a lock-free queue.
Here’s a concise guide on how to use it.

---

# ✅ **1. Enabling Asynchronous Logging**

You create an async logger using:

### **Option A — `spdlog::async_logger` via factory**

```cpp
#include <spdlog/spdlog.h>
#include <spdlog/async.h>              // support for async logging
#include <spdlog/sinks/basic_file_sink.h>

int main() {
    spdlog::init_thread_pool(8192, 1);  // queue size, number of threads

    auto logger = spdlog::create_async<spdlog::sinks::basic_file_sink_mt>(
        "async_file_logger", "logs/async.txt");

    logger->info("Hello from async logger!");
}
```

---

# ✅ **2. Using the Global Default Async Logger**

If you want **all** loggers to be async:

```cpp
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main() {
    spdlog::init_thread_pool(8192, 1);

    auto console = spdlog::stdout_color_mt("console");

    spdlog::set_default_logger(
        spdlog::create_async_nb<spdlog::sinks::stdout_color_sink_mt>(
            "async_console"));

    spdlog::info("Async log message!");
}
```

---

# ✅ **3. Async Modes: Blocking vs Non-Blocking**

### **Blocking (default)**

If queue is full, producer threads will wait.

```cpp
spdlog::init_thread_pool(8192, 1);
auto logger = spdlog::create_async<...>();
```

### **Non-blocking (drop logs when full)**

Use `_nb` version:

```cpp
auto logger = spdlog::create_async_nb<...>("name", ...);
```

---

# ✅ **4. Changing Queue Size & Thread Count**

```cpp
spdlog::init_thread_pool(queue_size, num_threads);
```

Example:

```cpp
spdlog::init_thread_pool(32768, 2);
```

---

# ✅ **5. Flushing**

Async loggers flush asynchronously too. To manually flush:

```cpp
logger->flush();
```

Flush every second automatically:

```cpp
spdlog::flush_every(std::chrono::seconds(1));
```

---

# 🔍 Tip: If you see “async logger not initialized”

You forgot to call:

```cpp
spdlog::init_thread_pool(...)
```

before creating async loggers.

---

If you want, I can give you a minimal working example, show how to integrate async logging into Qt, or explain performance characteristics.



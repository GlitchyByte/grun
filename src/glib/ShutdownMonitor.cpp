// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "glib/ShutdownMonitor.h"
#ifdef GLIB_SHUTDOWN_MONITOR

#include <csignal>

namespace glib {

    constinit bool _false { false };
    std::atomic<bool> generalShutdownInitiated { false };
    std::mutex generalShutdownLock;
    std::vector<std::shared_ptr<ShutdownMonitor>> shutdownMonitors;

    void triggerShutdown([[maybe_unused]] const int signal) noexcept {
        if (!generalShutdownInitiated.compare_exchange_strong(_false, true)) {
            return;
        }
        std::lock_guard<std::mutex> lock { generalShutdownLock };
        for (const auto& monitor: shutdownMonitors) {
            monitor->shutdown();
        }
        shutdownMonitors.clear();
    }

    std::shared_ptr<ShutdownMonitor> ShutdownMonitor::create() noexcept {
        static bool initialized { false };
        if (!initialized) {
            std::signal(SIGINT, triggerShutdown);
            std::signal(SIGTERM, triggerShutdown);
            initialized = true;
        }
        std::lock_guard<std::mutex> lock { generalShutdownLock };
        const bool isShuttingDown { generalShutdownInitiated };
        const std::shared_ptr<ShutdownMonitor> monitor { new ShutdownMonitor(isShuttingDown) };
        if (!isShuttingDown) {
            shutdownMonitors.push_back(monitor);
        }
        return monitor;
    }

    bool ShutdownMonitor::shouldShutdown() const noexcept {
        return isShuttingDown;
    }

    void ShutdownMonitor::shutdown() noexcept {
        isShuttingDown = true;
        std::lock_guard<std::mutex> lock { shutdownLock };
        shuttingDown.notify_all();
    }

    void ShutdownMonitor::awaitShutdown(const std::chrono::milliseconds& timeout) noexcept {
        if (shouldShutdown()) {
            return;
        }
        std::unique_lock<std::mutex> lock { shutdownLock };
        std::chrono::time_point<std::chrono::steady_clock> limit { std::chrono::steady_clock::now() + timeout };
        shuttingDown.wait_until(lock, limit, [&] { return isShuttingDown.load(); });
    }

    void ShutdownMonitor::awaitShutdown() noexcept {
        if (shouldShutdown()) {
            return;
        }
        std::unique_lock<std::mutex> lock { shutdownLock };
        shuttingDown.wait(lock, [&] { return isShuttingDown.load(); });
    }

    void ShutdownMonitor::whileLive(const std::chrono::milliseconds& cadence, const std::function<void()>& action) {
        while (!shouldShutdown()) {
            action();
            awaitShutdown(cadence);
        }
    }
}

#endif // GLIB_SHUTDOWN_MONITOR

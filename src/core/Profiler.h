#pragma once

#include "Core.h"

namespace core {
namespace profiler {
enum class ProfileZone : uint16_t {
    Frame = 0,
    EngineLoop,
    InputUpdate,
    WindowPoll,
    SystemsUpdate,
    RenderFrame,
    RenderClear,
    RenderSubmit,

    // Add new engine layers here as you build them
    Count
};

// Helper array to turn enums into readable strings *only* when printing/saving data
inline const char *ZoneToString(ProfileZone zone) {
    static const char *strings[] = {"Total Frame",  "Engine Loop",    "Input Update",
                                    "Window Poll",  "Systems Update", "Render Frame",
                                    "Render Clear", "Render Submit"};
    return strings[static_cast<size_t>(zone)];
}

using chrono_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

struct ProfileSample {
    ProfileZone zone;
    float durationMs;
    uint8_t depth;
};

class CORE_API Profiler {
  public:
    static Profiler &Get() {
        static Profiler instance;
        return instance;
    }

    void BeginFrame() {
        m_Samples.clear();
        m_CurrentDepth = 0;
        m_FrameStart = std::chrono::high_resolution_clock::now();
    }

    void EndFrame() {
        auto frameEnd = std::chrono::high_resolution_clock::now();
        m_TotalFrameTimeMs =
            std::chrono::duration<float, std::milli>(frameEnd - m_FrameStart).count();
    }

    void PushTimer(ProfileZone zone) {
        if (m_TimerStackIndex >= MAX_TIMERS)
            return; // Prevent stack overflow

        auto &timer = m_TimerStack[m_TimerStackIndex++];
        timer.zone = zone;
        timer.depth = m_CurrentDepth++;
        timer.start = std::chrono::high_resolution_clock::now();
    }

    void PopTimer() {
        if (m_TimerStackIndex == 0)
            return;

        auto now = std::chrono::high_resolution_clock::now();
        m_TimerStackIndex--;
        m_CurrentDepth--;

        const auto &top = m_TimerStack[m_TimerStackIndex];
        float elapsed = std::chrono::duration<float, std::milli>(now - top.start).count();

        m_Samples.push_back({top.zone, elapsed, top.depth});
    }

    const std::vector<ProfileSample> &GetSamples() const {
        return m_Samples;
    }
    float GetTotalFrameTime() const {
        return m_TotalFrameTimeMs;
    }

  private:
    Profiler() {
        m_Samples.reserve(256); // Pre-allocate to prevent mid-frame vector reallocations
    }

    struct TimerData {
        ProfileZone zone;
        uint8_t depth;
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
    };

    static constexpr size_t MAX_TIMERS = 64;
    TimerData m_TimerStack[MAX_TIMERS]; // Fixed-size stack array (Zero allocations!)
    size_t m_TimerStackIndex = 0;

    std::vector<ProfileSample> m_Samples;
    uint8_t m_CurrentDepth = 0;
    float m_TotalFrameTimeMs = 0.0f;

    chrono_t m_FrameStart;
};

class ScopedProfileTimer {
  public:
    ScopedProfileTimer(ProfileZone zone) {
        Profiler::Get().PushTimer(zone);
    }
    ~ScopedProfileTimer() {
        Profiler::Get().PopTimer();
    }
};

// Global instrumentation macros
#define WT_PROFILE_FRAME_BEGIN() Profiler::Get().BeginFrame()
#define WT_PROFILE_FRAME_END()   Profiler::Get().EndFrame()
#define WT_PROFILE_SCOPE(zone)   ScopedProfileTimer timer__##__LINE__(zone)

} // namespace profiler
} // namespace core

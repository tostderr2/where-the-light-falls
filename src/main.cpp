#include <glad/glad.h>

#include "core/Log.h"
#include "core/Profiler.h"

// Simulating the input subsystem layer
void UpdateInput() {
    WT_PROFILE_SCOPE(ProfileZone::InputUpdate);
    std::this_thread::sleep_for(std::chrono::milliseconds(2)); // Simulate work
}

// Simulating engine game systems layer
void UpdateSystems() {
    WT_PROFILE_SCOPE(ProfileZone::SystemsUpdate);
    std::this_thread::sleep_for(std::chrono::milliseconds(4)); // Simulate work
}

// Simulating the graphics pipeline layer
void RenderFrame() {
    WT_PROFILE_SCOPE(ProfileZone::RenderFrame);
    {
        WT_PROFILE_SCOPE(ProfileZone::RenderClear);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    {
        WT_PROFILE_SCOPE(ProfileZone::RenderSubmit);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
// simulation end

int main(/*int argc, char* argv[]*/) {

    core::Log::Init();

    LOG_GAME_CRITICAL("game crit!!");
    LOG_GAME_ERR("game err!!");
    LOG_GAME_WARN("game warn!!");
    LOG_GAME_INFO("game info!!");
    LOG_GAME_DEBUG("game debug!!");
    LOG_GAME_TRACE("game trace!!");

    LOG_CORE_CRITICAL("core crit!!");
    LOG_CORE_ERR("core err!!");
    LOG_CORE_WARN("core warn!!");
    LOG_CORE_INFO("core info!!");
    LOG_CORE_DEBUG("core debug!!");
    LOG_CORE_TRACE("core trace!!");
    // spdlog::log(spdlog::level::level_enum::info, "Welcome to the greatest game ever created\n");

    return 0;
}


/*
* info: profiling tests

    // Engine Loop simulation (running for 300 frames)
    for (int frame = 0; frame < 300; ++frame) {
        WT_PROFILE_FRAME_BEGIN();
        {
            WT_PROFILE_SCOPE(ProfileZone::EngineLoop);

            UpdateInput();
            UpdateSystems();
            RenderFrame();
        }
        WT_PROFILE_FRAME_END();

        // Print performance readout for the frame
        std::cout << "\n=== FRAME " << frame << " (" << Profiler::Get().GetTotalFrameTime()
                  << " ms) ===\n";

        // Render step translates fast enums back to readable string strings
        for (const auto &sample : Profiler::Get().GetSamples()) {
            std::string indent(sample.depth * 2, ' ');
            std::cout << indent << "- " << ZoneToString(sample.zone) << ": " << sample.durationMs
                      << " ms\n";
        }
    }

*
*/

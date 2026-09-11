
#include "core/Application.h"
#include "core/Log.h"

int main(/*int argc, char* argv[]*/) {

    core::Log::Init();

    core::Application app = core::Application();
    app.Run();

    return 0;
}

/*
* info: profiling tests

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

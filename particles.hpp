#include "imgui.h" // set to wherever you have this file for example "../Utils/ImGui/ImGui.h"
#include <vector>
#include <random>

class M_Particle_System {
public:
    enum class prt_type { 
        snow, 
        rain, 
        ash 
    };

    void render(prt_type type);

private:
    struct Particle {
        float x = 0.0f, y = 0.0f;
        float fallSpeed = 0.0f, driftSpeed = 0.0f;
        uint8_t alpha = 0;
        int width = 0, height = 0;
    };

    std::vector<Particle> prts;

    Particle generate(prt_type type, bool firstTime = false);
    inline static int rand_int(int min, int max);
};

int M_Particle_System::rand_int(int min, int max) {
    static std::mt19937 gen(std::random_device{}());
    return std::uniform_int_distribution<>(min, max)(gen);
}
M_Particle_System::Particle M_Particle_System::generate(prt_type type, bool firstTime) {
    Particle p;
    auto io = ImGui::GetIO();
    p.x = static_cast<float>(rand_int(-static_cast<int>(io.DisplaySize.x / 2), static_cast<int>(io.DisplaySize.x)));
    p.y = static_cast<float>(rand_int(firstTime ? -static_cast<int>(io.DisplaySize.y * 2) : -100, -50));

    switch (type) {
    case prt_type::snow:
        p.fallSpeed = rand_int(100, 200) / 100.0f;
        p.driftSpeed = rand_int(10, 70) / 100.0f;
        p.alpha = static_cast<uint8_t>(rand_int(5, 255));
        p.width = p.height = rand_int(1, 2);
        break;
    case prt_type::rain:
        p.fallSpeed = rand_int(300, 600) / 100.0f;
        p.driftSpeed = rand_int(1, 10) / 100.0f;
        p.alpha = static_cast<uint8_t>(rand_int(100, 200));
        p.width = 1;
        p.height = rand_int(5, 10);
        break;
    case prt_type::ash:
        p.fallSpeed = rand_int(50, 100) / 100.0f;
        p.driftSpeed = rand_int(30, 100) / 100.0f;
        p.alpha = static_cast<uint8_t>(rand_int(50, 150));
        p.width = rand_int(2, 3);
        p.height = rand_int(4, 8);
        break;
    }
    return p;
}

void M_Particle_System::render(prt_type type) {
    float deltaTime = ImGui::GetIO().DeltaTime;
    if (prts.empty()) {
        prts.reserve(1400);
        for (int i = 0; i < 1400; ++i) {
            prts.push_back(generate(type, true));
        }
    }

    for (auto& p : prts) {
        if (p.y > ImGui::GetIO().DisplaySize.y + 50) {
            p = generate(type);
            continue;
        }
        p.x += p.driftSpeed * deltaTime * 100.0f;
        p.y += p.fallSpeed * deltaTime * 100.0f;

        ImU32 color;
        switch (type) {
        case prt_type::snow:
            color = ImColor(230, 230, 230, p.alpha);
            break;
        case prt_type::rain:
            color = ImColor(173, 216, 230, p.alpha);
            break;
        case prt_type::ash:
            color = ImColor(105, 105, 105, p.alpha);
            break;
        }

        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + p.width, p.y + p.height), color);
    }
}

namespace M { inline M_Particle_System Particle; }

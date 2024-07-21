# particle-system

ImGui particle system based on Lak3's snow system from [SE-Owned](https://www.unknowncheats.me/forum/team-fortress-2-a/436430-seowned-featured-cheat.html) 






## Particles
- [x] Snow.
- [x] Rain.
- [x] Ash.
- [ ] Leaves.
- [ ] Fireflys.
- [ ] Shooting Stars.
> Will add more at some point.


## Usage
1. First you need to Include the particles.hpp
```cpp
#include "Particles.h"
```

2. Call the Function
```cpp
// call this right before your imgui::begin function 
M::Particle.render(M_Particle_System::prt_type::snow); // options { snow, rain, ash }
```

### Example Program

```cpp
bool menu_particle = true;

if (menu_particle)
     M::Particle.render(M_Particle_System::prt_type::snow);

ImGui::SetNextWindowSize(ImVec2(500, 500));
ImGui::Begin("Example", nullptr, ImGuiWindowFlags_NoSavedSettings); {
    ImGui::Checkbox("Particles", &menu_particle);
}ImGui::End();
```

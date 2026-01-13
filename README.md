# AIEngine2D

A lightweight, SNES-inspired 2D pixel-perfect game engine built with modern C++17.

## Features

- **ECS Architecture** - Entity-Component-System design for optimal performance
- **Custom 2D Physics** - AABB/Circle collisions, rigidbodies, raycasting
- **Custom Audio** - WAV playback, multi-channel mixer, spatial audio
- **Pixel-Perfect Rendering** - OpenGL 3.3+ with sprite batching and dynamic resolution
- **In-Engine Level Editor** - ImGui-based editor with tilemap support
- **Zero External Dependencies** - Only SDL2, OpenGL, and ImGui

## Requirements

- **C++17** compatible compiler (MSVC 2019+, GCC 9+, Clang 10+)
- **CMake** 3.16+
- **SDL2** 2.0.12+
- **OpenGL** 3.3+

## Installation

### Windows

```bash
# Clone the repository
git clone https://github.com/SebastienFeser/AIEngine2D.git
cd AIEngine2D

# Install dependencies via vcpkg (recommended)
vcpkg install sdl2 imgui[sdl2-binding,opengl3-binding]

# Build
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

### Linux

```bash
# Install dependencies
sudo apt install libsdl2-dev cmake build-essential

# Clone and build
git clone https://github.com/SebastienFeser/AIEngine2D.git
cd AIEngine2D
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### macOS

```bash
# Install dependencies
brew install sdl2 cmake

# Clone and build
git clone https://github.com/SebastienFeser/AIEngine2D.git
cd AIEngine2D
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
```

## Quick Start

```cpp
#include "core/engine.h"

int main() {
    engine::Engine game(800, 600, "My Game");

    // Create entity with components
    auto player = game.createEntity();
    game.addComponent<PositionComponent>(player, 100.0f, 100.0f);
    game.addComponent<SpriteComponent>(player, "player.png");

    return game.run();
}
```

## Project Structure

```
AIEngine2D/
├── src/
│   ├── core/       # ECS, engine loop, events
│   ├── renderer/   # OpenGL, shaders, batching
│   ├── physics/    # Collisions, rigidbodies
│   ├── audio/      # WAV loader, mixer
│   ├── input/      # SDL2 input handling
│   ├── assets/     # Asset management
│   └── editor/     # ImGui level editor
├── assets/         # Game assets (sprites, audio, levels)
├── docs/           # Documentation and wiki
└── examples/       # Example games
```

## Documentation

- [Wiki](docs/wiki/) - User guides and tutorials *(coming soon)*
- [API Reference](docs/api/) - Full API documentation *(coming soon)*

## License

MIT License - See [LICENSE](LICENSE) for details.

## Status

**In Development** - Phase 0

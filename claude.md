# 🎮 SNES-Like 2D Pixel Perfect Game Engine
## ECS-Based, Ultra-Optimized, WebGL-Compatible
### Multi-Agent Architecture + Auto-Documentation

---

## 📌 PROJECT INFO

| Info | Value |
|------|-------|
| **Repo** | https://github.com/SebastienFeser/AIEngine2D.git |
| **Branch** | master |
| **Platform** | Windows (win32) |

## ⏳ TEMPORARY TODOs (Delete once done)

- [ ] **Update README.md** once project is installed and functional (verify install instructions, quick start, etc.)

---

## 🔄 CLAUDE.MD MAINTENANCE (CRITICAL)

**Each session, Claude MUST:**
1. Identify important info discovered (decisions, configs, solved issues)
2. Update this file with that info
3. **Keep file OPTIMIZED** - no redundancy, no noise
4. **Delete `tmpclaude-*` files** at root if they exist (Claude Code temp files)

**Rules:**
- Add only **actionable and reusable** info
- Remove obsolete info
- Prefer tables and lists over paragraphs
- Max ~600 lines for this file
- **ALL files must be in English** (code, comments, docs, commits)

---

## 📋 PROJECT PHILOSOPHY

| Aspect | Detail |
|--------|--------|
| **Core** | 2D SNES-like engine with ECS, custom 2D physics, custom audio, in-engine level editor |
| **Approach** | 100% Claude code-gen, you validate/compile |
| **Tokens** | MAX 10k tokens/request → fragmentation + sub-agents mandatory |
| **Languages** | C++17 (core), GLSL 3.3 (shaders), HTML/CSS/JS (auto docs) |
| **Dependencies** | SDL2 (window), OpenGL 3.3+ (render), ImGui (editor UI) |
| **No** | FMOD, Box2D, Lua, external physics → **all custom** |
| **Architecture** | Dense ECS (SoA), async render pipeline, modular systems |
| **Targets** | Desktop (SDL2+GL 3.3), WebGL (Emscripten future), extensible |

---

## 🏗️ SYSTEM ARCHITECTURE

### Design Layers (Bottom-Up)

```
┌──────────────────────────────────────────────────────────┐
│  GAMEPLAY                                                │
│  Entity behaviors, systems, scripting (100% C++)         │
├──────────────────────────────────────────────────────────┤
│  EDITOR (ImGui)                                          │
│  Level editor, property inspector, play/edit toggle      │
├──────────────────────────────────────────────────────────┤
│  ECS CORE                                                │
│  Entities, Components, Systems, Events, Hierarchy       │
├──────────────────────────────────────────────────────────┤
│  SUBSYSTEMS                                              │
│  Physics 2D │ Audio │ Input │ Asset Manager │ Timing    │
├──────────────────────────────────────────────────────────┤
│  RENDERER                                                │
│  OpenGL 3.3+ │ Shaders │ Batching │ Pixelization       │
├──────────────────────────────────────────────────────────┤
│  PLATFORM                                                │
│  SDL2 │ OpenGL Extensions │ File I/O                     │
└──────────────────────────────────────────────────────────┘
```

### 8 Specialized Agents

```
Agent-CORE      → ECS manager, entity lifecycle, events, transform hierarchy
Agent-RENDERER  → OpenGL pipeline, sprite batching, shaders, FX, pixelization
Agent-PHYSICS   → 2D collisions (AABB, circles), rigidbodies, constraints
Agent-AUDIO     → WAV loader, audio mixer, streaming, effects (custom impl)
Agent-INPUT     → SDL2 input polling, input mapping, event buffering
Agent-ASSETS    → Image loading, texture pooling, sprite sheets, pixelization
Agent-EDITOR    → ImGui UI, level editor, property panel, prefab system
Agent-TOOLS     → Build helpers, asset converters, shaders, validation
Agent-DOCS      → Blog posts (MD→HTML), API docs, tutorials, examples
```

Each agent has its own **`claude.md`** (specialized directives).

---

## 🔑 CORE PATTERNS & CONVENTIONS

### Naming

```cpp
// Classes/Types: PascalCase
class SpriteRenderer { };
struct TransformComponent { };

// Methods/Variables: camelCase
void updatePosition();
float deltaTime;

// Constants: UPPER_SNAKE_CASE
const int MAX_ENTITIES = 10000;
const float PIXEL_SCALE = 1.0f;

// Private members: m_name
class Engine {
    int m_width;
    EventSystem* m_eventSystem;
};

// Internal/Implementation: detail namespace
namespace detail {
    void internalOptimization();
}
```

### Patterns

**Ownership**
- Own: `std::unique_ptr<T>` (exclusive ownership)
- Borrow: `T*` raw pointer (non-owning reference)
- Shared rare: `std::shared_ptr<T>` (last resort only)
- Views: `span<T>` (array views, zero-cost)

**No exceptions**
- Return error codes or `Result<T, Error>` type
- Asserts for invariants (debug mode only)
- Silent failures with logging in release

**RAII everywhere**
- Resources allocated in constructor
- Resources freed in destructor
- No manual cleanup

**Cache-friendly**
- Structure of Arrays (SoA) preferred for hot data
- Align frequently accessed data together
- Minimize pointer chasing
- Batch operations when possible

---

## 🎮 ECS ARCHITECTURE (CRITICAL)

### Entity-Component-System

**Entity** = uint32 (index + generation counter)
```cpp
struct Entity {
    uint32 index : 20;      // 2^20 = ~1M entities
    uint32 generation : 12; // Reuse detection
};
```

**Component** = Plain data struct, 0 overhead
```cpp
struct PositionComponent { float x, y; };
struct VelocityComponent { float dx, dy; };
struct SpriteComponent { uint32 textureId; float u0, v0, u1, v1; };
```

**System** = Logic operating on components
```cpp
class MovementSystem : public ISystem {
    void update(float dt, EntityManager& em);
};
```

**Storage** = Dense SoA (Structure of Arrays)
```
Entities:     [E0] [E1] [E2] [E3] ...
Positions:    [P0] [P1] [P2] [P3] ...
Velocities:   [V0] [V1] [V2] [V3] ...
Sprites:      [S0] [S1] [S2] [S3] ...
```

**Benefits**
- Cache-optimal sequential access
- SIMD-friendly layouts
- Fast iteration (no null checks)
- Deterministic performance
- Easy parallel processing

### Component Registry (Type-Safe)

```cpp
enum class ComponentType : uint16 {
    Position = 0,
    Velocity = 1,
    Sprite = 2,
    // ... auto-generated enum
};

// At compile-time: index components
template<typename T> struct ComponentId { static constexpr uint16 id = ...; };
```

---

## 🔧 KEY SYSTEMS (Overview)

### Physics 2D (Custom Implementation)

**Collision shapes**
- AABB (axis-aligned bounding box) = primary
- Circle (secondary for special cases)
- Raycast
- No polygons initially (complex)

**Rigidbody types**
- Static (immobile, e.g., terrain)
- Dynamic (affected by forces/gravity)
- Kinematic (scripted movement)

**Constraints**
- Simple joint system
- Distance constraints
- Angle limits

**Solver**
- Iterative impulse-based (fast, stable)
- Fixed timestep (1/120 or configurable)
- Broad-phase: spatial grid
- Narrow-phase: shape tests

### Audio System (Custom, Optimized)

**Features**
- WAV file loading (RIFF format parser)
- Audio mixer (multi-channel)
- Master volume + per-channel volume
- Looping, pitch control
- Spatial audio (2D panning)
- No compression initially (use WAV 16-bit PCM)

**Performance**
- Ring buffer playback
- Lock-free queue for commands
- Minimal thread overhead

### Renderer (OpenGL 3.3+ Core)

**Pipeline**
1. Clear framebuffer
2. Update cameras
3. Sort/batch sprites by layer
4. Render batches (instancing)
5. Post-process (pixelization shader)
6. Composite UI (ImGui)
7. Swap buffers

**Features**
- Sprite batching (up to 10k instances per batch)
- Layer-based sorting + Z-order
- Dynamic resolution scaling (internal 256x224 → window size)
- Nearest-neighbor filtering (pixel-perfect)
- Shader hot-reload (dev mode)
- Render-to-texture FX

**Shaders**
- Vertex: position transform, UV pass-through
- Fragment: texture sample + color modulation + pixelization

### Level Editor (ImGui In-Engine)

**Features**
- Toggle play/edit mode (F1)
- Tilemap editor
- Entity placement (drag/drop)
- Property inspector (auto-reflect component data)
- Prefab system
- Multi-layer support
- Undo/redo (command pattern)
- Save/load levels (binary or JSON)

---

## 📊 DEVELOPMENT ROADMAP

**See `todo.md` for detailed task breakdown with visual milestones.**

The project spans **20 major phases**, each with:
- Detailed subtasks
- Visual/functional milestones
- Blog post deliverables
- Estimated timeline
- Validation criteria

---

## 🗂️ FINAL FOLDER STRUCTURE

```
snes-engine/
├── CMakeLists.txt (top-level build)
├── claude.md (THIS FILE)
├── todo.md (DEVELOPMENT ROADMAP)
├── .gitignore
│
├── src/
│   ├── main.cpp
│   ├── core/
│   │   ├── claude.md (Agent-CORE)
│   │   ├── engine.h/cpp
│   │   ├── entity.h/cpp
│   │   ├── component.h/cpp
│   │   ├── system.h/cpp
│   │   ├── event_system.h/cpp
│   │   ├── transform.h/cpp
│   │   └── clock.h/cpp
│   │
│   ├── renderer/
│   │   ├── claude.md (Agent-RENDERER)
│   │   ├── renderer.h/cpp
│   │   ├── shader.h/cpp
│   │   ├── texture.h/cpp
│   │   ├── camera.h/cpp
│   │   ├── batch.h/cpp
│   │   ├── shaders/
│   │   │   ├── sprite.vert
│   │   │   ├── sprite.frag
│   │   │   ├── pixelize.frag
│   │   │   └── ui.vert/frag
│   │   └── gl_utils.h/cpp
│   │
│   ├── physics/
│   │   ├── claude.md (Agent-PHYSICS)
│   │   ├── collision.h/cpp
│   │   ├── rigidbody.h/cpp
│   │   ├── physics_system.h/cpp
│   │   ├── constraints.h/cpp
│   │   └── spatial_grid.h/cpp
│   │
│   ├── audio/
│   │   ├── claude.md (Agent-AUDIO)
│   │   ├── audio_system.h/cpp
│   │   ├── wav_loader.h/cpp
│   │   ├── audio_clip.h/cpp
│   │   └── mixer.h/cpp
│   │
│   ├── input/
│   │   ├── claude.md (Agent-INPUT)
│   │   ├── input_system.h/cpp
│   │   ├── input_map.h/cpp
│   │   └── sdl_input.h/cpp
│   │
│   ├── assets/
│   │   ├── claude.md (Agent-ASSETS)
│   │   ├── asset_manager.h/cpp
│   │   ├── image_loader.h/cpp
│   │   ├── sprite_sheet.h/cpp
│   │   └── pixelizer.h/cpp
│   │
│   ├── animation/
│   │   ├── animator.h/cpp
│   │   ├── animation_clip.h/cpp
│   │   └── state_machine.h/cpp
│   │
│   ├── editor/
│   │   ├── claude.md (Agent-EDITOR)
│   │   ├── editor_system.h/cpp
│   │   ├── level_editor.h/cpp
│   │   ├── property_panel.h/cpp
│   │   ├── gizmos.h/cpp
│   │   └── imgui_glue.h/cpp
│   │
│   └── math/
│       ├── vector.h
│       ├── matrix.h
│       ├── quaternion.h
│       ├── color.h
│       └── utils.h
│
├── include/
│   └── [mirror of src/ structure, headers only]
│
├── docs/
│   ├── claude.md (Agent-DOCS)
│   ├── blog_posts/
│   │   ├── 01-engine-setup.html
│   │   ├── 02-game-loop.html
│   │   └── ... (1 per phase)
│   ├── api/
│   │   └── index.html
│   └── tutorials/
│       ├── getting-started.md
│       └── first-game.md
│
├── examples/
│   ├── pong/
│   │   ├── main.cpp
│   │   └── level.bin
│   ├── platformer/
│   │   └── ...
│   └── space_shooter/
│       └── ...
│
├── assets/
│   ├── sprites/
│   │   ├── player.png
│   │   └── enemies/
│   ├── audio/
│   │   ├── jump.wav
│   │   └── bgm.wav
│   └── levels/
│       ├── level_01.bin
│       └── level_02.bin
│
└── tests/
    ├── math_tests.cpp
    ├── ecs_tests.cpp
    ├── physics_tests.cpp
    └── CMakeLists.txt
```

---

## ⚡ TOKEN OPTIMIZATION RULES (CRITICAL)

### Fragmentation Strategy

1. **One request = ONE system module OR 3-5 small files**
2. **Max 10k tokens per Claude response** (strict)
3. **Split large systems across multiple phases**

### When File Gets Too Big

| File Size | Action |
|-----------|--------|
| < 200 LOC | Single file, single request |
| 200-500 LOC | Single request, split .h/.cpp |
| 500-1000 LOC | Multiple requests (class by class) |
| 1000+ LOC | Create sub-agent with specialized claude.md |

### Example Prompt Template

```
[PHASE: 8]
[MODULE: core/entity_manager]
[FILE: entity_manager.h]
[TOKENS USED: 3000/10000]
[CONTEXT]
Implement EntityManager for dense ECS.
Entity = uint32 (20-bit index + 12-bit generation).
Store component data as SoA (Structure of Arrays).
Max 10k entities.

[CONSTRAINTS]
- < 250 lines of code
- Header-only or .h + .cpp split?
- No exceptions, use result types
- RAII for cleanup

[DELIVERABLE]
entity_manager.h with class definition + key methods:
- create() → Entity
- destroy(Entity)
- alive(Entity) → bool
- hasComponent<T>(Entity) → bool
- getComponent<T>(Entity) → T*
```

---

## 🎯 PROMPT GUIDELINES FOR YOU

### Before Each Request

1. **Check your token budget**
   - "I've used X tokens so far in this conversation"
   - "I'll request a small feature: Y (estimate ~2k tokens)"

2. **Be specific**
   - ✅ "Implement SpriteRenderer::render() for batching 10 sprites"
   - ❌ "Code me the renderer"

3. **Provide context**
   - "See include/renderer/renderer.h for interface"
   - "Follow ECS patterns from Phase 8"

4. **Validate before committing**
   ```bash
   cd build && cmake .. && make
   # Check for warnings/errors
   ```

### Red Flags (Break These)

- ❌ "Code 3000 lines of new stuff"
- ❌ "Refactor everything at once"
- ❌ "No error handling"
- ❌ "Tight coupling between systems"
- ❌ "Magic numbers everywhere"

---

## 🔧 CONVENTIONS (INLINE STYLE)

### Header Files

```cpp
#pragma once

// Forward declarations
class Engine;
struct TransformComponent;

namespace engine {

class SpriteRenderer {
public:
    explicit SpriteRenderer(Renderer* renderer);
    ~SpriteRenderer();
    
    // No copies
    SpriteRenderer(const SpriteRenderer&) = delete;
    SpriteRenderer& operator=(const SpriteRenderer&) = delete;
    
    void render(const EntityManager& em, Camera2D& camera);
    
private:
    Renderer* m_renderer; // non-owning
    std::unique_ptr<ShaderProgram> m_shader;
    std::unique_ptr<VertexBuffer> m_vbo;
    
    void updateBatches(const EntityManager& em, Camera2D& camera);
};

} // namespace engine
```

### Implementation Pattern

```cpp
#include "sprite_renderer.h"
// ...

namespace engine {

SpriteRenderer::SpriteRenderer(Renderer* renderer)
    : m_renderer(renderer)
{
    m_shader = std::make_unique<ShaderProgram>("sprite.vert", "sprite.frag");
    m_vbo = std::make_unique<VertexBuffer>(MAX_VERTICES);
}

SpriteRenderer::~SpriteRenderer()
{
    // Unique ptrs auto-cleanup
}

void SpriteRenderer::render(const EntityManager& em, Camera2D& camera)
{
    // Implementation
}

} // namespace engine
```

---

## 🚀 WORKFLOW CYCLE

### Daily Dev Cycle

```
[Morning]
1. Identify next feature (from todo.md)
2. Create focused prompt (< 2 min)
3. Claude generates code (5-10 min)
4. Review output (2-3 min)

[Afternoon]
5. Integrate code into project
6. Compile & fix warnings (5 min)
7. Git commit ("feat: phase X, system Y")
8. Test basic functionality

[Evening]
9. Plan next feature OR
10. Generate blog post for completed phase
```

### Weekly Cadence

- Mon-Thu: Code generation + integration
- Fri: Blog post writing + documentation
- Weekend: Testing + optional refactoring

---

## 📝 COMMITMENTS

This `claude.md` commits to:

✅ **Zero external dependencies** (except SDL2, OpenGL, ImGui)
✅ **Custom physics 2D** (no Box2D)
✅ **Custom audio system** (no FMOD)
✅ **100% ECS architecture** (day 1)
✅ **Extensible design** (plugins, custom systems)
✅ **In-engine level editor** (ImGui-based)
✅ **WebGL-ready** (Emscripten preparation)
✅ **Blog posts** (auto-generated documentation)
✅ **Token-efficient** (< 10k per request)
✅ **Cache-optimal** (SoA, minimal pointer chasing)

---

## 🎬 NEXT IMMEDIATE STEPS

1. **Create folder structure** + CMakeLists.txt
2. **Generate Agent-CORE claude.md** (specialized ECS directives)
3. **Generate Agent-RENDERER claude.md**
4. **Phase 0: INIT** (basic project setup)
5. **Phase 1: CORE LOOP** (main engine skeleton)

Then we proceed phase-by-phase, requesting Claude code for each system.

---

**Version**: 1.0
**Last Updated**: 2026-01-13
**Status**: Ready for Phase 0
**Supervisor**: You
**Agents**: 8 specialized + coordinated
**Philosophy**: Ultra-optimized + Extensible + Well-Documented

---

🚀 **Ready to build the engine of your dreams!**

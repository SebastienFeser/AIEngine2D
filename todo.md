# 🎮 SNES Engine - Detailed Development Roadmap

**Total Estimated Duration**: 16-24 weeks (full-time) or 32-48 weeks (part-time 20h/week)

Each phase includes:
- ✅ Detailed subtasks
- 🎨 Visual/functional milestones
- 📝 Blog post deliverable
- ⏱️ Time estimate
- 🔍 Validation criteria

---

## 🚀 PHASE 0: INIT & INFRASTRUCTURE
**Duration**: 4-5 days | **Blog Post**: "Setting Up a Modern C++ Game Engine - From Zero to Compilation"

### Subtasks

- [x] **Create Git repository**
  - Initialize git repo
  - Create `.gitignore` (build/, bin/, .vscode/, .idea/, *.o, *.a, .DS_Store)
  - First commit: "init: project setup"

- [x] **Create folder structure**
  - /src, /include, /docs, /examples, /assets, /tests
  - /src/{core,renderer,physics,audio,input,assets,animation,editor,math}
  - /assets/{sprites,audio,levels}

- [x] **CMakeLists.txt (top-level)**
  - Detect compiler (GCC, Clang, MSVC)
  - Find SDL2, OpenGL, ImGui packages
  - Set C++17 standard
  - Enable -O2 optimizations
  - Configure Debug/Release builds
  - Add subdirectories

- [x] **CMakeLists.txt (src/)**
  - Create library targets for each module
  - Link SDL2, OpenGL, ImGui via vcpkg

- [x] **CMakeLists.txt (test/)**
  - Google Test setup (optional)

- [x] **CMakeLists.txt (examples/)**
  - Build example projects

- [x] **IDE configuration**
  - Generate VS Code `launch.json` for debugging
  - Generate `.clang-format` config
  - Generate `settings.json` for workspace

- [x] **First compilation test**
  - main.cpp with SDL2 window + OpenGL context
  - Verify build succeeds (AIEngine2D.exe created)

### 🎨 Visual Milestones

**After Phase 0:**
```
✅ Folder structure complete
✅ CMakeLists.txt compiles successfully
✅ IDE can open project without errors
✅ No compilation warnings
✅ Git repo ready
```

### ✔️ Validation Criteria

```bash
# Should succeed without errors
cd build && cmake .. && make

# Should show clean build output
# No undefined references
# No linker errors
```

---

## ⚡ PHASE 1: CORE ENGINE LOOP
**Duration**: 5-7 days | **Blog Post**: "Building a Game Loop: Fixed Timestep vs Variable Timestep"

### Subtasks

- [x] **Engine main class**
  - `class Engine` in main.cpp (basic version)
  - `init()`, `run()`, `shutdown()` lifecycle
  - Note: Singleton pattern (`Engine::Get()`) to be added later

- [x] **Window creation (SDL2)**
  - SDL_Init()
  - SDL_CreateWindow(800x600, centered)
  - Window title: "AIEngine2D - Test"
  - Window icon (TODO later)

- [x] **OpenGL context initialization**
  - SDL_GL_CreateContext()
  - SDL_GL_SetSwapInterval(1) for Vsync
  - OpenGL 3.3 Core Profile
  - Clear color: cornflower blue (test color)

- [x] **Main loop structure**
  ```
  while (running) {
    handleEvents();
    update(deltaTime);
    render();
    swapBuffers();
  }
  ```

- [ ] **Fixed timestep (120 FPS)**
  - `deltaTime = 1/120 = 0.00833s`
  - Accumulator pattern (avoid spiral of death)
  - Step physics/logic at fixed rate
  - Render at refresh rate (uncapped or Vsync)

- [x] **Event handling**
  - SDL_PollEvent() loop
  - SDL_QUIT → set running = false
  - SDL_KEYDOWN (ESC) → quit

- [ ] **Timing/Clock system**
  - `Clock` class (measure frame time)
  - FPS counter (log every 100 frames)
  - Frame delta time tracking

- [x] **Logger system**
  - `LOG_INFO()`, `LOG_WARNING()`, `LOG_ERROR()` macros
  - Output to console with colors (Windows + Unix support)
  - Level prefix ([INFO], [WARNING], [ERROR])

- [x] **Test: Basic window**
  - Window displays, no crashes
  - Console shows colored logs
  - Quit on ESC key

### 🎨 Visual Milestones

**After Phase 1:**
```
┌─ SNES Engine ────────┐
│                      │
│   [BLACK WINDOW]     │
│   800 x 600          │
│                      │
│   FPS: 120           │  ← shown in console
│                      │
└──────────────────────┘

Console output:
[INFO] Engine initialized
[INFO] Window created (800x600)
[INFO] OpenGL 3.3+ loaded
[INFO] FPS: 120.0
```

### ✔️ Validation Criteria

```
✅ Window opens without crash
✅ Displays 800x600 pixels
✅ FPS locked to 120 (±1 FPS)
✅ ESC key closes window gracefully
✅ No memory leaks (valgrind clean)
✅ Console shows FPS counter
```

---

## 🔢 PHASE 2: MATH FOUNDATIONS
**Duration**: 3-4 days | **Blog Post**: "SIMD-Friendly Math Library for Game Engines"

### Subtasks

- [ ] **Vector2 class**
  - Members: x, y (float)
  - Operators: +, -, *, /, ==, !=
  - Methods: length(), normalize(), dot(), distance()
  - Constructor overloads

- [ ] **Vector3 class**
  - Members: x, y, z (float)
  - Same operators/methods as Vector2
  - Cross product, 3D distance

- [ ] **Vector4 class**
  - Members: x, y, z, w (float)
  - For homogeneous coordinates / colors

- [ ] **Matrix4x4 class**
  - 4x4 float array (row-major or column-major, consistent)
  - Operators: matrix multiplication (M1 * M2)
  - Methods:
    - `identity()` → identity matrix
    - `translate(Vector3)` → translation matrix
    - `scale(Vector3)` → scale matrix
    - `rotateZ(float angle)` → 2D rotation around Z
    - `orthographic(left, right, bottom, top, near, far)` → projection matrix
    - `inverse()` → matrix inversion
    - `transpose()` → transpose

- [ ] **Quaternion class** (for 3D rotation, but simplify for 2D)
  - Members: x, y, z, w
  - Constructors from angle/axis
  - Quaternion multiplication
  - To/from Euler angles

- [ ] **Color struct**
  - Members: r, g, b, a (uint8 or float 0-1)
  - Constructors (hex, RGB, RGBA)
  - Operators: ==, !=
  - Methods: toHex(), fromHex()

- [ ] **Rect struct**
  - Members: x, y, width, height (float)
  - Methods: contains(Vector2), intersects(Rect), area()

- [ ] **Circle struct**
  - Members: x, y, radius (float)
  - Methods: contains(Vector2), intersects(Circle)

- [ ] **Math utils (header-only)**
  - `lerp(float a, float b, float t)` → linear interpolation
  - `clamp(float v, float min, float max)` → clamp value
  - `easeInQuad(float t)`, `easeOutQuad(t)`, `easeInOutQuad(t)`
  - `radians(float degrees)`, `degrees(float radians)`
  - `min(float a, float b)`, `max(a, b)`
  - `abs(float v)`

- [ ] **Random number generator**
  - `Random::seed(uint32 s)`
  - `Random::nextInt(int max)` → [0, max)
  - `Random::nextFloat()` → [0.0, 1.0)
  - `Random::range(float min, float max)` → [min, max)

- [ ] **Unit tests (optional but recommended)**
  - Vector2 addition, subtraction, scaling
  - Matrix multiplication
  - Rotation tests

### 🎨 Visual Milestones

**After Phase 2:**
```
✅ All math operations compile without errors
✅ Unit tests pass (if implemented)
✅ Example: Create 256x224 orthographic matrix for SNES
✅ Example: Rotate a vector by 45 degrees
```

### ✔️ Validation Criteria

```cpp
// Example test
Vector2 v1(3, 4);
Vector2 v2(1, 2);
Vector2 v3 = v1 + v2;  // (4, 6)
assert(v3.x == 4 && v3.y == 6);

Matrix4x4 ortho = Matrix4x4::Orthographic(0, 256, 224, 0, -1, 1);
// Result: orthographic projection for SNES 256x224
```

---

## 🎨 PHASE 3: MINIMAL RENDERER
**Duration**: 6-8 days | **Blog Post**: "OpenGL 3.3+ Rendering Pipeline for 2D Games"

### Subtasks

- [ ] **OpenGL context validation**
  - Query OpenGL version (must be ≥ 3.3)
  - List supported extensions
  - Enable debug output (optional)

- [ ] **VAO/VBO/IBO patterns**
  - `class VertexBuffer`
    - Create VBO, VAO
    - Bind/unbind
    - Data upload (static/dynamic)
  - `class IndexBuffer`
    - Create EBO
    - Store indices (quad = 2 triangles = 6 indices)
  - `class VertexArray`
    - Wrap VAO + VBO + IBO
    - Vertex attribute layout

- [ ] **Quad mesh**
  - Pre-defined unit quad (0,0 to 1,1)
  - 4 vertices + 6 indices (2 triangles)
  - Store in static VBO

- [ ] **Shader compilation**
  - `class ShaderProgram`
    - Load vertex/fragment source
    - Compile individual shaders
    - Link program
    - Error reporting
  - `class Shader`
    - Compile from file/string
    - Report compilation errors

- [ ] **Basic vertex/fragment shaders**
  - vertex.glsl: transform position by MVP matrix
  - fragment.glsl: output white color (for now)

- [ ] **Matrix transforms**
  - `class Camera2D`
    - Position, zoom
    - Compute view matrix
    - Compute projection matrix (orthographic)
  - Model matrix (entity position/rotation/scale)
  - MVP = Projection * View * Model

- [ ] **Color rendering (solid quads)**
  - Render 5 colored quads at different positions
  - Red, green, blue, yellow, magenta
  - Demonstrate matrix transforms

- [ ] **Clear framebuffer**
  - glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
  - Set clear color

- [ ] **Render loop integration**
  - Engine calls `renderer->render()`
  - Renderer clears, renders, swaps buffers

### 🎨 Visual Milestones

**After Phase 3:**
```
┌─ SNES Engine ────────────────┐
│                              │
│  ██ ██ ██ ██ ██              │  (5 colored squares)
│                              │
│  ██ ██ ██ ██ ██              │
│                              │
│  FPS: 120                    │
└──────────────────────────────┘
```

### ✔️ Validation Criteria

```
✅ 5 colored quads render without flickering
✅ Quads positioned at different coords
✅ No OpenGL errors in console
✅ Shader compilation succeeds
✅ Camera zoom/pan works (test with input)
```

---

## 🖼️ PHASE 4: TEXTURE & SPRITE BASICS
**Duration**: 5-6 days | **Blog Post**: "Sprite Rendering: Atlasing and Efficient Memory Management"

### Subtasks

- [ ] **Image loading (simple format)**
  - Support PPM format (Portable PixMap, easiest)
    - ASCII header: `P3`, width, height, max color (255)
    - RGB bytes follow
  - OR: Custom binary format (header + raw RGBA pixels)
  - Error handling for missing/invalid files

- [ ] **Texture class**
  - `class Texture`
    - GPU texture ID
    - Width, height
    - Load from file
    - Bind/unbind
    - Filtering mode (nearest for pixel-perfect)
    - Cleanup in destructor

- [ ] **Texture caching**
  - `class TextureManager` (singleton)
    - Load texture once, reuse by path
    - Prevent duplicates in VRAM

- [ ] **Sprite data structure**
  - `struct Sprite`
    - Texture ID
    - Source rect (x, y, w, h in spritesheet)
    - UV coordinates (u0, v0, u1, v1)
    - Pivot point (for rotation)

- [ ] **Spritesheet support**
  - Load single large image (atlas)
  - Specify regions (x, y, w, h) for each sprite
  - Generate UV coords automatically
  - Example: 256x256 atlas with 16x16 sprites = 256 sprites

- [ ] **UV mapping**
  - Convert pixel coords to normalized UV (0-1 range)
  - Handle spritesheet padding (border pixels)

- [ ] **Sprite rendering (quads + UVs)**
  - Modify fragment shader to sample texture
  - Pass UV coords in vertex attributes
  - Render 10 different sprites on screen

- [ ] **Batching foundations**
  - Store sprite data in VBO (position + UV)
  - Render multiple sprites in one draw call (if same texture)

- [ ] **Test: Load and render sprites**
  - Create simple 16x16 pixel sprites (red square, blue circle, etc.)
  - Display 10 sprites at different positions

### 🎨 Visual Milestones

**After Phase 4:**
```
┌─ SNES Engine ────────────────┐
│                              │
│  [sprite] [sprite] [sprite]  │
│  [sprite] [sprite] [sprite]  │
│  [sprite] [sprite] [sprite]  │  (10 textured quads)
│  [sprite] [sprite]           │
│                              │
│  FPS: 120                    │
└──────────────────────────────┘
```

### ✔️ Validation Criteria

```
✅ Load PPM/custom image file without crash
✅ 10 sprites render with textures visible
✅ Sprites tile correctly from spritesheet
✅ No texture artifacts or clipping
✅ Texture memory freed on exit
```

---

## 🌈 PHASE 5: PIXELIZATION SHADERS
**Duration**: 5-7 days | **Blog Post**: "Pixel-Perfect Rendering: Techniques for Retro Game Engines"

### Subtasks

- [ ] **Render-to-texture infrastructure**
  - `class FrameBuffer`
    - Create FBO, color attachment, depth attachment
    - Bind/unbind
    - Resize dynamically
  - `class RenderTarget`
    - Wrap FBO for rendering to texture

- [ ] **Internal resolution (256x224)**
  - Render all game content to 256x224 framebuffer
  - Keep window at 800x600 (or resizable)
  - Scale 256x224 → window size with pixelization

- [ ] **Pixelization shader**
  - Fragment shader that:
    - Samples from FBO texture
    - Applies pixel-grid effect
    - Nearest-neighbor filtering
    - Upscales to screen size
  - Vertex shader: full-screen quad

- [ ] **Scanline effect (optional)**
  - Add horizontal dark lines
  - Simulates CRT monitor (SNES-like aesthetic)
  - Toggle on/off with debug key

- [ ] **Color palette system (optional)**
  - Restrict colors to 16-bit palette (SNES-style)
  - Dither or snap to nearest color
  - Lookup table in texture

- [ ] **Debug visualization**
  - F2 key: toggle pixelization on/off
  - F3 key: toggle scanlines
  - Show internal resolution info

- [ ] **Test: Pixelized rendering**
  - Render 10 sprites through pixelization pipeline
  - Verify pixel-perfect aesthetic

### 🎨 Visual Milestones

**After Phase 5:**
```
WITHOUT pixelization (blurry):
┌──────────────────────────────┐
│  [smooth sprite] [blurry...] │
└──────────────────────────────┘

WITH pixelization (crisp):
┌──────────────────────────────┐
│  ████████ ████████           │
│  ████████ ████████           │  (pixel-perfect blocks)
│  ████████ ████████           │
│  ████████ ████████           │
└──────────────────────────────┘

+ optional scanlines
────────────────────────────────
```

### ✔️ Validation Criteria

```
✅ 256x224 framebuffer renders without artifacts
✅ Pixelization shader applied correctly
✅ F2 toggles pixelization on/off
✅ No visual glitches or tearing
✅ Performance: > 100 FPS (should be fast)
```

---

## ⌨️ PHASE 6: INPUT SYSTEM
**Duration**: 4-5 days | **Blog Post**: "Designing Extensible Input Systems"

### Subtasks

- [ ] **Keyboard polling (SDL2)**
  - `class InputSystem`
    - Poll SDL_KeyboardState every frame
    - Track key down/up events
    - Key code mapping

- [ ] **Input mapping (key → action)**
  - `enum class Action { MOVE_LEFT, MOVE_RIGHT, JUMP, ATTACK, ... }`
  - `class InputMap`
    - Map keys to actions (configurable)
    - E.g., SDL_SCANCODE_A → MOVE_LEFT
    - Allow rebinding

- [ ] **Button state tracking**
  - `isKeyDown(SDL_Scancode)` → bool
  - `isKeyPressed(SDL_Scancode)` → bool (edge detection)
  - `isKeyReleased(SDL_Scancode)` → bool
  - Distinguish press/release/held

- [ ] **Input buffering**
  - Store input events in queue
  - Prevent missed inputs (especially important for fighting games)
  - Clear buffer each frame

- [ ] **Mouse input**
  - `getMousePos()` → Vector2
  - `isMouseDown()` → bool
  - `isMousePressed()` → bool
  - For editor (level editor needs mouse)

- [ ] **Debug input**
  - F1 key: toggle play/edit mode (for editor)
  - F2 key: toggle pixelization (from Phase 5)
  - Ctrl+R: reload assets
  - ESC: pause/menu

- [ ] **Test: Input response**
  - Display which keys are pressed
  - Move sprite with WASD
  - Jump with SPACE

### 🎨 Visual Milestones

**After Phase 6:**
```
┌─ SNES Engine ────────────────┐
│                              │
│      [player sprite]         │
│      (position changes       │
│       with WASD input)       │
│                              │
│  Keys: W=UP A=LEFT D=RIGHT   │
│  Space=JUMP                  │
└──────────────────────────────┘

Console:
Key Down: A
Key Down: W
Key Up: A
```

### ✔️ Validation Criteria

```
✅ WASD moves sprite smoothly
✅ SPACE triggers jump (can be seen in physics)
✅ Input responsive (no lag)
✅ F1 toggles editor mode (visual feedback)
✅ Input buffering works (no missed inputs)
```

---

## 🔔 PHASE 7: EVENT SYSTEM
**Duration**: 4-5 days | **Blog Post**: "Event-Driven Architecture in Games"

### Subtasks

- [ ] **Event queue (frame-buffered)**
  - `class EventQueue`
    - Store events for current frame
    - Clear after frame is processed
    - Safe to iterate (can add events during dispatch)

- [ ] **Event dispatcher**
  - `class EventDispatcher`
    - Register listeners for event types
    - Dispatch events to all listeners
    - Return early if event is consumed

- [ ] **Built-in events**
  - `CollisionEnterEvent { Entity a, b }`
  - `CollisionExitEvent { Entity a, b }`
  - `InputEvent { Action action, bool pressed }`
  - `EntityDestroyedEvent { Entity e }`
  - `AnimationFinishedEvent { Entity e, AnimId anim }`

- [ ] **Custom event support**
  - Allow users to define custom event types
  - Template-based event system
  - Type-safe listener registration

- [ ] **Event priority**
  - Some events processed before others
  - E.g., Input → Physics → Rendering order

- [ ] **Safe iteration during dispatch**
  - Listeners can add/remove listeners during dispatch
  - Double-buffered queue to avoid iterator invalidation

- [ ] **Test: Event flow**
  - Emit collision event, verify listeners receive it
  - Create 2 entities, collide, log event

### 🎨 Visual Milestones

**After Phase 7:**
```
Console output:
[EVENT] CollisionEnter: Entity(1) with Entity(3)
[EVENT] InputEvent: JUMP pressed
[EVENT] InputEvent: JUMP released
[EVENT] AnimationFinished: Entity(1) attack_anim

(Events printed in order of dispatch)
```

### ✔️ Validation Criteria

```
✅ Events dispatched in correct order
✅ Multiple listeners receive same event
✅ Event consuming works (early exit)
✅ Custom events can be defined
✅ No crashes with dynamic listener add/remove
```

---

## 🎯 PHASE 8: ECS CORE ⭐ **CRITICAL**
**Duration**: 8-10 days | **Blog Post**: "Entity-Component-System Design: Building Data-Oriented Game Engines"

This is the most important phase. Everything hinges on clean ECS.

### Subtasks

- [ ] **Entity representation**
  - `using Entity = uint32` with structure:
    - Bits 0-19: index (up to ~1M entities)
    - Bits 20-31: generation (for reuse detection)
  - `class EntityHandle` for type safety (wraps Entity)

- [ ] **Entity manager**
  - `class EntityManager`
    - Create entity (allocate in dense array)
    - Destroy entity (mark as dead, reuse slot later)
    - Alive check (validate generation)
    - Entity count
    - Iteration over alive entities

- [ ] **Component storage (dense SoA)**
  - One array per component type
  - Example (Position):
    ```
    Components[Position]:
    [Entity0.pos] [Entity1.pos] [Entity3.pos] [Entity7.pos] ...
    ```
  - NOT:
    ```
    [Entity0] [Entity1] [Entity2] [Entity3] ...
      pos       pos       X        pos
    ```
  - Keep entities tightly packed (SoA = Structure of Arrays)

- [ ] **Component registration**
  - `enum ComponentType { POSITION=0, VELOCITY=1, SPRITE=2, ... }`
  - `ComponentRegistry` maps type ID to storage arrays
  - Auto-generate component IDs at compile-time (template magic)

- [ ] **System manager**
  - `class SystemManager`
    - Register systems (`addSystem<MovementSystem>()`)
    - Update all systems in order each frame
    - Remove systems on demand

- [ ] **Entity queries**
  - Query entities with component set
  - Example: get all entities with (Velocity, Rigidbody)
  - Cache query results for fast iteration
  - `auto entities = em.query<Position, Velocity>()`

- [ ] **Component attachment/detachment**
  - `em.addComponent<SpriteComponent>(entity, data)`
  - `em.removeComponent<SpriteComponent>(entity)`
  - `em.hasComponent<SpriteComponent>(entity) → bool`
  - `auto& comp = em.getComponent<SpriteComponent>(entity)`

- [ ] **Dirty component tracking**
  - Mark components as dirty if modified
  - Update dependent systems only if changed
  - E.g., Position is dirty → Transform system recalculates

- [ ] **Hierarchy support (parent-child)**
  - `HierarchyComponent { Entity parent, Vector<Entity> children }`
  - Traversal (DFS/BFS over entity tree)
  - Prepare for Phase 9 (Transform propagation)

- [ ] **Memory pools**
  - Pre-allocate component storage (avoid runtime fragmentation)
  - Grow dynamically if needed
  - Max 10k entities per pool

- [ ] **Test: ECS functionality**
  - Create 100 entities with Position + Velocity
  - Query them, iterate, update positions
  - Destroy 50 entities, verify alive count
  - Spawn 50 new entities, verify generation counter works

### 🎨 Visual Milestones

**After Phase 8:**
```
✅ 100 entities created successfully
✅ Entity queries return correct subsets
✅ Dense SoA layout verified (memory efficient)
✅ Component attachment/removal works
✅ Hierarchy traversal functional

Memory layout example:
Entity IDs:     [E0] [E3] [E7] [E15] ...
Positions:      [P0] [P3] [P7] [P15] ...
Velocities:     [V0] [V3] [V7] [V15] ...
Sprites:        [S0] [S3] [S7] [S15] ...
(Cache-friendly sequential access)
```

### ✔️ Validation Criteria

```cpp
// Entity creation
Entity e1 = em.create();
Entity e2 = em.create();

// Component attachment
em.addComponent<PositionComponent>(e1, {10, 20});
em.addComponent<VelocityComponent>(e1, {1, 0});

// Query
auto entities = em.query<PositionComponent, VelocityComponent>();
assert(entities.size() >= 1);

// Get component
auto& pos = em.getComponent<PositionComponent>(e1);
assert(pos.x == 10 && pos.y == 20);

// Destroy
em.destroy(e1);
assert(!em.alive(e1));

✅ All assertions pass
✅ Memory footprint < 50MB for 10k entities
✅ Query returns correct entities
```

---

## 🔄 PHASE 9: TRANSFORM HIERARCHY
**Duration**: 4-5 days | **Blog Post**: "Transform Hierarchies: Local vs World Space"

### Subtasks

- [ ] **Transform component**
  - Members: position (local), rotation (local), scale (local)
  - Methods: getWorldPosition(), getWorldRotation(), etc.
  - Cache world transform (update only if dirty)

- [ ] **Parent-child relationships**
  - `TransformComponent { Entity parent; Vector<Entity> children; }`
  - Child inherits parent transform
  - Child position is relative to parent

- [ ] **Local vs world space**
  - Local: relative to parent
  - World: relative to origin (0,0)
  - Convert between spaces (matrix multiplication)

- [ ] **Transform propagation**
  - `TransformSystem::update()`
    - Walk hierarchy top-down
    - Compute world transform = parent world × child local
    - Use dirty flags to skip unchanged subtrees
  - Mark transform dirty when parent moves

- [ ] **Matrix caching**
  - Cache local-to-world matrix
  - Recompute only on dirty
  - Avoid redundant matrix multiplications

- [ ] **Test: Hierarchy movement**
  - Create parent entity at (100, 100)
  - Create child entity at (10, 10) relative to parent
  - Move parent to (200, 200)
  - Verify child moves to (210, 210) in world space

### 🎨 Visual Milestones

**After Phase 9:**
```
Hierarchy:
└─ Player (pos: 100, 100)
   ├─ Arm (pos: 20, 0 local)
   ├─ Head (pos: 0, -30 local)
   │  └─ Eye (pos: 5, 5 local)

World positions:
Player: (100, 100)
Arm: (120, 100) ← parent + local offset
Head: (100, 70)
Eye: (105, 75) ← grandparent + parents offset + local

(Move player to 200,200 → all children move accordingly)
```

### ✔️ Validation Criteria

```
✅ Parent movement affects all children
✅ Child local transform stays constant
✅ Rotation/scale propagate correctly
✅ Dirty flag optimization works
✅ No redundant matrix computations
```

---

## 🎨 PHASE 10: SPRITE SYSTEM
**Duration**: 5-6 days | **Blog Post**: "Sprite Batching and GPU Instancing for 2D Engines"

### Subtasks

- [ ] **SpriteComponent**
  - Members: textureId, sourceRect (or spriteIndex), color tint, renderLayer
  - Optional: flipX, flipY, rotation (but transform does rotation)

- [ ] **SpriteRenderer system**
  - `class SpriteRendererSystem : public ISystem`
    - Render all entities with SpriteComponent
    - Respect layer/Z-order
    - Use dynamic batching

- [ ] **Layer system**
  - Layer 0 = background, Layer 10 = foreground, etc.
  - Entities render in layer order
  - 16 layers total (0-15)

- [ ] **Depth/Z-order sorting**
  - Primary: renderLayer
  - Secondary: Z position (Y for SNES-style)
  - Bucket sort by layer + insertion sort within layer

- [ ] **Sprite batching (10k instances)**
  - Collect all sprites for current layer
  - Batch by texture (reduce draw calls)
  - Use instancing or dynamic VBO
  - Single draw call per texture per layer

- [ ] **Culling (off-screen sprites)**
  - Skip sprites outside camera frustum
  - 2D AABB vs camera bounds check
  - Reduce vertex processing overhead

- [ ] **Test: Render 1000 sprites**
  - Spawn 1000 random sprites
  - Verify FPS > 100
  - Verify batching works (check draw call count with glDebug)

### 🎨 Visual Milestones

**After Phase 10:**
```
┌─ SNES Engine ────────────────┐
│ ███ ███ ███ ███ ███ ███      │
│ ███ ███ ███ ███ ███ ███      │
│ ███ ███ ███ ███ ███ ███      │
│ ███ ███ ███ ███ ███ ███      │
│ ███ ███ ███ ███ ███ ███  ~1000 sprites
│ ███ ███ ███ ███ ███ ███      │
│ ███ ███ ███ ███ ███ ███      │
│                              │
│ FPS: 120                     │
└──────────────────────────────┘
```

### ✔️ Validation Criteria

```
✅ 1000 sprites render without significant FPS drop
✅ Sprites sorted correctly by layer
✅ Off-screen culling works
✅ Batching reduces draw calls to ~10 (multiple textures)
✅ No visual artifacts
```

---

## ⚙️ PHASE 11: PHYSICS 2D - BASICS
**Duration**: 8-10 days | **Blog Post**: "Implementing a 2D Physics Engine: Collision Detection Basics"

### Subtasks

- [ ] **Rigidbody component**
  - Members: mass, velocity, angularVelocity, gravity, drag, restitution
  - Types: Static (mass=∞), Dynamic (mass>0), Kinematic (script-driven)
  - Methods: applyForce(), applyImpulse(), setVelocity()

- [ ] **Collision component**
  - Members: shape (AABB or Circle), layer, layerMask, isTrigger
  - Represents collision bounds
  - Layer-based filtering (e.g., player collides with enemies, not other players)

- [ ] **Physics system**
  - `class PhysicsSystem : public ISystem`
    - Update velocities (gravity, forces)
    - Integrate velocities (V += A*dt, P += V*dt)
    - Fixed timestep (1/120 by default)
    - Collision detection (next subtask)

- [ ] **Fixed timestep for physics**
  - Physics always steps at fixed rate (deterministic)
  - Accumulator pattern (from Phase 1) applies
  - Multiple physics steps per frame if needed

- [ ] **Broad-phase (spatial grid)**
  - Divide world into grid cells
  - Each cell stores entities in it
  - Candidate pairs = entities in same/adjacent cells
  - E.g., 32x32 pixel cells for 256x224 world

- [ ] **Narrow-phase (shape tests)**
  - `intersect(AABB, AABB) → bool`
  - `intersect(Circle, Circle) → bool`
  - `intersect(AABB, Circle) → bool`
  - Return contact info (position, normal, depth)

- [ ] **Collision detection (no response yet)**
  - Detect all collisions in frame
  - Store contact pairs
  - Emit `CollisionEnterEvent` for new collisions
  - Emit `CollisionExitEvent` for lost collisions
  - Maintain collision cache (check if previously colliding)

- [ ] **Test: Collision detection**
  - Create 2 AABBs, move them together
  - Verify collision detected
  - Move them apart
  - Verify collision exit detected

### 🎨 Visual Milestones

**After Phase 11:**
```
Frame N:
┌────────────────────┐
│  [Box1]    [Box2]  │
│                    │
│            [Box3]  │
└────────────────────┘

Collision pairs detected:
(Box1, nothing)
(Box2, nothing)
(Box3, nothing)

(Move boxes together)

Collision pairs detected:
(Box1, Box2) ← NEW COLLISION
(Box2, Box1)
(Box3, nothing)

Console:
[COLLISION] Entity 1 <-> Entity 2
```

### ✔️ Validation Criteria

```
✅ Collision detection accurate (test 50 random shapes)
✅ Broad-phase reduces candidates significantly
✅ CollisionEnterEvent fires correctly
✅ CollisionExitEvent fires on separation
✅ No missing collisions
```

---

## 💥 PHASE 12: PHYSICS 2D - RESOLUTION
**Duration**: 6-8 days | **Blog Post**: "Collision Resolution: From Detection to Physical Response"

### Subtasks

- [ ] **Collision resolution (impulse-based)**
  - Impulse = force applied over time
  - For each contact, compute impulse to separate bodies
  - Apply impulse to velocities
  - Iterative solver (2-3 iterations per frame for stability)

- [ ] **Friction and restitution**
  - Restitution = bounciness (0=stick, 1=bounce, >1=explode)
  - Friction = resistance to sliding
  - Combined from both bodies (average or multiply)

- [ ] **Static/dynamic/kinematic types**
  - Static: never moves (walls, platforms)
  - Dynamic: affected by forces and collisions
  - Kinematic: script-driven (doesn't respond to collisions)
  - Resolve differently based on types

- [ ] **Constraints (joints)**
  - Distance constraint: keep 2 points at distance D
  - Angle constraint: keep angle between bodies at θ
  - Solve with iterative constraint solver

- [ ] **Raycasting**
  - `raycast(origin, direction, maxDistance) → RaycastHit`
  - Returns closest entity hit
  - RaycastHit: entity, position, normal, distance

- [ ] **Physics queries**
  - `getEntitiesInRadius(center, radius) → vector<Entity>`
  - `getEntitiesInRect(rect) → vector<Entity>`
  - Used for gameplay (detect nearby enemies, etc.)

- [ ] **Test: Physics simulation**
  - Drop box on static platform
  - Verify it stops (doesn't sink)
  - Jump and land
  - Roll along slope
  - Bounce (high restitution)

### 🎨 Visual Milestones

**After Phase 12:**
```
Frame N-1:
┌──────────────────────┐
│  [Box1] (in air)     │
│                      │
│                      │
│  ════════════════    │ ← platform
└──────────────────────┘

Frame N:
┌──────────────────────┐
│                      │
│  [Box1] (falling)    │
│                      │
│  ════════════════    │
└──────────────────────┘

Frame N+1:
┌──────────────────────┐
│                      │
│  [Box1] (on ground)  │
│  ════════════════    │ ← resting on platform
└──────────────────────┘

(Box settles due to gravity + collision resolution)
```

### ✔️ Validation Criteria

```
✅ Box falls and stops on platform
✅ No clipping through terrain
✅ Jumping works (apply upward impulse, fall back)
✅ Friction prevents sliding on flat ground
✅ Bouncing works with high restitution
✅ Raycasting returns correct hits
```

---

## 🎬 PHASE 13: ANIMATION SYSTEM
**Duration**: 7-9 days | **Blog Post**: "Animation Systems: From Sprite Sheets to State Machines"

### Subtasks

- [ ] **Keyframe animator**
  - Store keyframes (sprite index + time)
  - Interpolate between keyframes
  - Loop or play-once mode

- [ ] **Animation clip**
  - `class AnimationClip`
    - Vector of keyframes
    - Duration
    - Loop flag
    - Play rate (speed multiplier)
    - Methods: addKeyframe(), getDuration()

- [ ] **Sprite animation player**
  - `class SpriteAnimator : Component`
    - Current clip
    - Current time
    - Is playing
    - Methods: play(clipId), pause(), stop(), setFrame()
    - Updates SpriteComponent's sprite index each frame

- [ ] **State machine basics**
  - `class AnimationStateMachine`
    - States: idle, run, jump, attack, etc.
    - Transitions: jump → run on landing
    - Current state
    - Methods: setState(), update()
    - Each state has animation clip

- [ ] **Blend trees (optional for Phase 13)**
  - Skip initially (can add later)
  - Just state machine is enough

- [ ] **Timeline system**
  - Play multiple animations simultaneously
  - Synchronize to timeline
  - Useful for cutscenes

- [ ] **Animation events**
  - Trigger at specific frame (e.g., "footstep" at frame 5)
  - Emit AnimationEventFired event
  - Gameplay can listen (e.g., play sound on footstep)

- [ ] **Test: Animated sprite**
  - Create 4-frame walk animation (left, forward, right, back)
  - Play animation in loop
  - Transition to jump animation on input
  - Verify sprite updates frame by frame

### 🎨 Visual Milestones

**After Phase 13:**
```
Frame 0:    Frame 5:    Frame 10:   Frame 15:
┌────────┐ ┌────────┐ ┌────────┐ ┌────────┐
│ ║ ║ ║  │ │ ║ ║ ║  │ │ ║ ║ ║  │ │ ║ ║ ║  │
│ ║ ║ ║  │ │ ║ ║ ║  │ │ ║ ║ ║  │ │ ║ ║ ║  │
│ ╔═╗    │ │    ╚═╝ │ │ ╔═╗    │ │    ╚═╝ │  (walk animation looping)
│ ╚═╝    │ │ ╔═╗    │ │ ╚═╝    │ │ ╔═╗    │
└────────┘ └────────┘ └────────┘ └────────┘

State transitions:
IDLE → RUN (when moving)
RUN → JUMP (when jumping)
JUMP → FALL (when falling)
FALL → LAND → IDLE
```

### ✔️ Validation Criteria

```
✅ Animation plays through all frames
✅ Loop works (frame 0 after last frame)
✅ State transitions smooth
✅ Animation events fire at correct times
✅ Play rate/speed changes work
```

---

## 🔊 PHASE 14: AUDIO SYSTEM
**Duration**: 6-8 days | **Blog Post**: "Custom Audio Systems: Low-Level Audio Processing"

### Subtasks

- [ ] **WAV file loader**
  - Parse RIFF header
  - Extract fmt chunk (sample rate, channels, bit depth)
  - Extract data chunk (PCM samples)
  - Validate format (16-bit PCM, mono/stereo)

- [ ] **Audio buffer management**
  - `class AudioBuffer`
    - PCM samples (short[] array)
    - Sample rate (44100 Hz typical)
    - Channels (1=mono, 2=stereo)
    - Duration in seconds

- [ ] **Audio mixer (multi-channel)**
  - `class AudioMixer`
    - 16 audio channels
    - Each channel plays an audio clip independently
    - Mix output: sum all channel samples (with clipping)

- [ ] **Audio playback (one-shot + looping)**
  - `play(audioId, looping=false) → channelId`
  - Returns channel ID for control
  - `stop(channelId)`
  - `pause(channelId)`
  - `resume(channelId)`

- [ ] **Volume control**
  - Master volume (global)
  - Per-channel volume
  - Fade in/out over time (for smooth transitions)

- [ ] **Spatial audio (2D panning)**
  - Pan left/right based on entity position
  - Entity far left → pan left, right → pan right
  - Camera center used as reference

- [ ] **Audio caching**
  - `class AudioManager` (singleton)
    - Load WAV once, reuse
    - Cache in memory (for games < 50 MB audio)

- [ ] **Test: Play sounds**
  - Load 3 WAV files (jump, land, collect)
  - Play on game events
  - Test looping background music
  - Test volume control

### 🎨 Visual Milestones

**After Phase 14:**
```
Event → Sound playback:
[Player Jumps] → plays jump.wav
[Collectible Grabbed] → plays coin.wav (looping: no)
[Background Music] → plays bgm.wav (looping: yes)

Mixer output:
Channel 0: [╜╔═══╗] (jump, one-shot)
Channel 1: [╜═════════════════════] (bgm, looping)
Channel 2: [╜╔═╗] (coin, one-shot)
Mix:       [╜███╔═╗═══╗══════════]  → speakers
```

### ✔️ Validation Criteria

```
✅ WAV files load without crash
✅ Audio plays through speakers
✅ Multiple sounds play simultaneously
✅ Looping audio repeats correctly
✅ Volume control changes audible output
✅ Spatial panning works (pan based on position)
```

---

## 📦 PHASE 15: ASSET MANAGEMENT
**Duration**: 5-7 days | **Blog Post**: "Resource Management: Pooling and Caching Strategies"

### Subtasks

- [ ] **Asset manager**
  - `class AssetManager` (singleton)
    - Load/cache assets
    - Reference counting
    - Cleanup on demand

- [ ] **Resource pooling**
  - Pool of textures, audio clips, sprites, etc.
  - Reuse loaded assets instead of reloading
  - Track usage count per asset

- [ ] **Texture caching**
  - Load texture once per unique path
  - Subsequent requests return cached texture
  - Free texture when reference count = 0

- [ ] **Audio caching**
  - Load WAV once per path
  - Reuse for multiple play() calls
  - Keep in memory (< 50 MB total)

- [ ] **Prefab system (entity templates)**
  - `class Prefab`
    - Template of entity with components
    - Load from file (JSON or binary)
    - Instantiate prefabs to spawn entities
  - Example: "enemy_zombie_prefab" spawns complete zombie entity

- [ ] **Asset hot-reload (dev mode)**
  - Watch asset files for changes
  - Reload modified assets without restart
  - Useful for iteration (change sprite, reload)
  - Only in dev builds

- [ ] **Test: Asset loading and pooling**
  - Load 10 sprites from 5 unique files
  - Verify 5 textures in cache (not 10)
  - Free some, verify reference counting
  - Instantiate prefab 100 times, verify fast

### 🎨 Visual Milestones

**After Phase 15:**
```
Asset Cache:
- player_idle.png (refcount: 5)
- enemy_walk.png (refcount: 3)
- coin.png (refcount: 10)
- jump.wav (refcount: 2)
- bgm.wav (refcount: 1)

Prefabs:
- Player prefab → spawns with (Sprite, Transform, Physics, Animator)
- Enemy prefab → spawns with (Sprite, Transform, Physics, Behavior)
- Coin prefab → spawns with (Sprite, Transform, Collider)

(Instantiate Player prefab 50 times, uses 1 texture + 1 audio clip, huge memory savings)
```

### ✔️ Validation Criteria

```
✅ Loading same asset twice uses cache (1 copy in VRAM)
✅ Hot-reload updates sprite without restart (dev mode)
✅ Prefabs instantiate quickly (< 1ms for 100)
✅ Reference counting accurate
✅ No memory leaks (freed on unload)
```

---

## 🎮 PHASE 16: LEVEL EDITOR ⭐ **MAJOR FEATURE**
**Duration**: 10-12 days | **Blog Post**: "Building In-Engine Editors: From ImGui to Professional Tools"

This is a complex phase. Break it into sub-phases if needed.

### Subtasks

- [ ] **ImGui integration**
  - Integrate ImGui into engine
  - Render ImGui on top of game world
  - Mouse/keyboard input to ImGui
  - Toggle ImGui with debug key

- [ ] **Editor mode toggle**
  - F1 key: switch between Play and Edit mode
  - In Edit mode: pause physics, show ImGui UI
  - In Play mode: run normally, hide UI
  - Smooth transition (fade effect optional)

- [ ] **Tilemap editor**
  - Grid display (256x224 with 16x16 tiles)
  - Paint tiles on grid (click to place, drag to fill)
  - Tileset selector (choose which tile to paint)
  - Undo/redo for tile painting
  - Layer system (background, collision, foreground)

- [ ] **Entity placement**
  - Prefab selector in UI (list all prefabs)
  - Drag prefab onto level to spawn
  - Delete entity (select + delete key)
  - Move entity (select + arrow keys or mouse drag)
  - Clone entity (Ctrl+D)

- [ ] **Property inspector**
  - Select entity to edit properties
  - Auto-expose component members to UI
  - Edit position, rotation, scale
  - Edit color, physics parameters, animation clip
  - Reflect C++ types to ImGui widgets

- [ ] **Undo/redo system**
  - Command pattern for all editor actions
  - Store command history
  - Undo (Ctrl+Z), Redo (Ctrl+Y)
  - Max 100 commands in history

- [ ] **Save/load levels**
  - Save current level to file (binary format)
  - Load level from file
  - File format: entity list + tilemap data
  - Example: "levels/level_01.bin"

- [ ] **Multi-layer support**
  - Background layer (layer 0)
  - Collision layer (layer 5, invisible in play mode)
  - Foreground layer (layer 10)
  - Toggle layer visibility in editor

- [ ] **Gizmos (move/rotate tools)**
  - Select entity → show gizmo
  - Red arrow: drag to move X
  - Green arrow: drag to move Y
  - Blue circle: drag to rotate
  - White box: scale

- [ ] **Grid visualization**
  - Show 16x16 grid
  - Grid color customizable
  - Toggle grid on/off
  - Snap to grid (optional)

- [ ] **Entity selection and highlighting**
  - Click entity to select
  - Selected entity: green outline
  - Show entity name in properties panel
  - Multiple selection (Shift+click)

- [ ] **Test: Level editor workflow**
  - Create level with 10 tiles + 5 enemies + 1 player
  - Save level
  - Load level in play mode
  - Verify entities spawned correctly
  - Load in edit mode, modify, save again

### 🎨 Visual Milestones

**After Phase 16:**
```
EDIT MODE:
┌───────────────────────────────────────┐
│                                       │
│  [Game viewport with grid overlay]    │
│  ██████████████████ ← tiles           │
│  ██╔════╝██════════ ← entities (outlined)
│  ██║ O  ║██════════ ← property inspector on right
│  ██╚════╝██════════                   │
│  ██████████████████ ← ImGui panel on right
│                                       │
│  [Properties]                         │
│  Position: (100, 100)                 │
│  Rotation: 0°                         │
│  Scale: 1.0                           │
│  [Tileset picker]                     │
│  [Entity prefab selector]             │
└───────────────────────────────────────┘

PLAY MODE (F1 toggle):
┌───────────────────────────────────────┐
│                                       │
│  [Game viewport, no UI]               │
│  ██████████████████                   │
│  ██ ██ ██ ██ ██ ██                    │
│  ██ ██ ██ ██ ██ ██                    │
│  ██ ██ ██ ██ ██ ██                    │
│  ████████████████████                 │
│                                       │
│  FPS: 120                             │
└───────────────────────────────────────┘
```

### ✔️ Validation Criteria

```
✅ Level editor opens without crash
✅ Paint 10x10 tilemap, see tiles render
✅ Place 5 entities, see them appear
✅ Edit entity properties, changes take effect
✅ Save level (file appears on disk)
✅ Load level, entities spawn in correct positions
✅ Undo/redo works (paint tile, undo, tile disappears)
✅ Toggle F1, switch between edit/play seamlessly
✅ Multiple layers don't interfere with rendering
```

---

## 🔌 PHASE 17: EXTENSIBILITY FRAMEWORK
**Duration**: 6-8 days | **Blog Post**: "Designing Extensible Engines: Plugin Systems and Reflection"

### Subtasks

- [ ] **Custom component system**
  - User can define custom components
  - No modification to engine code needed
  - Example: `struct HealthComponent { int hp, maxHp; }`
  - Register component: `REGISTER_COMPONENT(HealthComponent);`

- [ ] **Custom system registration**
  - User can define custom systems
  - Example: `class HealthSystem : public ISystem { ... };`
  - Register: `engine.registerSystem<HealthSystem>();`
  - System runs with other systems each frame

- [ ] **Scriptable behavior (C++ only)**
  - No Lua/scripting language
  - Users write C++ behavior classes
  - `class EnemyBehavior` inherits from `Behavior`
  - Attach behavior to entity: `entity.addComponent<EnemyBehavior>()`

- [ ] **Property reflection**
  - Expose component members to property inspector (ImGui)
  - Mark members: `REFLECT() float x;`
  - Auto-generate UI sliders/inputs
  - No manual UI code needed

- [ ] **Plugin architecture (future-proof)**
  - Design for plugins (don't implement yet)
  - Systems can be hot-loaded (not implemented)
  - Prepare structure for DLL plugins later

- [ ] **Custom asset types**
  - Define custom asset format (e.g., level config)
  - Register loader: `assetManager.registerLoader<MyAssetType>()`
  - Load custom assets via asset manager

- [ ] **Test: Custom components and systems**
  - Create custom `HealthComponent`
  - Create custom `HealthSystem` that decreases HP over time
  - Register both
  - Spawn entity with health, verify HP decreases

### 🎨 Visual Milestones

**After Phase 17:**
```
User code (completely separate from engine):
────────────────────────────────────────────
// my_game.cpp
struct HealthComponent {
    REFLECT()
    int health = 100;
    int maxHealth = 100;
};

class HealthSystem : public ISystem {
    void update(float dt, EntityManager& em) {
        // Decrease health of damaged entities
    }
};

int main() {
    Engine engine;
    engine.registerComponent<HealthComponent>();
    engine.registerSystem<HealthSystem>();
    
    Entity player = engine.createEntity();
    player.addComponent<HealthComponent>();
    
    engine.run(); // HealthSystem runs automatically
}
────────────────────────────────────────────

(Editor shows HealthComponent properties for player)
```

### ✔️ Validation Criteria

```
✅ Custom component registers without engine modification
✅ Custom system runs automatically
✅ Property reflection shows HealthComponent.health in ImGui
✅ Edit health value in editor, entity responds
✅ Multiple custom systems coexist
```

---

## 🎮 PHASE 18: EXAMPLES & POLISH
**Duration**: 8-10 days | **Blog Post**: "From Engine to Game: Three Complete Examples"

### Subtasks

**Example 1: Pong**
- [ ] 2 paddles (player + AI)
- [ ] Ball with physics (bounce, gravity)
- [ ] Score tracking
- [ ] Win condition (first to 10 points)
- [ ] Time: 3-4 days

**Example 2: Simple Platformer**
- [ ] One level (level editor showcase)
- [ ] Player character (walk, jump)
- [ ] Enemies (patrol, jump toward player)
- [ ] Collectibles (coins, health pickups)
- [ ] Level complete condition
- [ ] Time: 5-7 days

**Example 3: Space Shooter**
- [ ] Player ship (WASD move, SPACE shoot)
- [ ] Enemies (spawn waves, different types)
- [ ] Bullets (simple physics)
- [ ] Particles (explosion effects)
- [ ] Score/lives system
- [ ] Time: 5-7 days

### Performance Benchmarks

- [ ] Profile each example
- [ ] Log: FPS, memory usage, draw call count
- [ ] Optimize bottlenecks

### Profiling Guide

- [ ] Document how to profile with perf/nsight
- [ ] Identify hot functions
- [ ] Optimization opportunities

### Release Build Optimizations

- [ ] Enable `-O3 -flto` (link-time optimization)
- [ ] Test release build performance
- [ ] Document optimization results

### 🎨 Visual Milestones

**After Phase 18:**
```
PONG:
┌──────────────────────────────┐
│  │                        │  │
│  │ o                      │  │ (ball bounces, paddles move)
│  │                        │  │
│  Player: 5    AI: 8           │
└──────────────────────────────┘

PLATFORMER:
┌──────────────────────────────┐
│                              │
│     ║ (player)               │
│    ═╧═                       │
│  ════╗    [enemy]   ○        │
│      ║════════════════       │
│      ║                       │
└──────────────────────────────┘

SPACE SHOOTER:
┌──────────────────────────────┐
│  ★ ★   ★ ★  ★               │
│    ★      ★                  │
│       Δ (player ship)         │
│      | | (bullets)           │
│                              │
│  Score: 1250   Lives: 3      │
└──────────────────────────────┘

(All 3 run at 120 FPS smoothly)
```

### ✔️ Validation Criteria

```
✅ Pong: 2 players, AI works, score tracking
✅ Platformer: enemies move, collectibles spawned, level load/save
✅ Space Shooter: waves spawn, bullets work, particles visible
✅ All examples: FPS > 100, smooth gameplay
✅ Profiling: FPS > 120 in all examples
```

---

## 📚 PHASE 19: DOCUMENTATION FINAL
**Duration**: 7-10 days | **Blog Post**: "Complete Game Engine Documentation: Best Practices"

### Subtasks

- [ ] **API reference**
  - Function signatures with descriptions
  - Parameter explanations
  - Return values
  - Example usage

- [ ] **Architecture deep-dive**
  - ECS design rationale
  - Renderer pipeline explanation
  - Physics solver details
  - Audio system design

- [ ] **Beginner tutorial ("Your First Game")**
  - Step-by-step: create empty project
  - Spawn player sprite
  - Add keyboard input
  - Add gravity/jumping
  - Estimated time: 30 minutes for reader

- [ ] **Advanced tutorials**
  - Custom physics constraints
  - Extend with custom systems
  - Optimize renderer for 10k sprites
  - Custom editor features

- [ ] **Troubleshooting guide**
  - Common errors and solutions
  - Performance issues and fixes
  - Build/compilation problems

- [ ] **Performance optimization tips**
  - Profiling techniques
  - Common bottlenecks
  - Memory management best practices
  - Batching strategies

### 🎨 Visual Milestones

**After Phase 19:**
```
Documentation structure:
docs/
├── API/
│   ├── Engine.md
│   ├── EntityManager.md
│   ├── Renderer.md
│   └── PhysicsSystem.md
├── Tutorials/
│   ├── getting-started.md
│   ├── first-game.md
│   ├── custom-systems.md
│   └── advanced-physics.md
├── Architecture/
│   ├── ECS-design.md
│   ├── Renderer-pipeline.md
│   └── Physics-solver.md
└── Troubleshooting/
    ├── Compilation-errors.md
    └── Performance-issues.md

(Comprehensive, user-friendly, searchable)
```

### ✔️ Validation Criteria

```
✅ API docs cover all public classes/methods
✅ Beginner tutorial takes < 1 hour
✅ Advanced tutorials use real examples
✅ Troubleshooting solves common issues
✅ Performance guide improves FPS by 10-20% for users
```

---

## 🌐 PHASE 20: WEBGL SUPPORT (OPTIONAL, Future)
**Duration**: 10-14 days | **Blog Post**: "Porting C++ Game Engine to WebGL with Emscripten"

*Optional phase. Can be skipped if desktop-only is desired.*

### Subtasks

- [ ] **Emscripten setup**
  - Install Emscripten SDK
  - Configure CMakeLists.txt for WASM builds

- [ ] **SDL2 → browser adaptation**
  - SDL2 works on web (Emscripten provides polyfill)
  - Canvas drawing instead of window
  - Web input (keyboard/mouse from browser)

- [ ] **OpenGL → WebGL compatibility**
  - GLSL 3.3 → GLSL ES 3.0 translation (mostly compatible)
  - Some extensions unavailable on web
  - Use compatibility mode

- [ ] **Build system for WASM**
  - Separate CMake configuration
  - JavaScript runtime stubs
  - WASM binary (*.wasm) size optimization

- [ ] **Example playable in browser**
  - Pong example compiled to WASM
  - Play in browser (no installation needed)
  - Share link with others

### 🎨 Visual Milestones

**After Phase 20:**
```
Desktop (native):
$ ./snes-engine
[Runs at 120 FPS natively]

Web (WebGL):
Browser: https://user.github.io/snes-engine/pong
[Runs in browser, WASM, 120 FPS]
```

### ✔️ Validation Criteria

```
✅ WASM binary compiles (< 5 MB)
✅ Plays in modern browser (Chrome, Firefox, Safari)
✅ FPS > 60 in browser
✅ Input responsive
✅ Assets load correctly
```

---

## 📊 ESTIMATED TIMELINE

| Phase | Duration | Cumulative | Status |
|-------|----------|-----------|--------|
| 0 | 4-5d | ~1 week | ✅ Done |
| 1 | 5-7d | ~2.5 weeks | 🔄 In Progress (Logger done, Clock TODO) |
| 2 | 3-4d | ~3.5 weeks | Math |
| 3 | 6-8d | ~5 weeks | Renderer |
| 4 | 5-6d | ~6.5 weeks | Sprites |
| 5 | 5-7d | ~8 weeks | Pixelization |
| 6 | 4-5d | ~9 weeks | Input |
| 7 | 4-5d | ~10 weeks | Events |
| 8 | 8-10d | ~12 weeks | **ECS** |
| 9 | 4-5d | ~13 weeks | Hierarchy |
| 10 | 5-6d | ~14.5 weeks | Sprites Batch |
| 11 | 8-10d | ~16.5 weeks | Physics Detection |
| 12 | 6-8d | ~18 weeks | Physics Resolution |
| 13 | 7-9d | ~20 weeks | Animation |
| 14 | 6-8d | ~22 weeks | Audio |
| 15 | 5-7d | ~23.5 weeks | Assets |
| 16 | 10-12d | ~26 weeks | **Editor** |
| 17 | 6-8d | ~27.5 weeks | Extensibility |
| 18 | 8-10d | ~29 weeks | Examples |
| 19 | 7-10d | ~31 weeks | Docs |
| 20 | 10-14d | ~34 weeks | WebGL (opt) |

**Total**: ~32 weeks full-time (~8 months)
or ~64 weeks part-time 20h/week (~15 months)

---

## ✅ FINAL VALIDATION CHECKLIST

Before each phase is "complete":

- [ ] Code compiles without warnings
- [ ] No memory leaks (valgrind/ASAN clean)
- [ ] Visual/functional milestone achieved
- [ ] All test cases pass
- [ ] Performance target met (120 FPS or better)
- [ ] Blog post written
- [ ] Git commit with descriptive message
- [ ] claude.md updated if needed

---

## 🚀 NEXT IMMEDIATE STEPS

1. ✅ Phase 0: Create folders + CMakeLists.txt
2. 🔄 Phase 1: Core loop (window, logger done - need Clock/FPS)
3. ⬚ Phase 2: Math library
4. ... continue through Phase 20

### Phase 1 Remaining:
- [ ] Clock system (delta time, FPS counter)
- [ ] Fixed timestep (120 FPS lock)

**Ready to code!** 🎮

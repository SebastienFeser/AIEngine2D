# =============================================================================
# AIEngine2D - Source CMakeLists.txt
# =============================================================================

# --- Math Library (header-only for now) ---
add_library(engine_math INTERFACE)
target_include_directories(engine_math INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/math)

# --- Core Library ---
add_library(engine_core STATIC
    core/placeholder.cpp
)
target_link_libraries(engine_core PUBLIC engine_math)

# --- Renderer Library ---
add_library(engine_renderer STATIC
    renderer/placeholder.cpp
)
target_link_libraries(engine_renderer
    PUBLIC engine_core
    PUBLIC OpenGL::GL
    PUBLIC $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    PUBLIC imgui::imgui
)

# --- Physics Library ---
add_library(engine_physics STATIC
    physics/placeholder.cpp
)
target_link_libraries(engine_physics PUBLIC engine_core)

# --- Audio Library ---
add_library(engine_audio STATIC
    audio/placeholder.cpp
)
target_link_libraries(engine_audio PUBLIC engine_core)

# --- Input Library ---
add_library(engine_input STATIC
    input/placeholder.cpp
)
target_link_libraries(engine_input
    PUBLIC engine_core
    PUBLIC $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

# --- Assets Library ---
add_library(engine_assets STATIC
    assets/placeholder.cpp
)
target_link_libraries(engine_assets PUBLIC engine_core engine_renderer)

# --- Animation Library ---
add_library(engine_animation STATIC
    animation/placeholder.cpp
)
target_link_libraries(engine_animation PUBLIC engine_core)

# --- Editor Library ---
add_library(engine_editor STATIC
    editor/placeholder.cpp
)
target_link_libraries(engine_editor
    PUBLIC engine_core
    PUBLIC engine_renderer
    PUBLIC imgui::imgui
)

# --- Main Executable (Test) ---
add_executable(AIEngine2D WIN32
    main.cpp
)

target_link_libraries(AIEngine2D
    PRIVATE engine_core
    PRIVATE engine_renderer
    PRIVATE engine_physics
    PRIVATE engine_audio
    PRIVATE engine_input
    PRIVATE engine_assets
    PRIVATE engine_animation
    PRIVATE engine_editor
    PRIVATE OpenGL::GL
    PRIVATE $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
)

# Export include directories
target_include_directories(AIEngine2D PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

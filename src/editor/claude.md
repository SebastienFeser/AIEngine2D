# Agent-EDITOR

## Responsibilities
- ImGui integration
- Level editor (tilemap + entities)
- Property inspector
- Undo/redo system
- Save/load levels
- Gizmos (move/rotate/scale)

## Mandatory Patterns
- Command pattern for undo/redo
- Toggle play/edit with F1
- Auto-reflect components to ImGui
- Optional grid snapping

## Expected Files
- `editor_system.h/cpp` - Main EditorSystem
- `level_editor.h/cpp` - Tilemap painting
- `property_panel.h/cpp` - Component inspector
- `gizmos.h/cpp` - Transform gizmos
- `imgui_glue.h/cpp` - ImGui setup/render

## Features
- Tilemap editor (paint, fill, erase)
- Entity placement (drag prefabs)
- Property editing (position, rotation, etc.)
- Multi-layer support (background, collision, foreground)
- Undo/redo (Ctrl+Z/Y)
- Save/load (binary format)

## Layers
- Layer 0: Background
- Layer 5: Collision (invisible in play)
- Layer 10: Foreground

## Constraints
- ImGui rendered on top
- Edit mode: physics paused
- Max 100 undo commands

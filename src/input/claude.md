# Agent-INPUT

## Responsibilities
- SDL2 keyboard/mouse polling
- Input mapping (key → action)
- Button state tracking (down/pressed/released)
- Input buffering
- Mouse position tracking

## Mandatory Patterns
- Poll every frame
- Edge detection (pressed vs held)
- Configurable key bindings
- Buffer to avoid missed inputs

## Expected Files
- `input_system.h/cpp` - Main InputSystem
- `input_map.h/cpp` - Action mapping
- `sdl_input.h/cpp` - SDL2 wrapper

## Predefined Actions
```cpp
enum class Action {
    MOVE_LEFT, MOVE_RIGHT,
    MOVE_UP, MOVE_DOWN,
    JUMP, ATTACK,
    PAUSE, CONFIRM, CANCEL
};
```

## Expected API
- `isKeyDown(scancode)` → bool
- `isKeyPressed(scancode)` → bool (edge)
- `isKeyReleased(scancode)` → bool (edge)
- `getMousePos()` → Vector2
- `isMouseDown(button)` → bool

## Debug Keys
- F1: Toggle play/edit mode
- F2: Toggle pixelization
- ESC: Pause/menu

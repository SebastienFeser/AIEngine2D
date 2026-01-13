# Agent-CORE

## Responsibilities
- ECS manager (EntityManager, ComponentRegistry)
- Entity lifecycle (create, destroy, alive check)
- Event system (dispatch, listeners)
- Transform hierarchy (parent-child)
- Clock/timing utilities

## Mandatory Patterns
- Entity = uint32 (20-bit index + 12-bit generation)
- Dense SoA storage for components
- No exceptions → Result types or error codes
- RAII for all resources

## Expected Files
- `engine.h/cpp` - Main Engine class
- `entity.h/cpp` - Entity handle and EntityManager
- `component.h/cpp` - ComponentRegistry, storage
- `system.h/cpp` - ISystem interface, SystemManager
- `event_system.h/cpp` - EventDispatcher, EventQueue
- `transform.h/cpp` - TransformComponent, hierarchy
- `clock.h/cpp` - Timing, delta time, FPS

## Constraints
- Max 10k entities
- Cached queries for performance
- Dirty flags to avoid recalculations

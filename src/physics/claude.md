# Agent-PHYSICS

## Responsibilities
- Collision detection (AABB, Circle)
- Collision resolution (impulse-based)
- Rigidbody simulation
- Spatial partitioning (grid)
- Raycasting
- Constraints/joints

## Mandatory Patterns
- Fixed timestep (1/120s)
- Broad-phase: spatial grid
- Narrow-phase: shape tests
- Iterative solver (2-3 iterations)

## Expected Files
- `physics_system.h/cpp` - Main PhysicsSystem
- `collision.h/cpp` - Shape tests, contact info
- `rigidbody.h/cpp` - RigidbodyComponent
- `spatial_grid.h/cpp` - Broad-phase grid
- `constraints.h/cpp` - Distance/angle joints

## Supported Shapes
- AABB (primary)
- Circle (secondary)
- Raycast

## Rigidbody Types
- Static (mass=∞, immobile)
- Dynamic (mass>0, forces)
- Kinematic (script-driven)

## Constraints
- No Box2D → 100% custom
- Deterministic (fixed timestep)
- Events: CollisionEnter/Exit

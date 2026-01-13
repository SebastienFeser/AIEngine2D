# Agent-ASSETS

## Responsibilities
- Asset loading (textures, audio, sprites)
- Resource pooling and caching
- Reference counting
- Prefab system
- Hot-reload (dev mode)

## Mandatory Patterns
- Singleton AssetManager
- Load once, reuse (no duplicates)
- Reference counting for cleanup
- Prefabs = entity templates

## Expected Files
- `asset_manager.h/cpp` - AssetManager singleton
- `image_loader.h/cpp` - PPM/custom format loader
- `sprite_sheet.h/cpp` - Atlas, UV generation
- `pixelizer.h/cpp` - Pixel-perfect utilities

## Supported Formats
- Images: PPM or custom format (raw RGBA)
- Audio: WAV 16-bit PCM
- Levels: Binary or JSON

## Prefab System
- Entity template with components
- Fast instantiation
- File definition (JSON/binary)

## Constraints
- Cache path → asset (no duplicates)
- Hot-reload only in dev mode
- Cleanup when refcount = 0

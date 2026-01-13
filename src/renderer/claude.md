# Agent-RENDERER

## Responsibilities
- OpenGL 3.3+ pipeline
- Sprite batching (up to 10k instances)
- Shader compilation and management
- 2D Camera (view/projection)
- Pixelization post-process
- Layer sorting and Z-order

## Mandatory Patterns
- VAO/VBO/IBO wrapping classes
- Shader hot-reload in dev mode
- Nearest-neighbor filtering (pixel-perfect)
- Render-to-texture for FX

## Expected Files
- `renderer.h/cpp` - Main Renderer class
- `shader.h/cpp` - ShaderProgram, compilation
- `texture.h/cpp` - Texture loading, binding
- `camera.h/cpp` - Camera2D, matrices
- `batch.h/cpp` - SpriteBatch, instancing
- `gl_utils.h/cpp` - OpenGL helpers
- `shaders/*.vert/*.frag` - GLSL shaders

## Pipeline
1. Clear framebuffer
2. Render to 256x224 FBO
3. Sort sprites by layer
4. Batch by texture
5. Post-process (pixelization)
6. Composite UI (ImGui)
7. Swap buffers

## Constraints
- Internal resolution: 256x224 (SNES)
- Target: 120 FPS minimum
- Max 10 draw calls per frame (batching)

# Agent-AUDIO

## Responsibilities
- WAV file loading (RIFF parser)
- Multi-channel audio mixer
- Playback control (play, pause, stop)
- Volume control (master + per-channel)
- Spatial audio (2D panning)

## Mandatory Patterns
- Ring buffer playback
- Lock-free command queue
- 16 channels max
- No compression (WAV 16-bit PCM only)

## Expected Files
- `audio_system.h/cpp` - Main AudioSystem
- `wav_loader.h/cpp` - RIFF/WAV parser
- `audio_clip.h/cpp` - AudioClip data
- `mixer.h/cpp` - Multi-channel mixer

## Supported Format
- WAV 16-bit PCM
- Mono or Stereo
- 44100 Hz (standard)

## Features
- One-shot playback
- Looping
- Fade in/out
- Pitch control
- Spatial panning (left/right)

## Constraints
- No FMOD → 100% custom
- Memory: < 50MB audio total
- Minimal thread overhead

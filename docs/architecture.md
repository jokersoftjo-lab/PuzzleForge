# PuzzleForge Architecture

PuzzleForge is organized as a desktop editor and runtime engine hybrid. The current implementation establishes the Phase 1 and Phase 2 foundations:

- `engine/core` owns the application lifecycle and module registry.
- `editor/windows` contains the Qt `QMainWindow` editor shell.
- `editor/assetbrowser`, `editor/timeline`, and `editor/viewport` provide dockable editor panels.
- `media/decoder` defines the FFmpeg-facing video decoder seam. It currently runs in stub mode when FFmpeg is not linked, so UI and puzzle workflows can be developed without blocking on third-party binaries.
- `puzzle/pieces` and `puzzle/timeline` contain runtime data models for generated puzzle pieces and timeline serialization.

## Implemented workflow

1. Start the editor through `MainEditorWindow`.
2. Import a media file from the File menu or toolbar.
3. Probe the clip through `FFmpegVideoDecoder`.
4. Generate a 4x3 grid of puzzle pieces through `PuzzleGenerator`.
5. Display pieces on the central puzzle board and timeline dock.
6. Save or load `.pforge.json` project files that preserve timeline and puzzle metadata.

## Next milestones

- Replace the FFmpeg stub with linked libavformat/libavcodec frame extraction.
- Persist visual thumbnails in the project cache.
- Promote puzzle-board item movement back into `TimelineModel` for full drag/drop placement saves.
- Add OpenGL texture-backed playback and synchronized audio waveforms.
- Split plugin, AI, online, and renderer modules into loadable service interfaces.

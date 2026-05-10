#pragma once

#include "media/video/MediaTypes.h"

#include <QString>

namespace PuzzleForge::Media {

class FFmpegVideoDecoder {
public:
  [[nodiscard]] bool isAvailable() const noexcept;
  [[nodiscard]] MediaClip probeClip(const QString &filePath) const;
  [[nodiscard]] QVector<VideoFrame>
  extractPreviewFrames(const QString &filePath, int frameCount) const;
};

} // namespace PuzzleForge::Media

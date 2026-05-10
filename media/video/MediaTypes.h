#pragma once

#include <QImage>
#include <QString>
#include <QVector>

namespace PuzzleForge::Media {

struct VideoFrame {
  int frameIndex = 0;
  double timestampSeconds = 0.0;
  QImage thumbnail;
};

struct MediaClip {
  QString sourcePath;
  double durationSeconds = 0.0;
  int width = 0;
  int height = 0;
  QVector<VideoFrame> previewFrames;
};

} // namespace PuzzleForge::Media

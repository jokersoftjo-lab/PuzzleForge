#include "FFmpegVideoDecoder.h"

#include <QColor>
#include <QFileInfo>
#include <QPainter>

namespace PuzzleForge::Media {

bool FFmpegVideoDecoder::isAvailable() const noexcept {
#ifdef PUZZLEFORGE_HAS_FFMPEG
  return true;
#else
  return false;
#endif
}

MediaClip FFmpegVideoDecoder::probeClip(const QString &filePath) const {
  MediaClip clip;
  clip.sourcePath = filePath;
  clip.durationSeconds = QFileInfo(filePath).exists() ? 60.0 : 0.0;
  clip.width = 1920;
  clip.height = 1080;
  clip.previewFrames = extractPreviewFrames(filePath, 8);
  return clip;
}

QVector<VideoFrame>
FFmpegVideoDecoder::extractPreviewFrames(const QString &filePath,
                                         int frameCount) const {
  QVector<VideoFrame> frames;
  frames.reserve(frameCount);

  const QString label = QFileInfo(filePath).fileName().isEmpty()
                            ? QStringLiteral("Unloaded Media")
                            : QFileInfo(filePath).fileName();

  for (int index = 0; index < frameCount; ++index) {
    QImage image(180, 100, QImage::Format_RGBA8888);
    image.fill(QColor::fromHsv((index * 36) % 360, 160, 170));

    QPainter painter(&image);
    painter.setPen(Qt::white);
    painter.drawText(image.rect().adjusted(8, 8, -8, -8),
                     Qt::AlignCenter | Qt::TextWordWrap,
                     QStringLiteral("%1\nFrame %2").arg(label).arg(index + 1));

    frames.push_back(VideoFrame{index, index / 24.0, image});
  }

  return frames;
}

} // namespace PuzzleForge::Media

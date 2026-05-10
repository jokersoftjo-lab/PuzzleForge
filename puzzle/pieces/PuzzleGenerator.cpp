#include "PuzzleGenerator.h"

namespace PuzzleForge::Puzzle {

QVector<PuzzlePiece>
PuzzleGenerator::generateGridPieces(const Media::MediaClip &clip,
                                    QSize gridSize) const {
  QVector<PuzzlePiece> pieces;
  if (gridSize.width() <= 0 || gridSize.height() <= 0 ||
      clip.previewFrames.isEmpty()) {
    return pieces;
  }

  const int pieceCount = gridSize.width() * gridSize.height();
  pieces.reserve(pieceCount);

  for (int index = 0; index < pieceCount; ++index) {
    const int x = index % gridSize.width();
    const int y = index / gridSize.width();
    const auto &frame =
        clip.previewFrames.at(index % clip.previewFrames.size());
    const double segmentLength =
        clip.durationSeconds > 0.0
            ? clip.durationSeconds / static_cast<double>(pieceCount)
            : 1.0;

    pieces.push_back(PuzzlePiece{
        QStringLiteral("piece_%1").arg(index + 1, 3, 10, QLatin1Char('0')),
        clip.sourcePath,
        TimeRange{index * segmentLength, (index + 1) * segmentLength},
        QPointF{x * 128.0, y * 96.0}, QPixmap::fromImage(frame.thumbnail)});
  }

  return pieces;
}

} // namespace PuzzleForge::Puzzle

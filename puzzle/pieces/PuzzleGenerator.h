#pragma once

#include "media/video/MediaTypes.h"
#include "puzzle/pieces/PuzzlePiece.h"

#include <QSize>
#include <QVector>

namespace PuzzleForge::Puzzle {

class PuzzleGenerator {
public:
  [[nodiscard]] QVector<PuzzlePiece>
  generateGridPieces(const Media::MediaClip &clip, QSize gridSize) const;
};

} // namespace PuzzleForge::Puzzle

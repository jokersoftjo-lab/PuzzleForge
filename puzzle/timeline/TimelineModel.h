#pragma once

#include "puzzle/pieces/PuzzlePiece.h"

#include <QJsonArray>
#include <QVector>

namespace PuzzleForge::Puzzle {

class TimelineModel {
public:
  void setPieces(QVector<PuzzlePiece> pieces);
  void addPiece(const PuzzlePiece &piece);
  void clear();

  [[nodiscard]] const QVector<PuzzlePiece> &pieces() const noexcept;
  [[nodiscard]] QJsonArray toJson() const;
  void fromJson(const QJsonArray &array);

private:
  QVector<PuzzlePiece> m_pieces;
};

} // namespace PuzzleForge::Puzzle

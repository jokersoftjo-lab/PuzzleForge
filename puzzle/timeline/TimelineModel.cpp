#include "TimelineModel.h"

#include <utility>

namespace PuzzleForge::Puzzle {

void TimelineModel::setPieces(QVector<PuzzlePiece> pieces) {
  m_pieces = std::move(pieces);
}

void TimelineModel::addPiece(const PuzzlePiece &piece) {
  m_pieces.push_back(piece);
}

void TimelineModel::clear() { m_pieces.clear(); }

const QVector<PuzzlePiece> &TimelineModel::pieces() const noexcept {
  return m_pieces;
}

QJsonArray TimelineModel::toJson() const {
  QJsonArray array;
  for (const auto &piece : m_pieces) {
    array.append(piece.toJson());
  }
  return array;
}

void TimelineModel::fromJson(const QJsonArray &array) {
  m_pieces.clear();
  m_pieces.reserve(array.size());

  for (const auto &value : array) {
    if (value.isObject()) {
      m_pieces.push_back(PuzzlePiece::fromJson(value.toObject()));
    }
  }
}

} // namespace PuzzleForge::Puzzle

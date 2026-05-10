#include "PuzzlePiece.h"

#include <QJsonObject>

#include <utility>

namespace PuzzleForge::Puzzle {

PuzzlePiece::PuzzlePiece(QString id, QString sourceMediaPath,
                         TimeRange timeRange, QPointF correctPlacement,
                         QPixmap preview)
    : m_id(std::move(id)), m_sourceMediaPath(std::move(sourceMediaPath)),
      m_timeRange(timeRange), m_correctPlacement(correctPlacement),
      m_currentPlacement(correctPlacement), m_preview(std::move(preview)) {}

const QString &PuzzlePiece::id() const noexcept { return m_id; }

const QString &PuzzlePiece::sourceMediaPath() const noexcept {
  return m_sourceMediaPath;
}

TimeRange PuzzlePiece::timeRange() const noexcept { return m_timeRange; }

QPointF PuzzlePiece::correctPlacement() const noexcept {
  return m_correctPlacement;
}

const QPixmap &PuzzlePiece::preview() const noexcept { return m_preview; }

void PuzzlePiece::setCurrentPlacement(QPointF placement) noexcept {
  m_currentPlacement = placement;
}

QPointF PuzzlePiece::currentPlacement() const noexcept {
  return m_currentPlacement;
}

QJsonObject PuzzlePiece::toJson() const {
  return {{QStringLiteral("id"), m_id},
          {QStringLiteral("sourceMediaPath"), m_sourceMediaPath},
          {QStringLiteral("startSeconds"), m_timeRange.startSeconds},
          {QStringLiteral("endSeconds"), m_timeRange.endSeconds},
          {QStringLiteral("correctX"), m_correctPlacement.x()},
          {QStringLiteral("correctY"), m_correctPlacement.y()},
          {QStringLiteral("currentX"), m_currentPlacement.x()},
          {QStringLiteral("currentY"), m_currentPlacement.y()}};
}

PuzzlePiece PuzzlePiece::fromJson(const QJsonObject &object) {
  PuzzlePiece piece(
      object.value(QStringLiteral("id")).toString(),
      object.value(QStringLiteral("sourceMediaPath")).toString(),
      TimeRange{object.value(QStringLiteral("startSeconds")).toDouble(),
                object.value(QStringLiteral("endSeconds")).toDouble()},
      QPointF{object.value(QStringLiteral("correctX")).toDouble(),
              object.value(QStringLiteral("correctY")).toDouble()},
      {});

  piece.setCurrentPlacement(
      QPointF{object.value(QStringLiteral("currentX")).toDouble(),
              object.value(QStringLiteral("currentY")).toDouble()});

  return piece;
}

} // namespace PuzzleForge::Puzzle

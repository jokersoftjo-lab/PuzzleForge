#pragma once

#include <QJsonObject>
#include <QPixmap>
#include <QPointF>
#include <QString>

namespace PuzzleForge::Puzzle {

struct TimeRange {
  double startSeconds = 0.0;
  double endSeconds = 0.0;
};

class PuzzlePiece {
public:
  PuzzlePiece() = default;
  PuzzlePiece(QString id, QString sourceMediaPath, TimeRange timeRange,
              QPointF correctPlacement, QPixmap preview);

  [[nodiscard]] const QString &id() const noexcept;
  [[nodiscard]] const QString &sourceMediaPath() const noexcept;
  [[nodiscard]] TimeRange timeRange() const noexcept;
  [[nodiscard]] QPointF correctPlacement() const noexcept;
  [[nodiscard]] const QPixmap &preview() const noexcept;

  void setCurrentPlacement(QPointF placement) noexcept;
  [[nodiscard]] QPointF currentPlacement() const noexcept;

  [[nodiscard]] QJsonObject toJson() const;
  static PuzzlePiece fromJson(const QJsonObject &object);

private:
  QString m_id;
  QString m_sourceMediaPath;
  TimeRange m_timeRange;
  QPointF m_correctPlacement;
  QPointF m_currentPlacement;
  QPixmap m_preview;
};

} // namespace PuzzleForge::Puzzle

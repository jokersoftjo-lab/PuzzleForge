#pragma once

#include "puzzle/timeline/TimelineModel.h"

#include <QListWidget>
#include <QWidget>

namespace PuzzleForge::Editor {

class TimelineWidget : public QWidget {
  Q_OBJECT

public:
  explicit TimelineWidget(QWidget *parent = nullptr);
  void setTimeline(const Puzzle::TimelineModel &model);

signals:
  void pieceSelected(const QString &pieceId);

private:
  QListWidget *m_trackList = nullptr;
};

} // namespace PuzzleForge::Editor

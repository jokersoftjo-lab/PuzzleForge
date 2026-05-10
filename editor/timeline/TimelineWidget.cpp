#include "TimelineWidget.h"

#include <QAbstractItemView>
#include <QLabel>
#include <QListWidgetItem>
#include <QVBoxLayout>

namespace PuzzleForge::Editor {

TimelineWidget::TimelineWidget(QWidget *parent)
    : QWidget(parent), m_trackList(new QListWidget(this)) {
  auto *layout = new QVBoxLayout(this);
  layout->setContentsMargins(8, 8, 8, 8);
  layout->addWidget(new QLabel(tr("Puzzle Timeline"), this));
  layout->addWidget(m_trackList);

  m_trackList->setDragDropMode(QAbstractItemView::InternalMove);
  m_trackList->setDefaultDropAction(Qt::MoveAction);

  connect(m_trackList, &QListWidget::itemClicked, this,
          [this](QListWidgetItem *item) {
            emit pieceSelected(item->data(Qt::UserRole).toString());
          });
}

void TimelineWidget::setTimeline(const Puzzle::TimelineModel &model) {
  m_trackList->clear();
  for (const auto &piece : model.pieces()) {
    auto *item =
        new QListWidgetItem(tr("%1  [%2s - %3s]")
                                .arg(piece.id())
                                .arg(piece.timeRange().startSeconds, 0, 'f', 2)
                                .arg(piece.timeRange().endSeconds, 0, 'f', 2),
                            m_trackList);
    item->setData(Qt::UserRole, piece.id());
    item->setIcon(piece.preview());
  }
}

} // namespace PuzzleForge::Editor

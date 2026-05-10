#include "PuzzleBoardWidget.h"

#include <QBrush>
#include <QColor>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPen>

#include <utility>

namespace PuzzleForge::Editor {
namespace {
class MovablePuzzleItem final : public QGraphicsPixmapItem {
public:
  MovablePuzzleItem(QString pieceId, const QPixmap &pixmap)
      : QGraphicsPixmapItem(pixmap), m_pieceId(std::move(pieceId)) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
  }

  [[nodiscard]] const QString &pieceId() const noexcept { return m_pieceId; }

private:
  QString m_pieceId;
};
} // namespace

PuzzleBoardWidget::PuzzleBoardWidget(QWidget *parent)
    : QGraphicsView(parent), m_scene(new QGraphicsScene(this)) {
  setScene(m_scene);
  setRenderHint(QPainter::Antialiasing);
  setDragMode(QGraphicsView::RubberBandDrag);
  setAcceptDrops(true);
  setSceneRect(0, 0, 1024, 640);
  m_scene->setBackgroundBrush(QBrush(QColor(28, 31, 36)));
  m_scene->addRect(sceneRect(), QPen(QColor(68, 74, 84)), Qt::NoBrush);
}

void PuzzleBoardWidget::setPieces(const QVector<Puzzle::PuzzlePiece> &pieces) {
  m_scene->clear();
  m_scene->setBackgroundBrush(QBrush(QColor(28, 31, 36)));
  m_scene->addRect(sceneRect(), QPen(QColor(68, 74, 84)), Qt::NoBrush);

  for (const auto &piece : pieces) {
    QPixmap preview = piece.preview().isNull()
                          ? QPixmap(120, 80)
                          : piece.preview().scaled(120, 80);
    if (preview.isNull()) {
      continue;
    }

    auto *item = new MovablePuzzleItem(piece.id(), preview);
    item->setPos(piece.currentPlacement());
    item->setToolTip(piece.id());
    m_scene->addItem(item);
  }
}

} // namespace PuzzleForge::Editor

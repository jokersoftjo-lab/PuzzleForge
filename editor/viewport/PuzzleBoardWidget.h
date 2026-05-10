#pragma once

#include "puzzle/pieces/PuzzlePiece.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>

namespace PuzzleForge::Editor {

class PuzzleBoardWidget : public QGraphicsView {
  Q_OBJECT

public:
  explicit PuzzleBoardWidget(QWidget *parent = nullptr);
  void setPieces(const QVector<Puzzle::PuzzlePiece> &pieces);

signals:
  void pieceMoved(const QString &pieceId, QPointF scenePosition);

private:
  QGraphicsScene *m_scene = nullptr;
};

} // namespace PuzzleForge::Editor

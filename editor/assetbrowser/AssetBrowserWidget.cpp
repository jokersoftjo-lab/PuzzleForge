#include "AssetBrowserWidget.h"

#include <QFileInfo>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidgetItem>
#include <QVBoxLayout>

namespace PuzzleForge::Editor {

AssetBrowserWidget::AssetBrowserWidget(QWidget *parent)
    : QWidget(parent), m_assetList(new QListWidget(this)) {
  auto *layout = new QVBoxLayout(this);
  layout->setContentsMargins(8, 8, 8, 8);
  layout->addWidget(new QLabel(tr("Imported Media"), this));
  layout->addWidget(m_assetList);

  m_assetList->setAcceptDrops(true);
  m_assetList->setDragEnabled(true);
  m_assetList->setAlternatingRowColors(true);

  connect(m_assetList, &QListWidget::itemDoubleClicked, this,
          [this](QListWidgetItem *item) {
            emit assetActivated(item->data(Qt::UserRole).toString());
          });
}

void AssetBrowserWidget::addAsset(const QString &filePath) {
  const QFileInfo info(filePath);
  auto *item = new QListWidgetItem(
      info.fileName().isEmpty() ? filePath : info.fileName(), m_assetList);
  item->setToolTip(filePath);
  item->setData(Qt::UserRole, filePath);
}

} // namespace PuzzleForge::Editor

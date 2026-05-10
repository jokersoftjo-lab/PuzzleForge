#pragma once

#include <QListWidget>
#include <QWidget>

namespace PuzzleForge::Editor {

class AssetBrowserWidget : public QWidget {
  Q_OBJECT

public:
  explicit AssetBrowserWidget(QWidget *parent = nullptr);
  void addAsset(const QString &filePath);

signals:
  void assetActivated(const QString &filePath);

private:
  QListWidget *m_assetList = nullptr;
};

} // namespace PuzzleForge::Editor

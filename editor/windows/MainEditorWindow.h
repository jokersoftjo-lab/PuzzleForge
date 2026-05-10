#pragma once

#include "engine/core/Engine.h"
#include "media/decoder/FFmpegVideoDecoder.h"
#include "puzzle/pieces/PuzzleGenerator.h"
#include "puzzle/timeline/TimelineModel.h"

#include <QMainWindow>
#include <QTextEdit>

namespace PuzzleForge::Editor {

class AssetBrowserWidget;
class PuzzleBoardWidget;
class TimelineWidget;

class MainEditorWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainEditorWindow(EngineCore::Engine &engine,
                            QWidget *parent = nullptr);

private slots:
  void importMedia();
  void saveProject();
  void loadProject();
  void loadMediaAsPuzzle(const QString &filePath);

private:
  void buildMenus();
  void buildToolbar();
  void buildDockingUi();
  void refreshPuzzleViews();
  void logMessage(const QString &message);

  EngineCore::Engine &m_engine;
  Media::FFmpegVideoDecoder m_videoDecoder;
  Puzzle::PuzzleGenerator m_puzzleGenerator;
  Puzzle::TimelineModel m_timeline;

  AssetBrowserWidget *m_assetBrowser = nullptr;
  TimelineWidget *m_timelineWidget = nullptr;
  PuzzleBoardWidget *m_puzzleBoard = nullptr;
  QTextEdit *m_inspector = nullptr;
  QTextEdit *m_console = nullptr;
  QTextEdit *m_aiAssistant = nullptr;
};

} // namespace PuzzleForge::Editor

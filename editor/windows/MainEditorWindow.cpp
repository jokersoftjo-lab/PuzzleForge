#include "MainEditorWindow.h"

#include "editor/assetbrowser/AssetBrowserWidget.h"
#include "editor/timeline/TimelineWidget.h"
#include "editor/viewport/PuzzleBoardWidget.h"

#include <QAction>
#include <QDockWidget>
#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeySequence>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QSize>
#include <QStatusBar>
#include <QToolBar>

namespace PuzzleForge::Editor {

MainEditorWindow::MainEditorWindow(EngineCore::Engine &engine, QWidget *parent)
    : QMainWindow(parent), m_engine(engine) {
  setWindowTitle(tr("PuzzleForge Editor"));
  resize(1440, 900);

  buildMenus();
  buildToolbar();
  buildDockingUi();

  statusBar()->showMessage(
      tr("Ready — %1 modules loaded").arg(m_engine.loadedModules().size()));
  logMessage(tr("Editor initialized. FFmpeg backend: %1")
                 .arg(m_videoDecoder.isAvailable() ? tr("available")
                                                   : tr("stub mode")));
}

void MainEditorWindow::importMedia() {
  const QString filePath = QFileDialog::getOpenFileName(
      this, tr("Import Media"), {},
      tr("Media Files (*.mp4 *.mkv *.avi *.wav *.mp3 *.png *.jpg *.jpeg "
         "*.gif);;All Files (*)"));

  if (!filePath.isEmpty()) {
    m_assetBrowser->addAsset(filePath);
    loadMediaAsPuzzle(filePath);
  }
}

void MainEditorWindow::saveProject() {
  const QString filePath = QFileDialog::getSaveFileName(
      this, tr("Save PuzzleForge Project"),
      QStringLiteral("Untitled.pforge.json"),
      tr("PuzzleForge Project (*.pforge.json);;JSON Files (*.json)"));

  if (filePath.isEmpty()) {
    return;
  }

  QJsonObject root;
  root.insert(QStringLiteral("format"), QStringLiteral("PuzzleForgeProject"));
  root.insert(QStringLiteral("version"), 1);
  root.insert(QStringLiteral("timeline"), m_timeline.toJson());

  QFile file(filePath);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    QMessageBox::warning(this, tr("Save Failed"), file.errorString());
    return;
  }

  file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
  logMessage(tr("Saved project: %1").arg(filePath));
}

void MainEditorWindow::loadProject() {
  const QString filePath = QFileDialog::getOpenFileName(
      this, tr("Open PuzzleForge Project"), {},
      tr("PuzzleForge Project (*.pforge.json);;JSON Files (*.json)"));

  if (filePath.isEmpty()) {
    return;
  }

  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::warning(this, tr("Open Failed"), file.errorString());
    return;
  }

  const QJsonDocument document = QJsonDocument::fromJson(file.readAll());
  m_timeline.fromJson(
      document.object().value(QStringLiteral("timeline")).toArray());
  refreshPuzzleViews();
  logMessage(tr("Loaded project: %1").arg(filePath));
}

void MainEditorWindow::loadMediaAsPuzzle(const QString &filePath) {
  const auto clip = m_videoDecoder.probeClip(filePath);
  m_timeline.setPieces(m_puzzleGenerator.generateGridPieces(clip, QSize(4, 3)));
  refreshPuzzleViews();
  logMessage(tr("Imported %1 and generated %2 puzzle pieces")
                 .arg(filePath)
                 .arg(m_timeline.pieces().size()));
}

void MainEditorWindow::buildMenus() {
  auto *fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(tr("Import Media..."), this,
                      &MainEditorWindow::importMedia, QKeySequence::Open);
  fileMenu->addAction(tr("Save Project..."), this,
                      &MainEditorWindow::saveProject, QKeySequence::Save);
  fileMenu->addAction(tr("Load Project..."), this,
                      &MainEditorWindow::loadProject);
  fileMenu->addSeparator();
  fileMenu->addAction(tr("Exit"), this, &QWidget::close);

  auto *windowMenu = menuBar()->addMenu(tr("&Window"));
  windowMenu->addAction(tr("Reset Layout"), this, [this] {
    restoreState(QByteArray{});
    logMessage(tr("Dock layout reset"));
  });
}

void MainEditorWindow::buildToolbar() {
  auto *toolbar = addToolBar(tr("Main Toolbar"));
  toolbar->setMovable(false);
  toolbar->addAction(tr("Import"), this, &MainEditorWindow::importMedia);
  toolbar->addAction(tr("Save"), this, &MainEditorWindow::saveProject);
  toolbar->addAction(tr("Load"), this, &MainEditorWindow::loadProject);
}

void MainEditorWindow::buildDockingUi() {
  m_puzzleBoard = new PuzzleBoardWidget(this);
  setCentralWidget(m_puzzleBoard);

  m_assetBrowser = new AssetBrowserWidget(this);
  auto *assetDock = new QDockWidget(tr("Asset Browser"), this);
  assetDock->setWidget(m_assetBrowser);
  addDockWidget(Qt::LeftDockWidgetArea, assetDock);

  m_timelineWidget = new TimelineWidget(this);
  auto *timelineDock = new QDockWidget(tr("Timeline"), this);
  timelineDock->setWidget(m_timelineWidget);
  addDockWidget(Qt::BottomDockWidgetArea, timelineDock);

  m_inspector = new QTextEdit(this);
  m_inspector->setReadOnly(true);
  m_inspector->setText(tr("Select a puzzle piece to inspect metadata."));
  auto *inspectorDock = new QDockWidget(tr("Inspector"), this);
  inspectorDock->setWidget(m_inspector);
  addDockWidget(Qt::RightDockWidgetArea, inspectorDock);

  m_aiAssistant = new QTextEdit(this);
  m_aiAssistant->setPlaceholderText(
      tr("AI-assisted puzzle generation and timeline suggestions will appear "
         "here."));
  auto *aiDock = new QDockWidget(tr("AI Assistant"), this);
  aiDock->setWidget(m_aiAssistant);
  addDockWidget(Qt::RightDockWidgetArea, aiDock);
  tabifyDockWidget(inspectorDock, aiDock);

  m_console = new QTextEdit(this);
  m_console->setReadOnly(true);
  auto *consoleDock = new QDockWidget(tr("Console Output"), this);
  consoleDock->setWidget(m_console);
  addDockWidget(Qt::BottomDockWidgetArea, consoleDock);
  tabifyDockWidget(timelineDock, consoleDock);

  connect(m_assetBrowser, &AssetBrowserWidget::assetActivated, this,
          &MainEditorWindow::loadMediaAsPuzzle);
  connect(m_timelineWidget, &TimelineWidget::pieceSelected, this,
          [this](const QString &pieceId) {
            m_inspector->setText(tr("Piece: %1\nDrag pieces on the puzzle "
                                    "board or reorder them in the timeline.")
                                     .arg(pieceId));
          });
}

void MainEditorWindow::refreshPuzzleViews() {
  m_timelineWidget->setTimeline(m_timeline);
  m_puzzleBoard->setPieces(m_timeline.pieces());
}

void MainEditorWindow::logMessage(const QString &message) {
  if (m_console != nullptr) {
    m_console->append(message);
  }
}

} // namespace PuzzleForge::Editor

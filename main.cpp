#include "editor/windows/MainEditorWindow.h"
#include "engine/core/Engine.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  PuzzleForge::EngineCore::Engine engine;
  engine.initialize();

  PuzzleForge::Editor::MainEditorWindow window(engine);
  window.show();

  const int exitCode = app.exec();
  engine.shutdown();
  return exitCode;
}

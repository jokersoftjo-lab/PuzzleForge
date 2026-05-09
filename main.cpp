#include <QApplication>

#include "mainwindow.h"

#include "engine/core/Engine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Engine engine;

    engine.initialize();

    MainWindow window;

    window.show();

    return app.exec();
}
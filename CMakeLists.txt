cmake_minimum_required(VERSION 3.19)
project(PuzzleForge VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(PkgConfig QUIET)

option(PUZZLEFORGE_ENABLE_FFMPEG "Enable FFmpeg-backed media decoding when development libraries are available" ON)

qt_standard_project_setup()

qt_add_executable(PuzzleForge
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    engine/core/Engine.cpp
    engine/core/Engine.h
    editor/windows/MainEditorWindow.cpp
    editor/windows/MainEditorWindow.h
    editor/assetbrowser/AssetBrowserWidget.cpp
    editor/assetbrowser/AssetBrowserWidget.h
    editor/timeline/TimelineWidget.cpp
    editor/timeline/TimelineWidget.h
    editor/viewport/PuzzleBoardWidget.cpp
    editor/viewport/PuzzleBoardWidget.h
    media/decoder/FFmpegVideoDecoder.cpp
    media/decoder/FFmpegVideoDecoder.h
    media/video/MediaTypes.h
    puzzle/pieces/PuzzleGenerator.cpp
    puzzle/pieces/PuzzleGenerator.h
    puzzle/pieces/PuzzlePiece.cpp
    puzzle/pieces/PuzzlePiece.h
    puzzle/timeline/TimelineModel.cpp
    puzzle/timeline/TimelineModel.h
)

target_include_directories(PuzzleForge
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(PuzzleForge
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

if(PUZZLEFORGE_ENABLE_FFMPEG AND PkgConfig_FOUND)
    pkg_check_modules(FFMPEG QUIET IMPORTED_TARGET
        libavformat
        libavcodec
        libavutil
        libswscale
    )

    if(FFMPEG_FOUND)
        target_link_libraries(PuzzleForge PRIVATE PkgConfig::FFMPEG)
        target_compile_definitions(PuzzleForge PRIVATE PUZZLEFORGE_HAS_FFMPEG=1)
    endif()
endif()

install(TARGETS PuzzleForge
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET PuzzleForge
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

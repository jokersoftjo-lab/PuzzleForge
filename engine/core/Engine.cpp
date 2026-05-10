#include "Engine.h"

#include <iostream>
#include <utility>

namespace PuzzleForge::EngineCore {

Engine::Engine(EngineConfig config) : m_config(std::move(config)) {}

Engine::~Engine() { shutdown(); }

bool Engine::initialize() {
  if (m_initialized) {
    return true;
  }

  registerCoreModules();
  m_lastUpdate = std::chrono::steady_clock::now();
  m_initialized = true;

  std::cout << m_config.applicationName << " engine initialized with "
            << m_loadedModules.size() << " modules\n";

  return true;
}

void Engine::update() {
  if (!m_initialized) {
    return;
  }

  const auto now = std::chrono::steady_clock::now();
  const std::chrono::duration<double> delta = now - m_lastUpdate;
  m_lastUpdate = now;

  // The runtime tick is intentionally lightweight while the editor is being
  // scaffolded. Subsystems can subscribe to this loop as they are promoted
  // from editor prototypes into engine modules.
  (void)delta;
}

void Engine::shutdown() {
  if (!m_initialized) {
    return;
  }

  std::cout << m_config.applicationName << " engine shutdown\n";
  m_loadedModules.clear();
  m_initialized = false;
}

bool Engine::isInitialized() const noexcept { return m_initialized; }

const EngineConfig &Engine::config() const noexcept { return m_config; }

const std::vector<std::string> &Engine::loadedModules() const noexcept {
  return m_loadedModules;
}

void Engine::registerCoreModules() {
  m_loadedModules = {"Core",          "Editor",    "Renderer.OpenGL", "Media",
                     "PuzzleRuntime", "ProjectIO", "PluginHost"};

  if (m_config.enableAiServices) {
    m_loadedModules.emplace_back("AI.LocalInference");
  }
}

} // namespace PuzzleForge::EngineCore

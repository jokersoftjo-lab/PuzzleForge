#pragma once

#include <chrono>
#include <memory>
#include <string>
#include <vector>

namespace PuzzleForge::EngineCore {

struct EngineConfig {
  std::string applicationName = "PuzzleForge";
  bool enableMediaPipeline = true;
  bool enablePuzzleRuntime = true;
  bool enableAiServices = false;
};

class Engine {
public:
  explicit Engine(EngineConfig config = {});
  ~Engine();

  Engine(const Engine &) = delete;
  Engine &operator=(const Engine &) = delete;
  Engine(Engine &&) noexcept = default;
  Engine &operator=(Engine &&) noexcept = default;

  bool initialize();
  void update();
  void shutdown();

  [[nodiscard]] bool isInitialized() const noexcept;
  [[nodiscard]] const EngineConfig &config() const noexcept;
  [[nodiscard]] const std::vector<std::string> &loadedModules() const noexcept;

private:
  void registerCoreModules();

  EngineConfig m_config;
  bool m_initialized = false;
  std::chrono::steady_clock::time_point m_lastUpdate;
  std::vector<std::string> m_loadedModules;
};

} // namespace PuzzleForge::EngineCore

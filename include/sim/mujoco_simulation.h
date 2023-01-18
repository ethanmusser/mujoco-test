/**
 * @file mujoco_simulation.h
 * @author Ethan J. Musser (emusser@seas.upenn.edu)
 * @brief
 * @date 1/6/23
 *
 * This code modified from DeepMind Technologies example simulation, which is
 * licensed as follows.
 *
 * Copyright 2021 DeepMind Technologies Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <mutex>
#include <new>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

#include <mujoco/mujoco.h>
#include "sim/glfw_dispatch.h"
#include "sim/simulate.h"
#include "sim/array_safety.h"

extern "C" {
#if defined(_WIN32) || defined(__CYGWIN__)
#include <windows.h>
#else
#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif
#include <dirent.h>
#include <dlfcn.h>
#include <sys/errno.h>
#include <unistd.h>
#endif
}


#if defined(_WIN32) || defined(__CYGWIN__)
typedef std::unique_ptr<std::remove_pointer_t<HMODULE>, decltype(&FreeLibrary)> unique_dlhandle;
#else
typedef std::unique_ptr<void, decltype(&dlclose)> unique_dlhandle;
#endif


/**
 *
 */
class MuJoCoSimulation {

 public:

  // plugin handling

  /**
   * @brief Access the path to the directory containing the current executable used to
   * determine the location of auto-loaded plugin libraries
   * @details Access the path to the directory containing the current
   * executable.  Used to determine the location of auto-loaded plugin
   * libraries.
   * @return Path to the directory containing the current executable
   */
  std::string getExecutableDir();

  // scan for libraries in the plugin directory to load additional plugins
  /**
   * @brief scan for libraries in the plugin directory to load additional plugins
   * @return
   */
  std::vector<unique_dlhandle> scanPluginLibraries();


  // simulation


  mjModel *LoadModel(const char *file, ::mujoco::Simulate &sim);

  // simulate in background thread (while rendering in main thread)
  void PhysicsLoop(::mujoco::Simulate &sim);

 protected:

  // constants
  static constexpr int kErrorLength = 1024;  // load error string length
  const double syncMisalign = 0.1;           // maximum mis-alignment before re-sync (simulation seconds)
  const double simRefreshFraction = 0.7;     // fraction of refresh available for simulation

  // model and data
  mjModel *m = nullptr;
  mjData *d = nullptr;

  // control noise variables
  mjtNum *ctrlnoise = nullptr;

};

class MuJoCoSimulationThreaded : public MuJoCoSimulation {

 public:
  // physics_thread

  void PhysicsThread(::mujoco::Simulate *sim, const char *filename);

};

// main

// run event loop
int EventLoop(int argc, const char **argv);



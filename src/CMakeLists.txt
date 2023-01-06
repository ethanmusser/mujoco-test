
# Header list
set(include-dir ../include/)
set(HEADER_LIST
  ${include-dir}/sim/array_safety.h
  ${include-dir}/sim/glfw_dispatch.h
  ${include-dir}/sim/simulate.h
  ${include-dir}/sim/uitools.h
  ${include-dir}/sim/mujoco_simulation.h
  )

# Source list
set(SOURCE_LIST
  sim/glfw_dispatch.cpp
  sim/simulate.cpp
  sim/uitools.cpp
  sim/mujoco_simulation.cpp
  )

# Make an automatic library - will be static or dynamic based on user setting
add_library(mujoco-test ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(mujoco-test PUBLIC ../include ../thirdparty/lodepng)

# All users of this library will need at least C++17
target_compile_features(mujoco-test PUBLIC cxx_std_17)

# Link library with mujoco and dependencies
include(AddMujocoAndDependencies)
target_link_libraries(mujoco-test PUBLIC mujoco::mujoco)
target_link_libraries(mujoco-test PUBLIC glfw)
target_link_libraries(mujoco-test PUBLIC ${CMAKE_DL_LIBS})
target_link_libraries(mujoco-test PUBLIC lodepng)

# Threading
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(mujoco-test PRIVATE Threads::Threads)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

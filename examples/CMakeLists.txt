
macro(add_example demo_name)
  # add the executable.
  add_executable(${demo_name} ${demo_name}.cpp)
  # dependencies
  target_link_libraries(${demo_name} PRIVATE mujoco-test)
endmacro(add_example demo_name)

# Add examples
#add_example(temp)

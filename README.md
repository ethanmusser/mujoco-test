# mujoco-test

Simple evaluation simulations using MuJoCo.


## Getting Started

1. Install MuJoCo's dependencies as follows.
   - Install [GLFW](https://www.glfw.org) with `apt`.
      ```shell
      sudo apt install libglfw3-dev
      ```
2. Download the MuJoCo 2.3.X binaries from the 
[releases page](https://github.com/deepmind/mujoco/releases) as a `tar.gz`.  
Note that this code is tested on MuJoCo 2.3.0.
3. Set the `mujoco_INSTALL_VERSION` environment variable to match the installed
MuJoCo version.  
4. Extract the downloaded `mujoco-2.3.X` directory into the
`~/.mujoco/mujoco-2.3.X` directory. If you want to specify a nonstandard
location for the package, set the `mujoco_INSTALL_PATH` environment variable.

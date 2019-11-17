# Corsac-engine

C++, SDL2, OpenGL - Game engine.

* SDL2 2.0.10(stable)
* OpenGL 4.6 NVIDIA

# Install

```bash

sudo apt install libsdl2{,-image,-mixer,-ttf,-gfx}-dev

sudo add-apt-repository ppa:oibaf/graphics-drivers
sudo apt update
sudo apt upgrade
sudo apt install libvulkan1 mesa-vulkan-drivers vulkan-utils
sudo apt-get install libglm-dev cmake libxcb-dri3-0 libxcb-present0 libpciaccess0 \
libpng-dev libxcb-keysyms1-dev libxcb-dri3-dev libx11-dev \
libmirclient-dev libwayland-dev libxrandr-dev libxcb-ewmh-dev
sudo apt-get install qt5-default qtwebengine5-dev
sudo apt-get install git libpython2.7

git clone https://github.com/Survereignty/Corsac-engine.git

cd Corsac-engine

# build and run
make

```
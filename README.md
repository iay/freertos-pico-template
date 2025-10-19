# Sample FreeRTOS Template

This template is a minimal viable template to use a Raspberry Pi Pico / Pico 2 with [FreeRTOS](https://www.freertos.org) using [Visual Studio Code](https://code.visualstudio.com) with the [Raspberry Pi Pico](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico) extension.

The `ProjectName` must be a literal string for the rest of the tasks used for flashing and debugging to pick the correct `ProjectName.elf` file. After that the `${PROJECT_NAME}` variable is used throughout the rest of the `CMakeLists.txt` file. 

The template was created with the Raspberry Pi Pico SDK version 2.1.1 and supports the Pico, Pico W, Pico 2 and Pico 2 W so far. For the Pico 2 both ARM and RISC-V cpu cores are supported.

The `FreeRTOSConfig.h` and `FreeRTOSConfig_examples_common.h` come directly from the [Raspberry Pi Pico Examples](https://github.com/raspberrypi/pico-examples) github.

## Submodule Update

Make sure to either clone recursively or update the submodules for FreeRTOS-Kernel after you clone to make sure you have all of the required code to build the project.

```sh
cd FreeRTOS-Kernel
git submodule update --init
```

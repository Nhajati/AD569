cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(ad5694r_test C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()


add_executable(ad5694r
  ad5694r.cpp
ad5694r.h
)


pico_add_extra_outputs(ad5694r)

target_link_libraries(ad5694r
	pico_stdlib 
  hardware_i2c
  hardware_spi
)

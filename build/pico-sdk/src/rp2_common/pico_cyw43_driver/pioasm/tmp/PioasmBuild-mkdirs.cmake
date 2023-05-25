# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/LBNP_programming/Pico/pico-sdk/tools/pioasm"
  "D:/LBNP_programming/Pico/AD5694R/build/pioasm"
  "D:/LBNP_programming/Pico/AD5694R/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm"
  "D:/LBNP_programming/Pico/AD5694R/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "D:/LBNP_programming/Pico/AD5694R/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "D:/LBNP_programming/Pico/AD5694R/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "D:/LBNP_programming/Pico/AD5694R/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/LBNP_programming/Pico/AD5694R/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/LBNP_programming/Pico/AD5694R/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()

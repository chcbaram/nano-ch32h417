cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(FIRM_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../firm-sdk")
set(CMAKE_MODULE_PATH "${FIRM_SDK_PATH}/tools")
include(riscv-gcc)


# 프로젝트 이름은 최종 출력 파일 이름으로 사용된다.
#
set(PRJ_NAME ch32h417-v3f)


project(${PRJ_NAME}
  LANGUAGES ASM C CXX
)


set(EXECUTABLE ${PRJ_NAME}.elf)



# 지정한 폴더에 있는 파일만 포함한다.
#
file(GLOB SRC_FILES CONFIGURE_DEPENDS
  src/*.cpp
  src/*.c
  src/ap/*.cpp
  src/ap/*.c
  src/bsp/*.c
  src/bsp/device/*.c
  src/bsp/startup/startup_ch32h417_v3f.S
)

# 하위폴더에 있는 파일까지 포함한다.
#
file(GLOB_RECURSE SRC_FILES_RECURSE CONFIGURE_DEPENDS
  src/ap/*.cpp
  src/ap/*.c
  
  src/hw/*.c

  ${FIRM_SDK_PATH}/common/*.c
  ${FIRM_SDK_PATH}/hal/src/*.c
  )


# 특정 폴더를 빌드에서 제외한다.
#
set(EXCLUDE_PATHS 
)

foreach(TMP_PATH ${SRC_FILES_RECURSE}) 
  foreach(EXCLUDE_PATH ${EXCLUDE_PATHS}) 
    string(FIND ${TMP_PATH} ${EXCLUDE_PATH} RESULT) 
    if(NOT ${RESULT} EQUAL -1) 
      list(REMOVE_ITEM SRC_FILES_RECURSE ${TMP_PATH}) 
    endif() 
  endforeach(EXCLUDE_PATH) 
endforeach(TMP_PATH)


add_executable(${EXECUTABLE} 
  ${SRC_FILES}
  ${SRC_FILES_RECURSE}
)



target_include_directories(${EXECUTABLE} PRIVATE 
  src  
  src/ap
  src/ap/modules
  src/ap/modules/common
  src/bsp
  src/bsp/device
  src/bsp/rtos  
  src/hw
  src/hw/driver
  src/lib

  ${FIRM_SDK_PATH}/common
  ${FIRM_SDK_PATH}/common/core
  ${FIRM_SDK_PATH}/common/hw/include 
  ${FIRM_SDK_PATH}/lib

  ${FIRM_SDK_PATH}/hal/inc
)

target_compile_definitions(${EXECUTABLE} PRIVATE
  -DCore_V3F
  )

target_compile_options(${EXECUTABLE} PRIVATE
  -march=rv32imafc
  -mabi=ilp32f

  -fdata-sections
  -ffunction-sections
  
  -fstack-usage 
  -Wmissing-field-initializers
  -Wuninitialized 

  -Wall
  -g3
  -O0
  )

set_source_files_properties(
    ${SRC_FILES_SPECIAL}
    PROPERTIES
        COMPILE_OPTIONS "-O0"
)

target_link_options(${EXECUTABLE} PRIVATE
  -T../src/bsp/ldscript/Link_v3f.ld

  -march=rv32imafc
  -mabi=ilp32f

  -nostartfiles
  --specs=nano.specs
  --specs=nosys.specs

  -lc
  -lm
  -lstdc++
  -lsupc++
  -fno-rtti
  
  -Wl,-Map=${PRJ_NAME}.map,--cref
  -Wl,--gc-sections
  -Xlinker -print-memory-usage -Xlinker
  )

set (CMAKE_C_FLAGS "-Wenum-conversion")
set (CMAKE_CXX_FLAGS "-fno-rtti")


add_custom_command(TARGET ${EXECUTABLE} 
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
  COMMENT "Invoking: Make Bin -> ${KEYBOARD_PATH}"
  )  
  


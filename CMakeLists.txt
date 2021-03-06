
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Toolchain")

# Using search in module path mode, the extension (.cmake) must be omitted
include(cmake_arm_none_eabi)	

cmake_minimum_required(VERSION 3.1)


set(ProjName Calculator)

project(${ProjName})


# ------------------------ Building ---------------------------------------

# ---------------------------- Error -----------------------------------------
# This doesn't work !!! it gives an error (target pattern contains no %")
# set(LINKER_SCRIPT	"${CMAKE_SOURCE_DIR}/tm4c1294ncpdt.lds")
# then using this LINKER_SCRIPT variable in linking flags
# ----------------------------------------------------------------------------

# ---------------------------- Error -----------------------------------------
# Cannot open the file tm4c1294ncpdt.lds, file or directory not found
# set(LINKER_SCRIPT	"tm4c1294ncpdt.lds")
# then using this LINKER_SCRIPT variable in linking flags without specifying the whole path
# Though the file is located at CMAKE_SOURCE_DIR, it must be explictly specified
# ----------------------------------------------------------------------------

add_subdirectory(./Libraries/UART)
add_subdirectory(./Libraries/LCD)

set(LINKER_SCRIPT	"tm4c1294ncpdt.lds")

# Soruce variables
set(SOURCES 
	src/handy.c
	src/main.c
	src/calculator.c
	src/UI.c
	tm4c1294ncpdt_startup_ccs_gcc.c
	)
	
	
set(CPU_OPTIONS "-mthumb -mcpu=cortex-m4 -march=armv7e-m")
set(FPU_OPTIONS "-mfloat-abi=soft -mfpu=fpv4-sp-d16")
set(PART_NAME	"-DPART_TM4C1294NCPDT")	# -D defines a macro to be used by preprocessor

set(CMAKE_C_FLAGS 
	"${CPU_OPTIONS} ${FPU_OPTIONS} ${PART_NAME} \
	-Wall -g -MD -std=c99")

set(CMAKE_EXE_LINKER_FLAGS 
	"${CPU_OPTIONS} ${FPU_OPTIONS} ${PART_NAME} -specs=nosys.specs\
	-ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall \
	-Wl,-T\"${CMAKE_SOURCE_DIR}/${LINKER_SCRIPT}\" -Wl,-Map=\"GNU_test.map\" \
	")

set(CMAKE_EXECUTABLE_SUFFIX ".out" CACHE INTERNAL "")

#Executables and links
add_executable(${ProjName} "${SOURCES}")

target_include_directories(${ProjName} PUBLIC
			${PROJECT_SOURCE_DIR}/include
			${PROJECT_SOURCE_DIR}/include/CMSIS
			${PROJECT_SOURCE_DIR}/Libraries/UART/include
			${PROJECT_SOURCE_DIR}/Libraries/LCD/include
			 )

target_link_libraries(${ProjName} UART)
target_link_libraries(${ProjName} LCD)

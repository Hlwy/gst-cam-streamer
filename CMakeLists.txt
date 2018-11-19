cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(gst_cam_streamer)

# ===========================
#       Set Build Options
# ===========================
set(VERBOSE         ON CACHE INTERNAL "CMake execution debugging")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wno-write-strings")
set(CMAKE_CXX_FLAGS "  ${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall")
# ===========================
#        Set Compiler
# ===========================
# if(COMPILE_ARM)
#      set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
#      set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
# endif(COMPILE_ARM)

# ===========================
#    Set CMake Properties
# ===========================
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBS_DIR ${LIBRARY_OUTPUT_PATH})
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCS_DIR "${PROJECT_SOURCE_DIR}/include")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/tests")
set(HOME_DIR "${PROJECT_SOURCE_DIR}")

# ============================================
#       Find & Include Dependencies
# ============================================
# Find Armadillo
find_package(LAPACK REQUIRED)
find_package(BLAS REQUIRED)
find_package(Armadillo REQUIRED)

# Find Boost Libraries
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(Threads)

# Find OpenCV libraries
find_package(OpenCV REQUIRED
     NO_MODULE #Should be optional, tells CMake to use config mode
     PATHS /usr/local/share/OpenCV # Tells CMake to look here
     NO_DEFAULT_PATH #and don't look anywhere else
)

# OpenMP
find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
     pkg_check_modules(GST "gstreamer-1.0")
     if(GST_FOUND)
          set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GST_CFLAGS}")
          message(STATUS "Found Gstreamer 1.0")
     endif()
endif()

include_directories(
     include
     /usr/local/include/opencv2
     /usr/local/include/opencv
     ${Boost_INCLUDE_DIRS}
     ${LAPACK_INCLUDE_DIRS}
     ${BLAS_INCLUDE_DIRS}
     ${ARMADILLO_INCLUDE_DIRS}
     ${OpenCV_INCLUDE_DIRS}
     ${GST_INCLUDE_DIRS}
)

set(LIBS
     ${Boost_LIBRARIES}
     ${ARMADILLO_LIBRARIES}
     ${LAPACK_LIBRARIES}
     ${BLAS_LIBRARIES}
     ${OpenCV_LIBS}
     ${CMAKE_THREAD_LIBS_INIT}
     ${GST_LIBRARIES}
)

# MESSAGE(STATUS "OpenCV includes: " ${OpenCV_INCLUDE_DIRS} )
# MESSAGE(STATUS "OpenCV libraries: " ${OpenCV_LIBS} )

# ===========================
#     Build Targets
# ===========================

add_executable(server src/gstserver.cpp)
target_link_libraries(server ${LIBS})


add_executable(client src/gstclient.cpp)
target_link_libraries(client ${LIBS})

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")
cmake_minimum_required(VERSION 3.28)
project(render)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-documentation)

#system deps
find_package(OpenGL REQUIRED COMPONENTS OpenGL)

#vcpkg deps
find_package(llnl-units CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(mdspan CONFIG REQUIRED)
find_package(libassert CONFIG REQUIRED)

#fetchcontent deps
include(FetchContent)
set(WEBGPU_BACKEND DAWN) #or WGPU
FetchContent_Declare(
  webgpu
  GIT_REPOSITORY https://github.com/eliemichel/WebGPU-distribution
  GIT_TAG main
  SYSTEM EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(webgpu)

#add_subdirectory deps
#FIXME when glfw is installed via vcpkg / system package (maybe?) glfw3webgpu doesn't have the glfw macro
set(GLFW_BUILD_X11 TRUE)
add_subdirectory(glfw3webgpu)

add_executable(render src/render.cc)
set_target_properties(render PROPERTIES CMAKE_CXX_EXTENSIONS FALSE)
target_compile_options(render PRIVATE -Werror)
target_include_directories(render PRIVATE src)
target_link_libraries(render PRIVATE llnl-units::units OpenGL::OpenGL glfw glm::glm Freetype::Freetype assimp::assimp range-v3 nlohmann_json pugixml std::mdspan libassert::assert webgpu glfw3webgpu)
install(TARGETS render)
target_copy_webgpu_binaries(render)

project(MatrixMultOpenCL LANGUAGES CXX)

find_package(OpenCL REQUIRED)

add_executable(${PROJECT_NAME} ../src/dune.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenCL::OpenCL)
target_link_dune_default_libraries(${PROJECT_NAME})
target_compile_definitions(${PROJECT_NAME} PRIVATE CL_TARGET_OPENCL_VERSION=100)

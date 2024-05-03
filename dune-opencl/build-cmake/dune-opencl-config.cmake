if(NOT dune-opencl_FOUND)
# Whether this module is installed or not
set(dune-opencl_INSTALLED OFF)

# Settings specific to the module

# Package initialization
# Set prefix to source dir
set(PACKAGE_PREFIX_DIR /home/vinicius/Documentos/OpenCL/dune-opencl/dune-opencl)
macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

#report other information
set_and_check(dune-opencl_PREFIX "${PACKAGE_PREFIX_DIR}")
set_and_check(dune-opencl_INCLUDE_DIRS "/home/vinicius/Documentos/OpenCL/dune-opencl/dune-opencl")
set(dune-opencl_CXX_FLAGS "-std=c++17 ")
set(dune-opencl_CXX_FLAGS_DEBUG "-g")
set(dune-opencl_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(dune-opencl_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(dune-opencl_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
set(dune-opencl_DEPENDS "dune-common;dune-geometry;dune-uggrid;dune-grid;dune-istl")
set(dune-opencl_SUGGESTS "")
set(dune-opencl_MODULE_PATH "/home/vinicius/Documentos/OpenCL/dune-opencl/dune-opencl/cmake/modules")
set(dune-opencl_LIBRARIES "")

# Lines that are set by the CMake build system via the variable DUNE_CUSTOM_PKG_CONFIG_SECTION


#import the target
if(dune-opencl_LIBRARIES)
  get_filename_component(_dir "${CMAKE_CURRENT_LIST_FILE}" PATH)
  include("${_dir}/dune-opencl-targets.cmake")
endif()
endif()

#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "minitrace::minitrace" for configuration "RelWithDebInfo"
set_property(TARGET minitrace::minitrace APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(minitrace::minitrace PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/minitrace.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/minitrace.dll"
  )

list(APPEND _cmake_import_check_targets minitrace::minitrace )
list(APPEND _cmake_import_check_files_for_minitrace::minitrace "${_IMPORT_PREFIX}/lib/minitrace.lib" "${_IMPORT_PREFIX}/bin/minitrace.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

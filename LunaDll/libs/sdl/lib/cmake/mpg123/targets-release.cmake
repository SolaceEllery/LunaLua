#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MPG123::libmpg123" for configuration "Release"
set_property(TARGET MPG123::libmpg123 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MPG123::libmpg123 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/mpg123.lib"
  )

list(APPEND _cmake_import_check_targets MPG123::libmpg123 )
list(APPEND _cmake_import_check_files_for_MPG123::libmpg123 "${_IMPORT_PREFIX}/lib/mpg123.lib" )

# Import target "MPG123::libsyn123" for configuration "Release"
set_property(TARGET MPG123::libsyn123 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MPG123::libsyn123 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/syn123.lib"
  )

list(APPEND _cmake_import_check_targets MPG123::libsyn123 )
list(APPEND _cmake_import_check_files_for_MPG123::libsyn123 "${_IMPORT_PREFIX}/lib/syn123.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

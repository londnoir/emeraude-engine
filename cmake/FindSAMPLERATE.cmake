# - Find samplerate
# Find the native samplerate includes and libraries
#
#  SAMPLERATE_INCLUDE_DIRS - where to find samplerate.h, etc.
#  SAMPLERATE_LIBRARIES   - List of libraries when using libsamplerate.
#  SAMPLERATE_FOUND       - True if libsamplerate found.

if(SAMPLERATE_INCLUDE_DIRS)
	# Already in cache, be silent
	SET(SAMPLERATE_FIND_QUIETLY TRUE)
endif(SAMPLERATE_INCLUDE_DIRS)

find_path(SAMPLERATE_INCLUDE_DIRS NAMES samplerate.h PATHS
	${SAMPLERATE_DIR_SEARCH}/include
	/usr/include
	/usr/local/include
	/opt/local/include
	/Library/Frameworks
)

find_library(SAMPLERATE_LIBRARY NAMES samplerate PATHS
	${SAMPLERATE_DIR_SEARCH}/lib
	/usr/lib
	/usr/local/lib
	/opt/local/lib
	/Library/Frameworks
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SAMPLERATE DEFAULT_MSG SAMPLERATE_INCLUDE_DIRS SAMPLERATE_LIBRARY)

if(SAMPLERATE_FOUND)
	SET(SAMPLERATE_LIBRARIES ${SAMPLERATE_LIBRARY})
else(SAMPLERATE_FOUND)
	SET(SAMPLERATE_LIBRARIES)
endif(SAMPLERATE_FOUND)

mark_as_advanced(SAMPLERATE_INCLUDE_DIRS SAMPLERATE_LIBRARIES)

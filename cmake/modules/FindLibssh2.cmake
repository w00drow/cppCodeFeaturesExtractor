find_package(PkgConfig)

find_path(LIBSSH2_INCLUDE_DIR libssh2.h
    HINTS ${THIRD_PARTY_DIR}
)

find_library(LIBSSH2_LIBRARY NAMES ssh2 
    HINTS ${THIRD_PARTY_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libssh2 DEFAULT_MSG LIBSSH2_INCLUDE_DIR LIBSSH2_LIBRARY)

if(LIBSSH2_FOUND)
    set(LIBSSH2_INCLUDE_DIRS ${LIBSSH2_INCLUDE_DIR})
	set(LIBSSH2_LIBRARIES ${LIBSSH2_LIBRARY})
endif()
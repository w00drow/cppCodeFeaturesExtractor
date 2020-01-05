find_package(PkgConfig)

find_path(LIBGIT2_INCLUDE_DIR git2.h
    HINTS ${THIRD_PARTY_DIR}
)

find_library(LIBGIT2_LIBRARY NAMES git2
    HINTS ${THIRD_PARTY_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libgit2 DEFAULT_MSG LIBGIT2_INCLUDE_DIR LIBGIT2_LIBRARY)

if(LIBGIT2_FOUND)
    set(LIBGIT2_INCLUDE_DIRS ${LIBGIT2_INCLUDE_DIR})
	set(LIBGIT2_LIBRARIES ${LIBGIT2_LIBRARY})
endif()

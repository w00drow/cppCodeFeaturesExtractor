cmake_minimum_required(VERSION 3.14)

include(ExternalProject)

set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/vendor)
set(CMAKE_PREFIX_PATH ${THIRD_PARTY_DIR})

find_package(Libssh2)
if(NOT LIBSSH2_FOUND)
    ExternalProject_Add(
        libssh2
	    GIT_REPOSITORY https://github.com/libssh2/libssh2
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR} -DBUILD_SHARED_LIBS=ON
        )
else()
    add_custom_target(libssh2)
    set(LIBSSH2_INCLUDE_DIRNAME ${LIBSSH2_INCLUDE_DIRS} PARENT_SCOPE)
    set(LIBSSH2_LIBNAME ${LIBSSH2_LIBRARIES} PARENT_SCOPE)
endif(NOT LIBSSH2_FOUND)

find_package(Libgit2)
if(NOT LIBGIT2_FOUND)
    ExternalProject_Add(
        libgit2
	    GIT_REPOSITORY https://github.com/libgit2/libgit2
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR} -DCMAKE_PREFIX_PATH=${THIRD_PARTY_DIR}
        )
else()
    add_custom_target(libgit2)
    set(LIBGIT2_INCLUDE_DIRNAME ${LIBGIT2_INCLUDE_DIRS} PARENT_SCOPE)
    set(LIBGIT2_LIBNAME ${LIBGIT2_LIBRARIES} PARENT_SCOPE)
endif(NOT LIBGIT2_FOUND)
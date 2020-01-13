add_executable(cppCodeFeaturesExtractor main.cpp)

target_link_libraries(cppCodeFeaturesExtractor 
					${LIBGIT2_LIBRARY} 
					${LIBSSH2_LIBRARY})
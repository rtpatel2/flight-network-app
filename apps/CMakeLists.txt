add_executable(bfs-visualization main.cc)
target_compile_features(bfs-visualization PRIVATE cxx_std_17)
target_link_libraries(bfs-visualization PRIVATE flight)
# Tests need to be added as executables first
add_executable(test-flight test-main.cc test_network.cc)

# We're using C++17 in the test
target_compile_features(test-flight PRIVATE cxx_std_17)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(test-flight PRIVATE flight Catch2::Catch2)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME test-flight COMMAND test-flight) # Command can be a target

# Add folders
set_target_properties(test-flight PROPERTIES FOLDER cs126)

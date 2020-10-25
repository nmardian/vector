enable_testing()
find_package(GTest 1.10.0 REQUIRED CONFIG)
add_executable(TestVector)

target_include_directories(TestVector PUBLIC "${GTEST_INCLUDE_DIRS}")
target_include_directories(TestVector PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(TestVector 
        GTest::gtest 
        GTest::gtest_main
        VectorLib)

target_sources(TestVector PUBLIC
        TestInputParser.cpp
)      
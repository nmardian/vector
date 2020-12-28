target_include_directories(VectorLib PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_sources(VectorLib PUBLIC 
                    CallsignGenerator.cpp
                    InputParser.cpp
                    MathUtil.cpp
)
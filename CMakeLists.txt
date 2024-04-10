cmake_minimum_required(VERSION 3.16)

project(CatMaze LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(FETCHCONTENT_QUIET FALSE)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY              https://github.com/SFML/SFML.git
    GIT_TAG                     2.6.x
)
FetchContent_Declare(json 
    URL                         https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP  TRUE
)
FetchContent_MakeAvailable(SFML json)

file(GLOB SRC *.cc *.h)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics nlohmann_json::nlohmann_json)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM
    )
endif()

install(TARGETS ${PROJECT_NAME})
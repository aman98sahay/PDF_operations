cmake_minimum_required(VERSION 3.22)

project(LinkingPDFs )

include(FetchContent)

#-DCMAKE_BUILD_TYPE=Debug -DCMAKE_FIND_FRAMEWORK=NEVER -DCMAKE_PREFIX_PATH=`brew --prefix` -DFontconfig_INCLUDE_DIR=`brew --prefix fontconfig`/include -DOPENSSL_ROOT_DIR=`brew --prefix openssl@3`

set (DCMAKE_BUILD_TYPE Debug)
set (CMAKE_FIND_FRAMEWORK NEVER)

execute_process(COMMAND brew --prefix
OUTPUT_VARIABLE prefix_value
)

string(REPLACE "\n" "" prefix_value ${prefix_value})

set(CMAKE_PREFIX_PATH ${prefix_value})

execute_process(COMMAND brew --prefix fontconfig
OUTPUT_VARIABLE prefix_font_config
)

string(REPLACE "\n" "" prefix_font_config ${prefix_font_config})

set(Fontconfig_INCLUDE_DIR "${prefix_font_config}/include")
execute_process(COMMAND brew --prefix openssl@3
OUTPUT_VARIABLE prefix_openssl
)
message ("")
string(REPLACE "\n" "" prefix_openssl ${prefix_openssl})
set(OPENSSL_ROOT_DIR ${prefix_openssl})


#set(PODOFO_BUILD_LIB_ONLY TRUE)
#set(PODOFO_BUILD_STATIC TRUE)


set(CMAKE_CXX_STANDARD 17)

set(PODOFO_BUILD_STATIC TRUE)

# add_subdirectory(podofo)
FetchContent_Declare(
   podofo 
   GIT_REPOSITORY https://github.com/podofo/podofo.git
)
FetchContent_MakeAvailable (podofo)
#add_subdirectory(${CMAKE_BINARY_DIR}/_deps/podofo-src/)
add_compile_options(${PODOFO_CFLAGS})
add_executable(main main.cxx)
target_link_libraries(main ${PODOFO_LIBRARIES})
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/podofo-src/src)
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/podofo/src/podofo/)
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/podofo-build/src/podofo/)
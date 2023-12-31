# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("http")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.
add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        native-lib.cpp
        client.cc
        curl_client.cc

        nearby/utils.cc
        nearby/url.cc
        nearby/http_request.cc
        nearby/http_status_code.cc
        nearby/http_response.cc
        #nearby/http_client_impl.cc


        thread/Utils.cpp
        thread/ScopedThread.cpp
        thread/CompilerConstants.cpp
        thread/Porting.cpp
        thread/Format.cpp
        thread/KAssert.cpp
        thread/SingleThreadExecutor.cpp
        )


set(ABSEIL_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../third_party/abseil-cpp)
message("ABSEIL_ROOT_DIR: ${ABSEIL_ROOT_DIR}")
add_subdirectory(${ABSEIL_ROOT_DIR}  ${ABSEIL_ROOT_DIR}/build)


find_package(curl REQUIRED CONFIG)
find_package(jsoncpp REQUIRED CONFIG)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        curl::curl
        jsoncpp::jsoncpp
        android
        log
        absl::core_headers
        absl::absl_check
        absl::absl_log
        absl::algorithm
        absl::base
        absl::bind_front
        absl::bits
        absl::btree
        absl::check
        absl::cleanup
        absl::cord
        absl::core_headers
        absl::die_if_null
        absl::debugging
        absl::dynamic_annotations
        absl::flags
        absl::flat_hash_map
        absl::flat_hash_set
        absl::function_ref
        absl::flags_commandlineflag
        absl::flags_marshalling
        absl::flags_parse
        absl::flags_reflection
        absl::flags_usage
        absl::hash
        absl::layout
        absl::log_initialize
        absl::log_severity
        absl::log
        absl::log_flags
        absl::log_globals
        absl::log_initialize
        absl::log_internal_message
        absl::memory
        absl::node_hash_map
        absl::node_hash_set
        absl::optional
        absl::span
        absl::status
        absl::statusor
        absl::strings
        absl::synchronization
        absl::time
        absl::type_traits
        absl::utility
        absl::variant
        absl::cord
        absl::random_random
        absl::raw_hash_set
        absl::hash
        absl::leak_check
        absl::memory
        absl::meta
        absl::stacktrace
        absl::status
        absl::statusor
        absl::str_format
        absl::strings
        absl::synchronization
        absl::time
        absl::any)
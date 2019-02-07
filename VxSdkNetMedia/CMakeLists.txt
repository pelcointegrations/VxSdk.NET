cmake_minimum_required(VERSION 2.8)
project(VxSdk.NET-Media)

add_definitions (-D_SCL_SECURE_NO_WARNINGS -D_WIN32_WINNT=0x0601 /wd4267 /wd4018 /doc)

set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /KEYFILE:\"${CMAKE_SOURCE_DIR}/VxSdkNetKey.snk\"")

if (CMAKE_SIZEOF_VOID_P MATCHES 8)
set( ARCH "x64" )
set( CPP_ARCH "x64" )
else(CMAKE_SIZEOF_VOID_P MATCHES 8)
set( ARCH "x86" )
set( CPP_ARCH "Win32" )
endif(CMAKE_SIZEOF_VOID_P MATCHES 8)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${ARCH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${ARCH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${ARCH})

file(GLOB LIB_SOURCES ../VxSdkNet/Source/*.* Source/MediaControl.cpp Source/VxSdkNetMedia.rc)
list(FILTER LIB_SOURCES EXCLUDE REGEX ".*VxSdkNet.rc$")

link_directories(
    ${CMAKE_SOURCE_DIR}/packages/VideoXpertSdk-Media/build/native/${CPP_ARCH}/lib/
)

add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES})

target_link_libraries(${PROJECT_NAME} optimized VxSdk.lib)
target_link_libraries(${PROJECT_NAME} optimized VxSdk-Media.lib)

include_directories(
    ../VxSdkNet/Include/
    ${CMAKE_SOURCE_DIR}/Include/
    ${CMAKE_SOURCE_DIR}/packages/VideoXpertSdk-Media/build/native/include/VxSdk/
    ${CMAKE_SOURCE_DIR}/packages/VideoXpertSdk-Media/build/native/include/VxSdk-Media/
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.dll ${CMAKE_SOURCE_DIR}/bin/${ARCH}/Release/
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.xml ${CMAKE_SOURCE_DIR}/bin/${ARCH}/Release/
)

set_property(TARGET ${PROJECT_NAME} PROPERTY COMMON_LANGUAGE_RUNTIME "")
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_GLOBAL_ROOTNAMESPACE "VxSdkNetMedia")
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_GLOBAL_KEYWORD "ManagedCProj")
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_GLOBAL_CLRSupport "true")
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.6.1")
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_REFERENCES "System" "System.Data" "System.Drawing" "System.Windows.Forms" "System.Xml")

string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
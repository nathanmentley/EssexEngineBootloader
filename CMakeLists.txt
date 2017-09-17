#files

file(GLOB EssexEngineBootloader_HEADERS
    "src/System/Bootloader/*.h"
)
file(GLOB EssexEngineBootloader_SRC
    ${EssexEngineBootloader_HEADERS}
    "src/System/Bootloader/*.cpp"
)

#setup headers

file(COPY ${EssexEngineBootloader_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/lib/include/EssexEngineBootloader/")

#setup build

add_executable(EssexEngineBootloader ${EssexEngineBootloader_SRC})
target_link_libraries(EssexEngineBootloader EssexEngineCore)
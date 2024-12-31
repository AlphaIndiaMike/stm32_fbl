
#[[-----------------------------------
Set Project Directories
-------------------------------------]]
set(bsp_directory       ${CMAKE_CURRENT_SOURCE_DIR}/01_bsp)
set(main_directory      ${CMAKE_CURRENT_SOURCE_DIR}/50_main)
set(ll_directory        ${CMAKE_CURRENT_SOURCE_DIR}/10_ll_services)


#[[-----------------------------------
Include CMakeFiles from various modules
-------------------------------------]]
add_subdirectory(${bsp_directory})
add_subdirectory(${main_directory})
add_subdirectory(${ll_directory})

#[[-----------------------------------
Define the exe.
-------------------------------------]]
add_executable( ${target}
    $<TARGET_OBJECTS:cmsis_h7xx_component>
    $<TARGET_OBJECTS:stm32h7xx_hal_driver_component>
    $<TARGET_OBJECTS:main_component>
    $<TARGET_OBJECTS:ll_svc_component>
)

add_executable(${PROJECT_NAME_EXE}::${target} ALIAS ${target})

#[[-----------------------------------
How to compile:
Linking
-------------------------------------]]
target_link_options(${target} PUBLIC
    ${PROJ_TARGET_LINK_OPTIONS}
)

#[[-----------------------------------
How to compile:
Post-build
-------------------------------------]]

add_custom_command(TARGET ${target}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${target}> ${CMAKE_BINARY_DIR}/$<TARGET_FILE_NAME:${target}>
)

#[[-
add_custom_command(TARGET ${target}
    POST_BUILD
    COMMAND arm-none-eabi-size ${CMAKE_BINARY_DIR}/${target}
)
]]

add_custom_command(TARGET ${target}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${CMAKE_BINARY_DIR}/${target} ${CMAKE_BINARY_DIR}/${hex_file}
    COMMAND arm-none-eabi-objcopy -O binary ${CMAKE_BINARY_DIR}/${target} ${CMAKE_BINARY_DIR}/${bin_file}
)

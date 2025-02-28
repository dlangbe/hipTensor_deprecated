###############################################################################
 #
 # MIT License
 #
 # Copyright (c) 2023 Advanced Micro Devices, Inc.
 #
 # Permission is hereby granted, free of charge, to any person obtaining a copy
 # of this software and associated documentation files (the "Software"), to deal
 # in the Software without restriction, including without limitation the rights
 # to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 # copies of the Software, and to permit persons to whom the Software is
 # furnished to do so, subject to the following conditions:
 #
 # The above copyright notice and this permission notice shall be included in
 # all copies or substantial portions of the Software.
 #
 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 # FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 # LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 # OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 # THE SOFTWARE.
 #
 ###############################################################################

# Setup a test manifest
set(INSTALL_TEST_FILE "${CMAKE_CURRENT_BINARY_DIR}/install_CTestTestfile.cmake")
file(WRITE "${INSTALL_TEST_FILE}"
[=[
# This is a test file generated by hipTensor for install time.
# It differs slightly from the default testfile, and you may encounter issues because of that.
]=]
)

# Target that will trigger build of all tests
add_custom_target(hiptensor_tests)

# Create test executables and deploy
function(add_hiptensor_test BINARY_NAME FILE_NAME)

    message( STATUS "adding hiptensor test: ${BINARY_NAME}")
    add_executable(${BINARY_NAME} ${FILE_NAME})

    # Test must propagate the build interface includes to make sure
    # hiptensor includes are captured at runtime.
    target_link_libraries(${BINARY_NAME} PRIVATE hiptensor::hiptensor "-L${HIP_CLANG_ROOT}/lib" "-Wl,-rpath=${HIP_CLANG_ROOT}/lib")
    target_include_directories(${BINARY_NAME} PRIVATE
                               ${CMAKE_CURRENT_SOURCE_DIR}
                               ${PROJECT_SOURCE_DIR}/library/include
                               ${PROJECT_SOURCE_DIR}/library/src/contraction)

    # Build this test under custom target
    add_dependencies(hiptensor_tests ${BINARY_NAME})

    # Register with ctest
    add_test(NAME ${BINARY_NAME} COMMAND ${BINARY_NAME})
    set_property(TEST ${BINARY_NAME} PROPERTY SKIP_REGULAR_EXPRESSION "HIPTENSOR_STATUS_ARCH_MISMATCH" "unsupported host device")

    # Install with rocm pkg
    rocm_install_targets(
    TARGETS ${BINARY_NAME}
    COMPONENT tests
    )

    # Add to testing manifest
    get_target_property(EXE_NAME ${BINARY_NAME} RUNTIME_OUTPUT_NAME)
    if(EXE_NAME STREQUAL "EXE_NAME-NOTFOUND")
        get_target_property(EXE_NAME ${BINARY_NAME} OUTPUT_NAME)
        if(EXE_NAME STREQUAL "EXE_NAME-NOTFOUND")
            set(EXE_NAME "${BINARY_NAME}")
        endif()
    endif()
    file(APPEND "${INSTALL_TEST_FILE}" "add_test(${BINARY_NAME} \"../${BINARY_NAME}\")\n")

endfunction()

# Create unit test executables and deploy
# Differs from hiptensor_test in that src include directory is linked
function(add_hiptensor_unit_test BINARY_NAME FILE_NAME)

    message( STATUS "adding hiptensor unit test: ${BINARY_NAME}")
    add_executable(${BINARY_NAME} ${FILE_NAME})

    # Test must propagate the build interface includes to make sure
    # hiptensor includes are captured at runtime.
    target_link_libraries(${BINARY_NAME} PRIVATE hiptensor::hiptensor "-L${HIP_CLANG_ROOT}/lib" "-Wl,-rpath=${HIP_CLANG_ROOT}/lib")
    target_include_directories(${BINARY_NAME} PRIVATE
                               ${CMAKE_CURRENT_SOURCE_DIR}
                               ${PROJECT_SOURCE_DIR}/library/include
                               ${PROJECT_SOURCE_DIR}/library/src/include)

    # Build this test under custom target
    add_dependencies(hiptensor_tests ${BINARY_NAME})

    # Register with ctest
    add_test(NAME ${BINARY_NAME} COMMAND ${BINARY_NAME})
    set_property(TEST ${BINARY_NAME} PROPERTY SKIP_REGULAR_EXPRESSION "HIPTENSOR_STATUS_ARCH_MISMATCH" "unsupported host device")

    # Install with rocm pkg
    rocm_install_targets(
    TARGETS ${BINARY_NAME}
    COMPONENT tests
    )

    # Add to testing manifest
    get_target_property(EXE_NAME ${BINARY_NAME} RUNTIME_OUTPUT_NAME)
    if(EXE_NAME STREQUAL "EXE_NAME-NOTFOUND")
        get_target_property(EXE_NAME ${BINARY_NAME} OUTPUT_NAME)
        if(EXE_NAME STREQUAL "EXE_NAME-NOTFOUND")
            set(EXE_NAME "${BINARY_NAME}")
        endif()
    endif()
    file(APPEND "${INSTALL_TEST_FILE}" "add_test(${BINARY_NAME} \"../${BINARY_NAME}\")\n")

endfunction()

add_subdirectory(01_contraction)
add_subdirectory(00_unit/logger)

rocm_install(
    FILES "${INSTALL_TEST_FILE}"
    DESTINATION "${CMAKE_INSTALL_BINDIR}/${PROJECT_NAME}"
    COMPONENT tests
    RENAME "CTestTestfile.cmake"
)

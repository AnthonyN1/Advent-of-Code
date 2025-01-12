# Usage: cmake -D DAY=1 -D YEAR=2024 -P generate_day.cmake

if(NOT DEFINED DAY OR NOT DEFINED YEAR)
    message(FATAL_ERROR "DAY and YEAR parameters are required.")
endif()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/.session")
    message(FATAL_ERROR "Retrieve your session cookie from the Advent of Code website and put it in a .session file.")
endif()


function(generate_day day year)
    if(NOT "${day}" MATCHES "^([1-9]|1[0-9]|2[1-5])$")
        message(STATUS "Invalid day number: ${day}.")
        return()
    endif()
    if(NOT "${year}" MATCHES "^20(1[5-9]|2[0-4])$")
        message(STATUS "Invalid year number: ${year}.")
        return()
    endif()

    # Potentially adds a leading zero to the day.
    set(DAY_FILENAME ${day})
    if("${day}" MATCHES "^[1-9]$")
        set(DAY_FILENAME "0${day}")
    endif()

    # Generates the code files from templates.
    message(STATUS "Generating 12/${day}/${year}.")

    set(TEMPLATE_H_FILE "${CMAKE_SOURCE_DIR}/templates/day_template.h.in")
    set(TEMPLATE_CPP_FILE "${CMAKE_SOURCE_DIR}/templates/day_template.cpp.in")
    set(OUTPUT_H_FILE "${CMAKE_SOURCE_DIR}/src/problems/${year}/year${year}_day${DAY_FILENAME}.h")
    set(OUTPUT_CPP_FILE "${CMAKE_SOURCE_DIR}/src/problems/${year}/year${year}_day${DAY_FILENAME}.cpp")
    
    if(EXISTS ${OUTPUT_H_FILE} OR EXISTS ${OUTPUT_CPP_FILE})
        message(STATUS "This day source has already been generated.")
    else()
        message(STATUS "Generating source files for 12/${day}/${year}.")
        configure_file(${TEMPLATE_H_FILE} ${OUTPUT_H_FILE} @ONLY)
        configure_file(${TEMPLATE_CPP_FILE} ${OUTPUT_CPP_FILE} @ONLY)
    endif()

    # Downloads the input from the Advent of Code website.
    message(STATUS "Downloading the input.")

    file(READ ${CMAKE_SOURCE_DIR}/.session SESSION_COOKIE)
    set(INPUT_URL "https://adventofcode.com/${year}/day/${day}/input")
    set(HEADER "Cookie: ${SESSION_COOKIE}")
    set(OUTPUT_FILE "${CMAKE_SOURCE_DIR}/inputs/${year}/year${year}_day${DAY_FILENAME}.txt")
    file(DOWNLOAD ${INPUT_URL} ${OUTPUT_FILE}
        HTTPHEADER ${HEADER}
        STATUS DOWNLOAD_STATUS)
    list(GET DOWNLOAD_STATUS 0 DOWNLOAD_RESULT)
    if (NOT DOWNLOAD_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to download file from ${INPUT_URL}.")
    endif()

    message(STATUS "Generated ${OUTPUT_H_FILE} and ${OUTPUT_CPP_FILE} for 12/${day}/${year}.")
    message(STATUS "Downloaded input from ${INPUT_URL} to ${OUTPUT_FILE}.")
endfunction()


generate_day(${DAY} ${YEAR})

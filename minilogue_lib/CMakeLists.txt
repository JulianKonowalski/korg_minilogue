set(INCLUDE_DIR_PATH ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(
  MINILOGUE_LIB
  STATIC
)

set(
  MINILOGUE_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/src/Minilogue.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/VCO.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/Voice.cpp
)

target_sources(
  MINILOGUE_LIB
  PRIVATE 
  ${MINILOGUE_SOURCES}
)

target_include_directories(
  MINILOGUE_LIB
  PUBLIC
  ${INCLUDE_DIR_PATH}
)
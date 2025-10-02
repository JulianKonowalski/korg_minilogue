cmake_minimum_required(VERSION 3.22)
project(MINILOGUE_VST VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_subdirectory(JUCE)

juce_add_plugin(MINILOGUE_VST
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "Minilogue"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
    # COPY_PLUGIN_AFTER_BUILD TRUE/FALSE        # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE Juce               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Dem0                            # A unique four-character plugin id with exactly one upper-case character
                                                # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
    FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    PRODUCT_NAME "Minilogue")                   # The name of the final executable, which can differ from the target name

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
target_sources(MINILOGUE_VST PRIVATE ${SRC_FILES})
target_include_directories(MINILOGUE_VST PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(MINILOGUE_VST
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_compile_definitions(MINILOGUE_VST
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

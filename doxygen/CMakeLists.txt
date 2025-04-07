# add doxygen-awesome theme
include(FetchContent)
FetchContent_Declare(
    doxygen-awesome-css
    URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v2.3.4.zip
)
FetchContent_MakeAvailable(doxygen-awesome-css)

# Save the location the files were cloned into
# This allows us to get the path to doxygen-awesome.css
FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

# Generate the Doxyfile based on Doxyfile.in
set(DOXYFILE_IN  ${PROJECT_SOURCE_DIR}/doxygen/Doxyfile.in)
set(DOXYFILE_OUT ${PROJECT_SOURCE_DIR}/doxygen/Doxyfile)
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

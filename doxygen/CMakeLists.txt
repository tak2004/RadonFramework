ADD_CUSTOM_TARGET(Documentation ${DOXYGEN_EXECUTABLE} "${PROJECT_SOURCE_DIR}/doxygen/documentation"
                  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/doxygen/")
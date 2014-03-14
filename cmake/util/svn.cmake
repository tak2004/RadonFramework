#
# This module will looking for svn command line executable and
# obtain the svn revision and build version number of a specified repo.
#
FIND_PROGRAM(SVN_EXECUTABLE svn DOC "subversion command line client")
mark_as_advanced(SVN_EXECUTABLE)

MACRO(Subversion_GET_REVISION dir variable)
  EXECUTE_PROCESS(COMMAND ${SVN_EXECUTABLE} info ${dir}
	OUTPUT_VARIABLE ${variable}
	OUTPUT_STRIP_TRAILING_WHITESPACE)
  STRING(REGEX REPLACE "^(.*\n)?Revision: ([^\n]+).*"
	"\\2" ${variable} "${${variable}}")
	IF("${variable}" STREQUAL "")
		SET(${variable} "0")
	ENDIF("${variable}" STREQUAL "")
ENDMACRO(Subversion_GET_REVISION)
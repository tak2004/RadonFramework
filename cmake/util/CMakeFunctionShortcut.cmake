#
# This file contains functions which need more then 1 line in cmake.
# contact at http://www.radonframework.org
#
macro(rf_replace_flag flagcontainer oldflag newflag)
# replace all flags on the beginning till last flag
if(${flagcontainer} MATCHES "${oldflag} ")
  string(REPLACE "${oldflag}" "${newflag}" ${flagcontainer} "${flagcontainer}")
endif()
# replace the the flag if it's the last one
if(${flagcontainer} MATCHES "${oldflag}$")
  string(REPLACE "${oldflag}" "${newflag}" ${flagcontainer} "${flagcontainer}")
endif()
endmacro()
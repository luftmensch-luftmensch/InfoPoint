#
# Print a message only if the `VERBOSE_OUTPUT` option is on
#

function(verbose_message content)
  if(${PROJECT_NAME}_VERBOSE_OUTPUT)
    message(STATUS ${content})
  endif()
endfunction()

# function(verbose_message_info sources headers)
#   list(LENGTH ${sources} len1)
#   message(${len1})
#   
#   if(${PROJECT_NAME}_VERBOSE_OUTPUT)
#     verbose_message("Found the following sources:")
#     foreach(source ${sources})
#       verbose_message("* ${source}")
#     endforeach()
# 
#     verbose_message("Found the following headers:")
#     foreach(source "${headers}")
#       verbose_message("* ${headers}")
#     endforeach()
#   endif()
# endfunction()

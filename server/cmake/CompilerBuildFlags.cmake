function(set_project_build_flags project_name)
  set(MSVC_BUILD_FLAG
      /W4     # Baseline reasonable warnings
      /w14242 # 'identifier': conversion from 'type1' to 'type1', possible loss
              # of data
      /w14254 # 'operator': conversion from 'type1:field_bits' to
              # 'type2:field_bits', possible loss of data
      /w14263 # 'function': member function does not override any base class
              # virtual member function
      /w14265 # 'classname': class has virtual functions, but destructor is not
              # virtual instances of this class may not be destructed correctly
      /w14287 # 'operator': unsigned/negative constant mismatch
      /we4289 # nonstandard extension used: 'variable': loop control variable
              # declared in the for-loop is used outside the for-loop scope
      /w14296 # 'operator': expression is always 'boolean_value'
      /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
      /w14545 # expression before comma evaluates to a function which is missing
              # an argument list
      /w14546 # function call before comma missing argument list
      /w14547 # 'operator': operator before comma has no effect; expected
              # operator with side-effect
      /w14549 # 'operator': operator before comma has no effect; did you intend
              # 'operator'?
      /w14555 # expression has no effect; expected expression with side- effect
      /w14619 # pragma warning: there is no warning number 'number'
      /w14640 # Enable warning on thread un-safe static member initialization
      /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may
              # cause unexpected runtime behavior.
      /w14905 # wide string literal cast to 'LPSTR'
      /w14906 # string literal cast to 'LPWSTR'
      /w14928 # illegal copy-initialization; more than one user-defined
              # conversion has been implicitly applied
      /permissive- # standards conformance mode for MSVC compiler.
  )

  set(CLANG_BUILD_FLAGS
      -Wall
      -Wextra  # reasonable and standard
      -Wshadow # warn the user if a variable declaration shadows one from a
               # parent context
      -Wnon-virtual-dtor # warn the user if a class with virtual functions has a
                         # non-virtual destructor. This helps catch hard to
                         # track down memory errors
      -Wold-style-cast # warn for c-style casts
      -Wcast-align     # warn for potential performance problem casts
      -Wunused         # warn on anything being unused
      -Woverloaded-virtual # warn if you overload (not override) a virtual
                           # function
      -Wpedantic   # warn if non-standard C++ is used
      -Wconversion # warn on type conversions that may lose data
      -Wsign-conversion  # warn on sign conversions
      -Wnull-dereference # warn if a null dereference is detected
      -Wdouble-promotion # warn if float is implicit promoted to double
      -Wformat=2 # warn on security issues around functions that format output
                 # (ie printf)
  )

  # Full list here -> https://gcc.gnu.org/onlinedocs/gcc/Invoking-GCC.html
  set(GCC_BUILD_FLAGS
      ### BASICS ###
      -Wall              # Enables a base set of warnings generally agreed upon as being useful and easy to fix
      -Wextra            # Enables an additional set of flags not covered by -Wall
      -Wshadow           # Shadowing variables at the very least makes code difficult to read and often can be indicative of a bug because the code is not operating on the value the programmer expects
      -Wdouble-promotion # C type float and double are not the same! (When using floating point numbers in a project, it’s quite easy to unintentionally use a double, so don't forget the f after a float number)
      ### Formatter checks ###
      -Wformat=2 # Warn on security issues around functions that format output (ie printf)
      -Wformat-truncation # The options are able to detect various types of buffer overflows and truncation that could arise when using routines such as sprintf and snprintf respectively
      -Wformat-overflow
      -Wundef    # A classic bug in C code is an undefined macro silently evaluating as 0 and causing unexpected behavior (In general, it’s advisable to use #ifdef sparingly in a project for these reasons.)
      -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
      
      -Wduplicated-cond     # Warn if if / else chain has duplicated conditions
      -Wduplicated-branches # Warn if if / else branches have duplicated code
      -Wlogical-op          # Warn about suspicious uses of logical operators in expressions

      ### Optimization & Sections ###
      -O2
      # By default the linker will place all functions in an object within the same linker “section”. This becomes very clear when examining the mapfile and seeing a bunch of symbols in the .text section.
      # With this option each functions gets its own section
      -ffunction-sections 
      #--gc-sections # Enable optimization using the linker gc
  )

  if (${PROJECT_NAME}_WARNINGS_AS_ERRORS)
    set(GCC_BUILD_FLAGS   ${GCC_BUILD_FLAGS} -Werror)
    set(CLANG_BUILD_FLAGS ${CLANG_BUILD_FLAGS} -Werror)
    set(MSVC_BUILD_FLAG   ${MSVC_BUILD_FLAG} /WX)
  endif()

  if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(GCC_WARNINGS
      ${GCC_BUILD_FLAGS}
      -g3                  # Produces debugging information (Useful w/ gdb)
      --print-gc-sections  # Diagnostic logs about sections
      )
  endif()

  if(MSVC)
    set(PROJECT_BUILD_FLAG ${MSVC_BUILD_FLAG})

  elseif(CMAKE_C_COMPILER_ID MATCHES ".*Clang")
    set(PROJECT_BUILD_FLAG ${CLANG_BUILD_FLAGS})

  elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(PROJECT_BUILD_FLAGS ${GCC_BUILD_FLAGS})

  else()
    message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_C_COMPILER_ID}' compiler.")
  endif()

  if(${PROJECT_NAME}_BUILD_HEADERS_ONLY)
        target_compile_options(${project_name} INTERFACE ${PROJECT_BUILD_FLAGS})
  else()
        target_compile_options(${project_name} PUBLIC ${PROJECT_BUILD_FLAGS})
  endif()

  if(NOT TARGET ${project_name})
    message(AUTHOR_WARNING "${project_name} is not a target, thus no compiler warning were added.")
  endif()

endfunction()

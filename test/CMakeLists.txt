PROJECT(bitcoin)

aux_source_directory(. test_sources)

foreach(file ${test_sources})
    STRING( REGEX REPLACE ".cpp$" "" tmpStr ${file} )
    STRING( REGEX REPLACE "^./" "" test_bin_name ${tmpStr} )
    add_executable(${test_bin_name} ${file})
    target_link_libraries(${test_bin_name} bitcoin boost_system boost_filesystem boost_thread boost_program_options)
endforeach(file)

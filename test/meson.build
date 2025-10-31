fs = import('fs')

tests = files(
  'dir.c',
)

foreach file : tests
  test = file.full_path()
  
  e = executable(
  	fs.stem(test),
    test, 
  	include_directories: incdir,
  	link_with: C_xdg_base_directory,
  )

  test(
    fs.stem(test),
    e,
  )
endforeach

add_library(src
  math/complex.cpp
  math/complex.h
  bmp/bmp.cpp
  bmp/bmp.h
)

add_executable(md main.cpp)
target_link_libraries(md src)
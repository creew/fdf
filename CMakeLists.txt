cmake_minimum_required(VERSION 3.14)
project(fdf C)

set(CMAKE_C_STANDARD 11)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

add_executable(fdf
        srcs/fdf.c
        srcs/read_map.c
        srcs/draw_main.c
        srcs/init_images.c
        srcs/mouse_moves.c
        srcs/getters.c
        srcs/transforms.c
        srcs/draw_line.c
        srcs/mouse_hook.c
        srcs/key_hook.c
        srcs/colorize_map.c
        srcs/normalize_map.c
        srcs/do_transform.c
        srcs/draw_woo.c
        srcs/other_hooks.c
        srcs/setters.c
        )

include_directories(.
        ./includes
        ./libft/includes
        ./ft_printf/includes)

if (LINUX)
    include_directories(./minilibx)
    find_library(MLX mlx ./minilibx)
    find_library(XEXT Xext /usr/lib/x86_64-linux-gnu/)
    find_library(X11 X11 /usr/lib/x86_64-linux-gnu/)
    target_link_libraries(fdf ${XEXT} ${X11})
else()
    include_directories(./minilibx_macos)
    find_library(MLX mlx ./minilibx_macos)
    target_link_libraries(fdf "-framework AppKit" "-framework OpenGL")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libft ft)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ft_printf ftprintf)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/minilibx_macos mlx)
target_link_libraries(fdf ft ftprintf mlx)
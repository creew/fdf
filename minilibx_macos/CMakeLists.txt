cmake_minimum_required(VERSION 3.15)
project(mlx C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_library(mlx
        mlx_shaders.c
        mlx_new_window.m
        mlx_init_loop.m
        mlx_new_image.m
        mlx_xpm.c
        mlx_int_str_to_wordtab.c
        )

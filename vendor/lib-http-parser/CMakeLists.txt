cmake_policy(VERSION 2.8)
project(http_parser)

add_library(http_parser STATIC http_parser.c http_parser.h)

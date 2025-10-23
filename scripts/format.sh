#!/usr/bin/env bash 

find {src,include} -type f -exec clang-format -i --style=file {} +


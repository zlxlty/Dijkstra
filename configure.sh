#!/bin/bash
###
 # @Author: Tianyi Lu
 # @Description: 
 # @Date: 2021-10-09 19:34:00
 # @LastEditors: Tianyi Lu
 # @LastEditTime: 2021-10-10 09:12:51
### 

if [[ ! -d build ]]
then
    mkdir build
fi

if [[ ! -d bin ]]
then
    mkdir bin
fi

cmake -S . -B ./build

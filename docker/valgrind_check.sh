#!/usr/bin/env sh

valgrind aart_generator /logo.png 8 && valgrind aart_viewer ./logo.aart

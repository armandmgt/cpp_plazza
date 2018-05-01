#!/bin/bash

g++ -I include/ -Wall -Wextra -std=c++14 `pkg-config gtkmm-3.0 --cflags --libs` gui/Graphic.cpp -o plazza
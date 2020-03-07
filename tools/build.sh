#!/bin/bash

source /etc/profile_qt5.14

qmake -o Makefile EScreenShot.pro


make -j4 \
	&& rm -rf .qmake.stash \
	&& ./release/EScreenShot


#!/bin/bash

if [ -d "${ARDUPI_HOME}/lib" ] ; then
	echo "Cleaning lib"
	rm -rf ${ARDUPI_HOME}/lib
fi
if [ -d "${ARDUPI_HOME}/include" ] ; then
	echo "Cleaning include"
	rm -rf ${ARDUPI_HOME}/include
fi

#!/bin/bash

# This is a poor-man's driver script

DRIVER_SCRIPT_DIR=`echo $0 | sed "s/\(.*\)\/.*\.sh/\1/g"`
echo "DRIVER_SCRIPT_DIR = '$DRIVER_SCRIPT_DIR'"

TRILINOS_DIR=`readlink -f ${DRIVER_SCRIPT_DIR}/../../../..`
echo "TRILINOS_DIR='${TRILINOS_DIR}'"

source /etc/bashrc
source $TRILINOS_DIR/cmake/load_ci_sems_dev_env.sh

export CTEST_DASHBOARD_ROOT=$PWD

#echo ctest -V -S $DRIVER_SCRIPT_DIR/ctest_linux_mpi_debug_shared_pt_ci.sems.cmake
ctest -V -S $DRIVER_SCRIPT_DIR/ctest_linux_mpi_debug_shared_pt_ci.sems.cmake

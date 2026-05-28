#!/bin/sh

# Note: If you decide to copy and paste commands from this script to the terminal directly, then open a terminale in the "/qmtech-c5soc-kfb-linux-build-env/SCRIPTS" folder and then copy and paste the entire section of statements 

# 0. Set the Project's 'Top' directory - this is the folder that contains the GSRD, Software, Tools, etc. 
export BUILD_SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd ) # The script must be placed at the top/overhead place
cd $BUILD_SCRIPT_DIR/..
export BUILD_TOP_FOLDER=`pwd`
export GHRD_SRC_DIR="$BUILD_TOP_FOLDER/SOURCES/qmtech-c5soc-kfb-dual-sdram-ghrd"  # 'main' branch (take the latest commit)
export APPS_PROJS_TOP_DIR="$BUILD_TOP_FOLDER/SOURCES/linux-applications" 
export APPS_PROJS_SOPCINFO_DIR="$APPS_PROJS_TOP_DIR/sopcinfo" 


# Runs the Nios2 setup script in a throwaway subshell that tricks it into
# computing its paths correctly, then copies the resulting environment back
# into the current shell — so you get all PATH and variable changes without
# ever leaving or nesting your shell.
bash() { :; }       # no-op for the final 'bash' call
export -f bash      # propagate it to the subshell
eval "$(command bash -c 'source "$0" >&2; export -p' \
    "$SOPC_KIT_NIOS2/nios2_command_shell.sh" 2>/dev/null)"
unset -f bash       # restore real bash


# Go to the Linux applications top projects folder - sopcinfo system (header) folder
cd $APPS_PROJS_SOPCINFO_DIR
sopc-create-header-files \
"${GHRD_SRC_DIR}/qsys/soc_system.sopcinfo" \
--single "${APPS_PROJS_SOPCINFO_DIR}/hps_0.h" \
--module hps_0
sync



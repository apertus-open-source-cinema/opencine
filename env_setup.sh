#!/bin/bash
if [ $(uname -s) == "Linux" ]; then
    declare -a distributions=("Manjaro" "Ubuntu" "Arch");
    declare -a distpackagemgrs=("1" "0" "1");
    declare -a packagemgr=("apt-get" "pacman");

    dist_count=${#distributions[*]}
    usable_mgr="-1"

    dist_name=$(lsb_release -a);

    for (( i=0; i<=$(( $dist_count -1 )); i++ ))
        do
        if [ $(echo "$dist_name" | grep -c "${distributions[$i]}") -gt 0 ]; then
            usable_mgr=${distpackagemgrs[$i]}
            echo "Found Distribution ${distributions[$i]}, will use ${packagemgr[usable_mgr]}"
        fi
    done

    if [ $usable_mgr == "-1" ]; then
        echo "Err: Linux distibution unknown, will use apt-get"
        usable_mgr="0"
    fi

    case $usable_mgr in
        "0")
        echo "-- apt-get install --"
        sudo apt-get install git cmake build-essential freeglut3-dev libavformat-dev libswscale-dev libavfilter-dev libavdevice-dev libavresample-dev

        ;;
        "1")
        echo "-- pacman installation --"
        sudo pacman -S git cmake base-devel freeglut ffmpeg

        ;;
    esac
fi
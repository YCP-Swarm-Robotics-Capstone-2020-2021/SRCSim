#!/bin/bash -e

print_help(){
    echo
    echo "This is a script that builds the swarm debians."
    echo "          --help    | -h        Prints this message."
    echo "          --dolphin | -d        Pass in the number of the dolphin you wish to "
}

ID=-1
DOLPHIN_ID="Dolphin"
while [[ "$1" =~ ^- && ! "$1" == "--" ]]; do
    case $1 in
	-h | --help )
	    print_help
	    exit 0
	    ;;
	-d | --dolphin )
	    shift;
	    ID=$1
	    DOLPHIN_ID="Dolphin$1"
   	    echo "Building debian for $DOLPHIN_ID"
	    ;;
	* )
	    print_help
	    exit 1
	    ;;
    esac; shift; done
if [[ "$1" == '--' ]]; then shift; fi

if [[ ID -eq -1 ]]; then
   echo "Error. Please input a dolphin id."
   print_help
   exit -1
fi
dst_dir=dolphin${ID}_swarm-robotics-software

if [[ -e $dst_dir ]]; then
    rm -rf $dst_dir
fi

#Make the build directories
mkdir $dst_dir
mkdir $dst_dir/usr
mkdir $dst_dir/usr/bin
mkdir $dst_dir/DEBIAN
cp ../missions/control $dst_dir/DEBIAN

#Build the binaries and the configuration file
cd ../missions
/bin/bash launch_vehicle.sh -i $DOLPHIN_ID -D -b

echo "Moving targ_$DOLPHIN_ID.moos to ../build/$dst_dir/usr/bin"
cp targ_$DOLPHIN_ID.moos ../build/$dst_dir/usr/bin

cd ../modules

binlist=("./GPIOController" "./HealthManager" "./Pos_module" "./VehicleStateMachine" "./MotionController")
for i in "${binlist[@]}"; do
    echo "cp $i/bin/* ../build/$dst_dir/usr/bin"
    cp $i/bin/* ../build/$dst_dir/usr/bin
done

cd ../build
dpkg-deb --build $dst_dir
rm -rf $dst_dir

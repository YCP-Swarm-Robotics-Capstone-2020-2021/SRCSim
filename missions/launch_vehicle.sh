#!/bin/bash
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
NUM_BOTS=5
BUILD_MODE=0
KAPPA=1
DT=1
JUST_MAKE="no"
LAUNCH_GUI="yes"
version=0.0.1
VNAME=$ID
deployment=0

print_help(){
    echo
    echo "This is a script that will run multiple vehicle simulations. Pass the below arguments to customize how the simulation launches. The most importanct parameter is the num_bots flag."
    echo "      --num_bots | -n         This flag sets how many robots you want the simulation to launch."
    echo "      --keep     | -k         Pass this flag to ensure that the world files are not deleted."
    echo "      --build    | -b         Pass this flag to only build"
    echo "      --dt       | -d         Pass this flag to edit dt"
    echo "      --kappa    | -K         Pass this flag to edit kappa"
    echo
    exit 0
}

while [[ "$1" =~ ^- && ! "$1" == "--" ]]; do case $1 in
  -V | --version )
    echo $version
    exit
    ;;
  -h | --help )
    print_help
    ;;
  -k | --keep )
    print_help
    ;;
  -n | --num_bots )
    shift;
    NUM_BOTS=$1
    echo "Num Bots = $NUM_BOTS"
    ;;
  -b | --build )
    BUILD_MODE=1
    echo "Build only"
    ;;
  -d | --dt )
    shift;
    DT=$1
    ;;
  -K | --kappa )
    shift;
    KAPPA=$1
    ;;
  -i | --id )
    shift;
    VNAME=$1
    ;;
  -D | --deploy )
    deployment=1
    ;;
  * )
    print_help
    exit 1
    ;;
esac; shift; done
if [[ "$1" == '--' ]]; then shift; fi

#get version number
version_number=`git rev-parse --short HEAD`
commit_message=`git show-branch --no-name HEAD`
cd ../missions/

#-------------------------------------------------------
#  Part 2: Create the .moos and .bhv files.
#-------------------------------------------------------
#PATH='../../../missions/$title'
if [[ ! -d "./logs" ]]; then
    mkdir logs
fi
if [[ ! BUILD_MODE  -eq 1 ]]; then
    cd ./logs
    mission_dir=$(date +'%F-%H-%M-%S_Mission_Numbots-')
    mission_dir=$mission_dir$NUM_BOTS
    mkdir $mission_dir
    cd ../
fi


V1PORT="9000"


GCSIP="192.168.1.110"
GCSPORT=9000
BROADCASTNUM=1

#nsplug meta_vehicle.moos targ_$VNAME2.moos -f WARP=$TIME_WARP \
#    VNAME=$VNAME2          VPORT="8310" \
#    GCSIP=$GCSIP           GCSPORT=$GCSPORT    \
#    BROADCASTNUM=$BROADCASTNUM                   VIP=$VIP
VPORT=9000
UPDATEPOSE=""
VIP="localhost"
cat > plug_VehiclepShare.moos <<EOF
ProcessConfig = pShare
{
     Input=route=localhost:\$(VPORT)
     Output=src_name=PROC_WATCH_SUMMARY,dest_name=PROC_WATCH_DOLPHIN,route=\$(GCSIP):\$(GCSPORT)
     Output=src_name=Narwhal_Current_State,dest_name=Current_State,route=\$(GCSIP):\$(GCSPORT)
     Output=src_name=Reg_In,route=\$(GCSIP):\$(GCSPORT)
     Output=src_name=Speed_Curv,route=\$(GCSIP):\$(GCSPORT)
     Output=src_name=WCA_MESSAGE,route=\$(GCSIP):\$(GCSPORT)
     Output=src_name=VERSION_NUMBER,route=\$(GCSIP):\$(GCSPORT)
EOF
PORT=9000
VIP2="192.168.1."
VIPEND=110
for ((i=0 ; i < $NUM_BOTS ; i++)); do
VIPEND=$(($VIPEND+5))
cat >> plug_VehiclepShare.moos <<EOF
     Output=src_name=Dolphin${i}_Neighbor_Zeta,dest_name=Neighbor_Zeta,route=${VIP2}${VIPEND}:$PORT
EOF
done
cat >> plug_VehiclepShare.moos <<EOF
}
EOF

PORT=9000

if [[ deployment -eq 1 ]]; then
    echo "Building with deployment options."
    nsplug meta_vehicle_production.moos targ_$VNAME.moos -f WARP=$TIME_WARP \
        VNAME=$VNAME                                 VPORT=$PORT \
        GCSIP=$GCSIP                                 GCSPORT=$GCSPORT \
        BROADCASTNUM=$BROADCASTNUM                   VIP=$VIP \
        KAPPA=$KAPPA                                 DT=$DT  \
	LOG_DIR=$mission_dir                         VERSION=$version_number \
	MESSAGE=$commit_message
else
    nsplug meta_vehicle.moos targ_$VNAME.moos -f WARP=$TIME_WARP \
        VNAME=$VNAME                                 VPORT=$PORT \
        GCSIP=$GCSIP                                 GCSPORT=$GCSPORT \
        BROADCASTNUM=$BROADCASTNUM                   VIP=$VIP \
        KAPPA=$KAPPA                                 DT=$DT  \
	LOG_DIR=$mission_dir                         VERSION=$version_number \
	MESSAGE=$commit_message
fi
#-------------------------------------------------------
#  Part 3: Build the modules
#-------------------------------------------------------
cd ../modules
for i in ./*; do
    if [[ -d $i ]]; then
	if [[ "$i" != "./Images" && "$i" != "./SwarmHandler" && "$i" != "./StageInterface" && "$I" != "./ControlGUI" && "$i" != "./UserInterface" ]]; then
	    cd $i
	    qmake
	    make
	    cd ..
	fi
    fi
done
cd ../missions
if [[ BUILD_MODE -eq 1 ]]; then echo "Done building";
else
#-------------------------------------------------------
#  Part 4: Launch the processes
#-------------------------------------------------------
printf "Launching ${VNAME} MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_${VNAME}.moos >& /dev/null &
printf "Done \n"
fi


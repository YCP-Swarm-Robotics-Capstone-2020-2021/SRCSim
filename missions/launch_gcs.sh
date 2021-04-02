#!/bin/bash -e
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
#  Part 3: Create the .moos and .bhv files.
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

GCSNAME="Narwhal"
GCSIP="localhost"
GCSPORT=9000
VIP="localhost"
BROADCASTNUM=1

#nsplug meta_vehicle.moos targ_$VNAME2.moos -f WARP=$TIME_WARP \
#    VNAME=$VNAME2          VPORT="8310" \
#    GCSIP=$GCSIP           GCSPORT=$GCSPORT    \
#    BROADCASTNUM=$BROADCASTNUM                   VIP=$VIP
PORT=8300
UPDATEPOSE=""
cat > plug_GCSpShare.moos <<EOF
ProcessConfig = pShare
{
     Input = route=\$(GCSIP):\$(GCSPORT)

EOF
VIP="192.168.1."
VIPEND=110
for ((i = 0 ; i < 2 ; i++)); do
VIPEND=$(($VIPEND+5))
cat >> plug_GCSpShare.moos <<EOF
     Output = src_name=Change_State, route=${VIP}${VIPEND}:9000
     Output = src_name=LOG_BOOKMARK, route=${VIP}${VIPEND}:9000
     Output = src_name=BOUNDARY_SIZE, route=${VIP}${VIPEND}:9000
     Output = src_name=RUN_ENDED, route=${VIP}${VIPEND}:9000
     Output = src_name=RUN_STARTED, route=${VIP}${VIPEND}:9000
     Output = src_name=MAX_SPEED, route=${VIP}${VIPEND}:9000
     Output=src_name=Dolphin${i}_Update_Pos,dest_name=Update_Pos,route=${VIP}${VIPEND}:9000
     Output=src_name=Dolphin${i}_Change_State,dest_name=Change_State,route=${VIP}${VIPEND}:9000
     Output=src_name=Dolphin${i}_Reg_Ack,dest_name=Reg_Ack,route=${VIP}${VIPEND}:9000
     Output=src_name=Dolphin${i}_Neighbor_Zeta,dest_name=Neighbor_Zeta,route=${VIP}${VIPEND}:9000
     Output=src_name=Dolphin${i}_Zeta_Init,dest_name=Zeta_Init,route=${VIP}${VIPEND}:9000
     Output=src_name=Dolphin${i}_Speed_Curv,dest_name=Speed_Curv_Override,route=${VIP}${VIPEND}:9000
     Output=src_name=Dolphin${i}_BLACK_LINE_DETECTED,dest_name=BLACK_LINE_DETECTED,route=${VIP}${VIPEND}:9000
     Output=src_name=Dolphin${i}_VERSION_ACK,dest_name=VERSION_ACK,route=${VIP}${VIPEND}:9000

EOF
done
cat >> plug_GCSpShare.moos <<EOF
}
EOF

GCSARGS="NUMBOTS=$NUM_BOTS              GCSNAME=$GCSNAME \
GCSIP=$GCSIP           			GCSPORT=$GCSPORT    \
BROADCASTNUM=$BROADCASTNUM                   VIP=$VIP \
UPDATEPOSE=$UPDATEPOSE                      WORLDFILE="NA" LOG_DIR=$mission_dir"

nsplug meta_GroundControlStation_Production.moos targ_$GCSNAME.moos -f WARP=$TIME_WARP \
    $GCSARGS

if [ ! -e targ_$GCSNAME.moos ]; then echo "no targ_$GCSNAME.moos";  exit; fi

#-------------------------------------------------------
#  Part 3: Build the modules
#-------------------------------------------------------
cd ../modules
cd ControlGUI
qmake
make
cd ..
cd SwarmHandler
qmake
make
cd ..
cd CameraInterface
qmake
make
cd ../../missions
cd ../missions
if [[ BUILD_MODE -eq 1 ]]; then exit 1; fi
#-------------------------------------------------------
#  Part 4: Launch the processes
#-------------------------------------------------------
printf "Launching $GCSNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_$GCSNAME.moos >& /dev/null &
printf "Done \n"

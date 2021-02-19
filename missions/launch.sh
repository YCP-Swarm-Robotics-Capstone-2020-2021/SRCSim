1#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
NUM_BOTS=2
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

#-------------------------------------------------------
#  Part 2: Create the .world file
#-------------------------------------------------------
title=$(date "+%Y_%m_%d_%H_%M_%S")___$NUM_BOTS.world
echo $title
cd ../world/
cat > $title << EOF
include "/usr/local/share/stage/worlds/pioneer.inc"
include "/usr/local/share/stage/worlds/map.inc"
include "sick.inc"

quit_time 3600
paused 1
resolution 0.0762
speedup 1
window
(
  size [ 635.000 666.000 ] # in pixels
  scale 36.995   # pixels per meter
  center [ -0.040  -0.274 ]
  rotate [ 0  0 ]

  show_data 1              # 1=on 0=off
)
floorplan
(
  name "void"
  size [16.000 16.000 0.800]
  pose [0 0 0 0]
  bitmap "bittymaps/blank.png"
)
EOF
x=-7
y=7
for ((i = 0 ; i < $NUM_BOTS ; i++)); do
x=$(($x+3))
if [[ $x -gt 8 ]]; then
    y=$(($y-2))
    x=-7
fi
cat >> $title << EOF
pioneer2dx
(
  # can refer to the robot by this name
  name "Dolphin$i"
  pose [ $x $y 0 90.0 ]
  sicklaser( pose [ 0 0 0 0 ] ) 
  drive "omni"
  # report error-free position in world coordinates
  localization "gps"
  localization_origin [ 0 0 0 0 ]

  trail_length 400
)
EOF
done
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

WORLDFILE="../world/$title"
VNAME1="Dolphin0"           # The first vehicle Community
V1PORT="8305"
VNAME2="Dolphin1"           # The second vehicle Community
V2PORT="8310"
VNAME3="Dolphin2"           # The third vehicle Community
V3PORT="8315"
VNAME4="Dolphin3"           # The fourth vehicle Community
V4PORT="8320"
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
     Input = route=multicast_\$(BROADCASTNUM)
     Output = src_name=Change_State, route=multicast_\$(BROADCASTNUM)
     Output = src_name=LOG_BOOKMARK, route=multicast_\$(BROADCASTNUM)
     Output = src_name=BOUNDARY_SIZE, route=multicast_\$(BROADCASTNUM)
     Output = src_name=RUN_ENDED, route=multicast_\$(BROADCASTNUM)
     Output = src_name=RUN_STARTED, route=multicast_\$(BROADCASTNUM)
EOF
for ((i = 0 ; i < $NUM_BOTS ; i++)); do
    PORT=$(($PORT+5))
cat >> plug_GCSpShare.moos <<EOF
     Output=src_name=Dolphin${i}_Update_Pos,dest_name=Update_Pos,route=localhost:$PORT
     Output=src_name=Dolphin${i}_Change_State,dest_name=Change_State,route=localhost:$PORT
     Output=src_name=Dolphin${i}_Reg_Ack,dest_name=Reg_Ack,route=localhost:$PORT
     Output=src_name=Dolphin${i}_Neighbor_Zeta,dest_name=Neighbor_Zeta,route=localhost:$PORT
     Output=src_name=Dolphin${i}_Zeta_Init,dest_name=Zeta_Init,route=localhost:$PORT
     Output=src_name=Dolphin${i}_Speed_Curv,dest_name=Speed_Curv_Override,route=localhost:$PORT
     Output=src_name=Dolphin${i}_BLACK_LINE_DETECTED,dest_name=BLACK_LINE_DETECTED,route=localhost:$PORT
     Output=src_name=Dolphin${i}_VERSION_ACK,dest_name=VERSION_ACK,route=localhost:$PORT
     Output=src_name=Dolphin${i}_OBJECT_DETECTED,dest_name=OBJECT_DETECTED,route=localhost:$PORT
EOF
done
cat >> plug_GCSpShare.moos <<EOF
}
EOF

cat > plug_VehiclepShare.moos <<EOF
ProcessConfig = pShare
{
     Input=route=\$(VIP):\$(VPORT)
     Input=route=multicast_\$(BROADCASTNUM)

     Output=src_name=PROC_WATCH_SUMMARY,dest_name=PROC_WATCH_DOLPHIN,route=\$(GCSIP):\$(GCSPORT)
     Output=src_name=Narwhal_Current_State,dest_name=Current_State,route=\$(GCSIP):\$(GCSPORT)
     Output=src_name=Reg_In,route=\$(GCSIP):\$(GCSPORT)
     Output=src_name=Speed_Curv,route=\$(GCSIP):\$(GCSPORT)
     Output=src_name=WCA_MESSAGE,route=\$(GCSIP):\$(GCSPORT)
     Output=src_name=VERSION_NUMBER,route=\$(GCSIP):\$(GCSPORT)
EOF
PORT=8300
for ((i=0 ; i < $NUM_BOTS ; i++)); do
    PORT=$(($PORT+5))
cat >> plug_VehiclepShare.moos <<EOF
     Output=src_name=Dolphin${i}_Neighbor_Zeta,dest_name=Neighbor_Zeta,route=localhost:$PORT
EOF
done
cat >> plug_VehiclepShare.moos <<EOF
}
EOF

GCSARGS="NUMBOTS=$NUM_BOTS              GCSNAME=$GCSNAME \
GCSIP=$GCSIP           GCSPORT=$GCSPORT    \
BROADCASTNUM=$BROADCASTNUM                   VIP=$VIP \
UPDATEPOSE=$UPDATEPOSE                      WORLDFILE=$WORLDFILE \
LOG_DIR=$mission_dir"

PORT=8300
for ((i = 0 ; i < $NUM_BOTS ; i++)); do
    PORT=$(($PORT+5))
    nsplug meta_vehicle.moos targ_Dolphin$i.moos -f WARP=$TIME_WARP \
        VNAME="Dolphin$i"                                 VPORT=$PORT \
        GCSIP=$GCSIP                                 GCSPORT=$GCSPORT \
        BROADCASTNUM=$BROADCASTNUM                   VIP=$VIP \
        KAPPA=$KAPPA                                 DT=$DT  \
	LOG_DIR=$mission_dir                         VERSION=$version_number \
	MESSAGE="$commit_message"
done
nsplug meta_GroundControlStation.moos targ_$GCSNAME.moos -f WARP=$TIME_WARP \
    $GCSARGS
    
for ((i = 0 ; i < $NUM_BOTS ; i++)); do
    if [ ! -e targ_Dolphin$i.moos ]; then echo "no targ_Dolphin$i.moos"; exit; fi
done
if [ ! -e targ_$GCSNAME.moos ]; then echo "no targ_$GCSNAME.moos";  exit; fi

#-------------------------------------------------------
#  Part 3: Build the modules
#-------------------------------------------------------
cd ../modules
for i in ./*; do
    if [[ -d $i ]]; then
	if [[ "$i" != "./Images" ]]; then
	    cd $i
	    qmake
	    make
	    cd ..
	fi
    fi
done
cd ../missions
if [[ BUILD_MODE -eq 1 ]]; then exit 1; fi
#-------------------------------------------------------
#  Part 4: Launch the processes
#-------------------------------------------------------
printf "Launching $GCSNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_$GCSNAME.moos >& /dev/null &
for ((i = 0 ; i < $NUM_BOTS ; i++)); do
    printf "Launching Dolphin$i MOOS Community (WARP=%s) \n" $TIME_WARP
    pAntler targ_Dolphin$i.moos >& /dev/null &
done
printf "Done \n"

#uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
#mykill; ktm
printf "Done killing processes.   \n"

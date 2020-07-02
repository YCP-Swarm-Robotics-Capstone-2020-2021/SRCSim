#!/bin/bash -e
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
JUST_MAKE="no"
LAUNCH_GUI="yes"
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	printf "%s [SWITCHES] [time_warp]   \n" $0
	printf "  --just_make, -j    \n" 
	printf "  --help, -h         \n" 
	printf "  --no_gui, -n       \n"
	exit 0;
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then 
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
	JUST_MAKE="yes"
    elif [ "${ARGI}" = "--no_gui" -o "${ARGI}" = "-n" ] ; then
	LAUNCH_GUI="no"
    else 
	printf "Bad Argument: %s \n" $ARGI
	exit 0
    fi
done

#-------------------------------------------------------
#  Part 2: Create the .moos and .bhv files. 
#-------------------------------------------------------
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

nsplug meta_vehicle.moos targ_$VNAME1.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME1                                VPORT="8305" \
    GCSIP=$GCSIP                                 GCSPORT=$GCSPORT \
    BROADCASTNUM=$BROADCASTNUM                   VIP=$VIP

nsplug meta_vehicle.moos targ_$VNAME2.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME2          VPORT="8310" \
    GCSIP=$GCSIP           GCSPORT=$GCSPORT    \
    BROADCASTNUM=$BROADCASTNUM                   VIP=$VIP

nsplug meta_GroundControlStation.moos targ_$GCSNAME.moos -f WARP=$TIME_WARP \
    NUMBOTS=2              GCSNAME=$GCSNAME \
    GCSIP=$GCSIP           GCSPORT=$GCSPORT    \
    BROADCASTNUM=$BROADCASTNUM                   VIP=$VIP \
    VNAME1=$VNAME1                               VNAME2=$VNAME2 \
    V1IP=$VIP                                    V1PORT=$V1PORT \
    V2IP=$VIP                                    V2PORT=$V2PORT 
    

if [ ! -e targ_$VNAME1.moos ]; then echo "no targ_$VNAME1.moos"; exit; fi
if [ ! -e targ_$VNAME2.moos ]; then echo "no targ_$VNAME2.moos"; exit; fi
if [ ! -e targ_$GCSNAME.moos ]; then echo "no targ_$GCSNAME.moos";  exit; fi

if [ ${JUST_MAKE} = "yes" ] ; then
    exit 0
fi


#-------------------------------------------------------
#  Part 3: Launch the processes
#-------------------------------------------------------
printf "Launching $GCSNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_$GCSNAME.moos >& /dev/null &
printf "Launching $VNAME1 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME1.moos >& /dev/null &
printf "Launching $VNAME2 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME2.moos >& /dev/null &
printf "Done \n"

#uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
mykill; ktm
printf "Done killing processes.   \n"

#!/bin/bash
TIME=10
if [ "$#" -gt 0 ]
then
	TIME=$((60*$1))
fi	

sleep $TIME
for((i=0; i<5; i++))
do
	/home/pi/git/raspi_plugin-switch_controller/raspidev/remote_switch A OFF
	sleep 2
done

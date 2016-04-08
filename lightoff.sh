TIME=10
if [ "$#" -gt 0 ]
then
	TIME=$((60*$1))
	if [ "$TIME" -gt 600 ]
	then
		TIME=600
	fi
fi	

sudo -v
sleep $TIME
for((i=0; i<5; i++))
do
	sudo $HOME/git/raspi_plugin-switch_controller/remote_switch A OFF
	sleep 2
done

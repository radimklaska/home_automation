Web cam panel.
============

Displays various live streams on hdmi in pixel perfect grid.

* Does not need GUI - use sudo raspi-config to disable it.
* Run it using: bash cam_grid.sh
* Or add it into crontab: @reboot bash /home/pi/cam_grid.sh 2>&1

Requirements:
* sudo apt-get update && sudo apt-get install omxplayer screen

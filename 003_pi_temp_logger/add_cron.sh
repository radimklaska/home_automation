#!/bin/sh
# Ensures that launcher.sh is run every time system starts.
# Run via sudo!

crontab -l | { cat; echo "@reboot sh /home/pi/temp_logger/launcher.sh 2>&1"; } | crontab -
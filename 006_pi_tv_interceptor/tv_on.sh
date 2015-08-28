#!/bin/bash

# Config:

# How long (s) should be the cam image displayed:
time_standby=60
time_on=5

# Code, no edits needed (if you are lucky) :-)

# Turn on TV and save the output.
tv_state="$(echo 'on 0' | cec-client -s | awk -v FS='\t' '{print $2}')"
tv_pwr="$(echo $tv_state | grep 'power status changed')"

if [[ $tv_pwr == *'in transition from standby to on'* ]]; then
  echo "TV was already off."

  # Show RPi output
  echo "as" | cec-client -s >/dev/null 2>&1
  echo "RPi output is beeing shown on TV."
  sleep $time_standby

  # Turn off TV.
  echo "standby 0" | cec-client -s >/dev/null 2>&1
  echo "TV should be off now."

else
  # This case is not fully functional yet.
  echo "TV was already ON."

  # Someone is probably watching something - let's not be so intrusive.
  # This:
  # echo "scan" | cec-client -s
  # displays sources connected to TV, but e.g. my Chromecast is listed as unknown + logic probably depends on your habits.
  #tv_source="$(echo "scan" | cec-client -s | grep 'currently active source')"
  #echo $tv_source

  # Switch to RPi
  echo "as" | cec-client -s >/dev/null 2>&1
  sleep $time_on

  # New we should switch back to tv_source, but I don't know how... :(

  # Switch to Chromecast. (Refer to scan command.)
  # 4 - the source
  # f - broadcast
  # 9d - <Inactive Source> command
  # 10 00 - physical address (ID) of currently active source = 1.0.0.0
  #echo 'tx 4f 9d 10 00' | cec-client -s
fi

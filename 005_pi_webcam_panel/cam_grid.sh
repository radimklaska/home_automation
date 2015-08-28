#!/bin/bash

# rk-cam1 Edimax
# top right:
#screen -dmS camera1 sh -c 'omxplayer -o hdmi -t 3600 --blank --live --fps 10 --win "640 0 1280 480" http://username:password@10.0.0.31:80/mjpg/video.mjpg; exec bash'
# fullscreen:
screen -dmS camera1 sh -c 'omxplayer -o hdmi -t 3600 --blank --live --fps 10 --win "0 0 1280 720" http://username:password@10.0.0.31:80/mjpg/video.mjpg; exec bash'

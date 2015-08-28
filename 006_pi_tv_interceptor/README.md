TV interceptor
============

This should run on the same Raspberry Pi as 005_pi_webcam_panel and turn on TV/intercept currently playing TV
for few seconds when something (eg. 004_ino_doorbell_with_mobile_phone_notification) happens.

It does not takes care about the triggering mechanism. - It's up to you to run this script.

This script uses Consumer Electronics Control (CEC) (part of HDMI specs) https://en.wikipedia.org/wiki/HDMI#CEC 
to control the TV.

Requirements:
* TV connected using hdmi.
* sudo apt-get update && sudo apt-get install cec-utils

Ideas:
* Use motion http://www.lavrsen.dk/foswiki/bin/view/Motion as trigger.
* Use 004_ino_doorbell_with_mobile_phone_notification as trigger.

ToDo:
* Fix switching input back when the TV was already playing something.
* Explore http://www.cec-o-matic.com/

Doorbell with mobile phone notification
============

Arduino monitors LED on the Bell (or anything really) with photocell. When LED blinks Arduino makes a request to pushingbox.com. There you can pick how to react on this event.

Demo: https://www.youtube.com/watch?v=8fBnqJvt_ys

Materials:
* Wireless Doorbel that can indicate by flashing light. 
* Arduino
* Arduino Ethernet shield
* Photocell

How To:
* Connect Arduino, Ethernet shield and Photocell - see photocell.gif
* Learn more about using photocells: https://learn.adafruit.com/photocells/using-a-photocell
* Attach photocell directly to doorbell light. Preferably using black electrical tape to prevent ambient light interfering.
* Register on https://pushingbox.com
* Add new device and note DeviceID: https://www.pushingbox.com/scenarios.php
* Fill in DeviceID in DEVID1 variable in code
* Run the code with debugging enabled.
* Ring the bell, figure out the threshold value and add it into the code. (threshold variable).
* Set the bell_duration variable in code. Tip: make it ~1s longer than the bell actually rings.
* Pushingbox box should be now able to register the doorbell.
* Add "Reactions" https://www.pushingbox.com/services.php and attach them to pushingbox device.
* TIP: https://www.pushbullet.com/ can do notifications to Android/iPhone/PC etc.
* TIP: Authorize multiple Pushbullet accounts to Pushingbox to allow other people to get the notigication.
* TIP: If you have public webcam Pushingbox can attach an image to the notification.

Credits:
* Connection diagram, photocell snippets: https://learn.adafruit.com/photocells/using-a-photocell
* PushingBox code: https://github.com/Clement87/PushingBox-for-Arduino

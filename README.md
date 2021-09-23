# MiniHoopTracker

October 2020


![20200425_211651](https://user-images.githubusercontent.com/72897159/134527189-15478a2b-4f57-4388-af86-e98161d7d0f5.jpg)



Youtube Demonstration: https://www.youtube.com/watch?v=VsOM16-T-PU

Extra Images Link: https://drive.google.com/drive/u/2/folders/1ssZ8SuUYN1haxjPsAh7jhmlVfP83LuEI

A system that is attached to the basketball mini hoop, which counts all the shot attempts as well as shots made. In total, this leads to a "Field-Goal Percentage" which will be displayed to the right of the shots made and total shots counter. All the tracking is handled by two individual sensors, the HC-SR04 (Ultrasonic distance sensor) and the MPU-6050 (accelerometer and gyro). These two sensors track all the shots taken, whether it went into the hoop or not. Together with some code, this system can track your overall shots on (in this case) a basketball mini hoop. All this information is conveniently displayed on the LCD screen visible at the top of the system. I also added two extra features, one being a push-button that rests the systems count. This button when pressed prompts the user on the screen by reading "RESET" and sets both shots made and attempted to 0. The other feature, which is quite necessary is the toggle on-off switch. This is essential since the entire system is run on batteries it is important to turn off the system, when not in use, to ensure battery life is sufficient. The on-off switch is a physical switch rather than a digital one, which ensures the sensors, Arduino, and LCD screen are not consuming power when off.

![20200425_211435](https://user-images.githubusercontent.com/72897159/134527165-b797cb12-d465-4d69-8107-9b4e486bbcf0.jpg)

Challenges:

The first challenge was to make sure the hoop accounted for the fact that the basketball could bounce around the rim for an amount of time and then fall in. A time interval had to be set up to give a delay between the first bounce on the rim and the ball going in or missing. The second challenge was to create an effective way to put up the entire system together since there are not any optimal points for sensors or the display. A box was used for the various switches, the display and the sensors, all of which were glued onto the rim. The net on the rim had to be torn up slightly for the distance sensor to have a clear "view" of the ball.

Lessons:

This project was very helpful in learning how to coordinate various sensors together effectively. Putting together a system in this way was very difficult but also rewarding. The complexity of taking into account the different ways the ball can go into the hoop really tested my critical thinking and pushed me to be creative with the code.

Possible Improvements:

The Distance Sensor could have been better protected since a lot of the time the ball was directly hitting the sensor shifting it slightly, maybe a little protective casing would have helped make it more secure.

![20200425_211343](https://user-images.githubusercontent.com/72897159/134527198-1c61d595-dfde-4366-8345-f2d3e89f8676.jpg)


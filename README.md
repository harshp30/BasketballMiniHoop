# MiniHoopTracker

October 2020

Youtube Demonstration: https://www.youtube.com/watch?v=VsOM16-T-PU

Pictures Link: https://drive.google.com/drive/u/2/folders/1ssZ8SuUYN1haxjPsAh7jhmlVfP83LuEI

A system that is attached to the basketball mini hoop, and proceeds to count all shot attempts as well as shots made. In total, this leads to a "Field-Goal Percentage" which will be displayed to the right of the shots made and total shots counter. All the tracking is handled by two individual sensors, the HC-SR04 (Ultrasonic distance sensor) and the MPU-6050 (accelerometer and gyro). These two trackers combined work on sensing whether a shot was taken and if a shot was taken whether it went in the hoop or not. Together with some code, this system can track your overall shots on (in this case) a basketball mini hoop. All this information is conveniently displayed on an LCD screen visible at the top of the system. I also added two extra features, one being a push-button that rests the systems count. This button when pressed prompts the user on the screen by reading "RESET" and sets both shots made and attempted to 0. The other feature, which is quite necessary is the toggle on-off switch. This is essential since the entire system is run on batteries it is important to turn off the system to ensure battery life is sufficient. The on-off switch is a physical switch rather than a digital one, which ensures the sensors, Arduino, and LCD screen are not consuming power when off.

Challenges:

The first challenge was to make sure the hoop accounted for the fact that the basketball could bounce around the rim for an amount of time and then fall in. A time interval had to be set up to give a delay between the first bounce on the rim and the ball going in or missing.
The second challenge was to create an effective way to put up the entire system since there are not any optimal points for sensors or the display. A box was used for the various switches and display and the sensors were all glued onto the rim. The net on the rim had to be torn up slightly for the distance sensor to have a clear "view" of the ball.

Lessons:

This project was very helpful in learning how to coordinate various sensors together effectively. Putting together another system such as this was very difficult but also rewarding. The complexity of taking into different ways the ball can go into the hoop really tested by critical thinking and pushed me to be creative with the code.

Possible Improvements:

The Distance Sensor could have been better projected since a lot of the time the ball is directly hitting the sensor shifting it slightly. maybe a little projective casing would have helped to make it more secure.



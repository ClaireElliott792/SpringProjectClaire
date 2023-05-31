# Spring Project

using https://github.com/ClaireElliott792/Spring-Project NGL demo

## How to play

Use the arrow keys left and right to set your cannon angle.

Use the arrow keys up and down to set your spring compression within the cannon.

Press the key 'P' to fire!

## Project Report

### my aim
- In my  project I aimed to produce a simulation of a ball being fired from a cannon with variables that were controlled by the user.
- the aim was to show how spring compression and cannon angles can effects the ball movement/arch and aimed for these variables to be altered through a user friendly menu on the window.
- I also wanted the ball to be able to bounce on the ground of the screen.

### base code 
- initally I researched into the basic equations I would need to use such  as hooke's law
/// Hooke's Law http://labman.phys.utk.edu/phys221core/modules/m3/Hooke's%20law.html#:~:text=F%20%3D%20%2Dkx.,direction%20towards%20its%20equilibrium%20position. (online) (acceessed May 2023)
- I also used pythagoras' thereom and SOHCAHTOA for basic length and angle calulations.
- I initally struggled with getting my code to start and creating a window, I was getting alot of errors with cmake, ngl, etc so I looked through and tried different ngl demos seeing which would be most suitable for my project and I could use as a jumping off point. I finially found the issues and understood this was not related to the specific demos.

### methodology
- i started by  playing around with the ngl demo to get the screen to open and to create the features i needed within  the window and in the location i desired (cannon,ball,ground)
- unforuntantely i  struggled with drawing these objects, to overcome this issue I looked through other ngl demos and found box2D
- I looked at the documation and the ngl demo and tried to figure out how it was working and what I could do with it
- After doing this i went back to the start creating the same window as before with box2D instralled, which allowed me to easily create and draw the spring, ground and ball
- I then calculated the forces on the ball from the spring equation. Dividing this into x and y components, and applying this to the SetLinearVelocity built in function. This gave the ball the correct speed and angle when the game started.
- One issue i had was the ball seenmed to bounce in a retrograde path, I found the issue was that the ball was being drawn at a diffeerent size to the size I had created. The setting of scale was cuasing these issues. After some playing around and calculations, I managed to  get them the same sizer and the ball was bouncing correct;y./
- I nexted wanted to create a user interface (menu) for the user to be able to change the cannon angle and spring compression while in the simulation.
- Initally I was using the terminal for user input however I wanted soemething better so I played around with qt and the openGL widgets for this, but failed to execute this. After time constraints i gave up and looked at other options. 
-  This led me to key presses as user input as the box2d demo had used.
- I used the left and right keys to alter the angle of  the cannon, i felt this was intuitive. I used the SetTransform method for this.
- I used the up and down keys for the spring compression. This was more complicated and took alot of trial and error of calculations.
- i Finally removed the startTimer method which began the movement of the window, and added it to the press of the 'p' key. I tried to use enter but it didnt work; i researched and saw some complaints and other issues and therefore steered clear.

### summary
- Overall I was happy with what I was able to produce within the time constrates and found the box2D library extreming helpful in the completion of this project. 
- However I wish I had more time to spend on the user interface and spending time make the simulation more visually pleasing, with issues such as the ball and cannon geometry overlapping when the ball is fired at certain angles.


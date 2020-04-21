![Do Or Die System Design](/Portfolio/Images/systemDesignLogo.png)

# 1. System Design :
## a. Architecture of the entire system
Our initial [User Story video](../develop/Portfolio/Images/paper_prototype_video.mp4) demonstrates changes we made based on user interaction. (**test, move from this section later **) 

Architecture of the system uses a central controller database dealing with recieving and sending requests, using MQTT protocol to communicate between devices. Three key devices of system:

Processing - dealing with sending and recieving requests, parsing to make sure request is not malformed, storing user information in a central database, and visualising general consumer data such as total users of the app.

M5 - stateless device to update the database when user step count is incremented, and inform user when player death occurs.

Web - allows user to log in and provide information about their account, user information and challenges.

See relevant sections for further information about specific subsystems. 

## b. Object-Oriented design of key sub-systems (e.g. Desktop Application, Web Application etc.)
### Desktop
Key classes for desktop app include:

* **data** - database API that retrieves and updates user, sponsor, challenge information.
* **events** - recieves and processes MQTT payloads, passes on information into view to rebuild UI with every new request, and into the database API to either publish (pull type requests) information into MQTT topics or update (push type requests) the database.
* **tests** - the test class contains unit tests to ensure edge cases are handles gracefully.
* **view** - this class deals with data visualisation from parsed user.json, challenge.json and sponser.json. Contains helped functions for building the UI, for building expanded lists and building charts using local json files. 

### Web
For more detail on web technologies see section **1g.** bellow.
React is ideal to implement a object oriented design. Our website conists of functional components (classes- one for each site/view) and a MQTT class which is integrated into the different views.
* **Mqtt Class:** This class handles all comunication with our "server" and the associated rendering. You will find a call for the Mqtt class in all the following components. The class:
  * encapsulates - it hides the detail of the server communication from the other components
  * is abstract - with a simple interface that can be called by all components
  * inherits its basic methods from the react components
  * is polymorph - it can handle all sorts of data: from profile to challenge data  
* **Landing Page:** Contains all the static content and the Mqtt component for creating a new profile
* **Login Page:** Contains the static UI + a Mqtt instance to handle the Login
* **Profile Page:** Contains a Mqtt instance which renders the full profile incl. a dynamic profile picture and  the challenges the user has signed up for
* **Challenge Choice Page:** Contains a Mqtt instance which lets the user sign up for challenges
* **Common static components such as headers, navbars or footers** which can be integrated in all of the views


### M5
Team

## c. Requirements of key sub-systems (in the form of selected user stories)
In our prototype we implemented the following user stories for our three key users **User, Sponsor and Admin**. These user stories defined our test cases and requirements and were the basis for our development effort:
* 1. **User** A user walks around with the M5 stack in his hand and he can see his steps and time updated both on the stack and on the web version. On the stack the user will see an animated "tamagotchi" and on the web he will see his profile picture. On the web a user can create an account or login to his existing account, sign up for challenges and view his profile, including the challenges he signed up for and the total steps/remaining time. 

* 3. **Sponsor Activity** can create an account or login to his existing account and create new challenges

* 4. **Admin** can visit a dashboard with key statistics around our game userbase. Used to track increase and decrease of user activity, how many total steps by all players together have been taken, and an easy way to visualise number of users and challenge for the game. The main requirement is monitoring and visualising data in a user friendly way.

**These three user stories translate into the following requirements for our sub-systems:**
### Desktop
Administration interface for data visualisation. Allow back-end to deal with sending and recieving requests, and front-end to track total users, sponsers and challenges currently available.

**Data visualisation UI**
* Front-end needs to pull flat totals from database for current users, sponsers, and available current challenges.
* The interface must be able to split this quantative data based on a time frame, showing changes over daily, weekly and monthly periods.
* We want to be able to look at statistics for any specific user, such as how much time they have left and global steps taken.
* We want to follow thematic colour scheme for the UI.

**Data processing back-end**
* System must be capable of processing JSON requests from the web application and inserting new users, sponsers and challenges into central database, and retaining this data in a persistant manner. 
* System must be able to listen on the correct channel for step updates for each user, and update records accordingly.
* System also calculates the life time remaining for each user's avatar based on step updates and time elapsed
* System also informs user of death.

### Web
* 1. **User Profile**
  * a. Login: The website must be able to retain the username upon creation/login and in case of a sign-up send the new profile information to the server 
  * b. Profile: The website must send a request to the server for the user profile and and all his challenge and render that information
  * c. Render a profile picture depending on the user name (the profile picture will be available on the webserver)
  * d. Enroll in Challenges: The website must request all challenges from the server, render all of them (dynamically) and inform the server if a user has selected a challenge
* 2. **User activity**
  * a. The information requested and rendered under point i.a) must be updated regurarely (i.e. send a new request to the server every second and render the updated data on the screen)
* 3. **Sponsor activity**
  * a. The website must have an input form for new challenges that the sponser can fill in. The input of the sponser gets validated (e.g. did he complete all fields). Upon submission the new challenge will be sent to the server
### M5
## d. The evolution of UI wireframes for key sub-systems
* *Can we integrate the paper prototypes here?* *

### Desktop
Original multi-tab wireframe design for desktop UI:
![Wireframe-desktop](/Portfolio/Images/desktop-wireframe.jpg)

Updated wireframe design for UI:

### Web

### M5
## e. Details of the communication protocols in use (including a rational for your choice)
* *Team M5 please write this section* *

## f. Details of the data persistence mechanisms in use (including a rational for your choice)
* *Team Processing please write this section* *
Each user, challenge and sponsor is stored as a JSON object to allow for easy parsing and sending of payloads. In order to allow persistence we used users.json, sponsors.json and challenges.json files to store respective data. This format allows the central server to send an entire user profile when recieving a request from the M5 or web device to pull a profile. Each user object contains a challenges_id array which contains all the ids of currently enrolled challenges. Challenge_id array parameter is used to refer to enrolled challenges from challenges.json in order to keep payload lengths below the MQTT maximum. Similarly, each sponsor object also contains a challenge_id array (foreign key that refers to challenges data). This structure would ideally be implemented in a SQL relational database to increase speed and maintanability. 

M5 device is stateless therefore does not store information locally apart from created variables. These are then pulled from the database via a pull_user request type. 


## g. Details of web technologies in use (including a rational for your choice)
Our website is react based and build on top of a simple react/bootsrap template.
The choice for these technologies was driven by some key needs of our website/team that ultimately led us to choose this set up:
* 1. **Ability for integration of MQTT commuication protocol:** When looking into the different framework we realized that the script Tom provided us for the MQTT communication could be easily reused and integrated into all major Javascript based frameworks (e.g. Angualar, React, Vue).
* 2. **Ability to dynamicially refresh content on a regular basis in an easy way:** Ract turned out to be the obvious candidate to satisfy this need: It's logic is centered around an app state, with components getting rerendered every time the state changes. That way we could display a dynamic step / lifetime counter which would change in real time without refreshing the page.
* 3. **Availability of UI templates for rapid but beautiful prototyping:** React is currently [the most widely used](https://hotframeworks.com/) web framework, so there were plenty of templates available. We chose a [free template by Creative Tim](https://demos.creative-tim.com/now-ui-kit/index.html), which included some basic UI components such as a navigation and a profile page and would allow us to build rapid prototypes without bottering about the details of styling and navigation.
* 4. **Support for Object Oriented Design:** To support our object oriented design we were looking for a framwork that supports the use of a strong object oriented design. React components are ideal to build class based software (see chapter 1.b).

The key component of our design is the Mqtt class... * *Oli please write more on the details* *


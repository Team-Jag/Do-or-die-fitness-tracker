![Do Or Die System Design](/Portfolio/Images/systemDesignLogo.png)

# 1. System Design :
## a. Architecture of the entire system

Architecture of the system uses a central controller database dealing with recieving and sending requests, using MQTT protocol to communicate between devices. Three key devices of system:

Processing - dealing with sending and recieving requests, parsing to make sure request is not malformed, storing user information in a central database, and visualising general consumer data such as total users of the app.

M5 - stateless device to update the database when user step count is incremented, and inform user when player death occurs.

Web - allows user to log in and provide information about their account, user information and challenges.

To maintain seperation of concerns, all data is accessed through an API public class, and requests pass through a single server (so web and M5 stack components do not ever interact directly). Communication between devices was devised to be as simple as possible to avoid unecessary complexit, with the concept of a common contract of User, Challenge and Sponser classes being consistent across all devices. Unit testing each subsystem allowed for confidence of individual compenents working correctly and expectedly during integration.

![Architecture](/Portfolio/Images/architecture.png)

See relevant sections for further information about specific subsystems. 

## b. Object-Oriented design of key sub-systems (e.g. Desktop Application, Web Application etc.)
Our [initial UML diagram](/Portfolio/Images/first_uml.png) from one of our initial meetings was limited, however it developed in to the following UML diagrams for each of the three sub-systems. 

### DESKTOP
Key classes for desktop app include:

* **data** - database API that retrieves and updates user, sponsor, challenge information.
* **events** - recieves and processes MQTT payloads, passes on information into view to rebuild UI with every new request, and into the database API to either publish (pull type requests) information into MQTT topics or update (push type requests) the database.
* **tests** - the test class contains unit tests to ensure edge cases are handles gracefully.
* **view** - this class deals with data visualisation from parsed user.json, challenge.json and sponser.json. Contains helped functions for building the UI, for building expanded lists and building charts using local json files. 

### WEB
For more detail on web technologies see section **1g.** bellow.
React is ideal to implement object oriented design. Our website consists of functional components (classes - one for each site/view) and an MQTT class which is integrated into the different views.
* **Mqtt Class:** This class handles all comunication with our "server" and the associated rendering. You will find a call for the Mqtt class in all the following components. The class:
  * encapsulates - it hides the detail of the server communication from the other components
  * is abstract - with a simple interface that can be called by all components
  * inherits its basic methods from the react components
  * is polymorphic - it can handle all sorts of data: from profile to challenge data  
* **Landing Page:** Contains all the static content and the Mqtt instance for creating a new profile
* **Login Page:** Contains the static UI + a Mqtt instance to handle the Login
* **Profile Page:** Contains a Mqtt instance which renders the full profile incl. a dynamic profile picture and  the challenges the user has signed up for
* **Challenge Choice Page:** Contains a Mqtt instance which lets the user sign up for challenges
* **Common static components such as headers, navbars or footers** which can be integrated in all of the views

### M5

## c. Requirements of key sub-systems (in the form of selected user stories)
We ensured that our product had a user-focused framework by developing three key user stories: **End-User, Admin, and Sponsor**. These three user stories defined our test cases and requirements and were the basis for our development effort.

<p align="center"><b> END-USER:</b> Our first user story is the end-user, who walks around with the M5 stack on his arm, which counts his steps, and displays the health bar of the Bean. The health bar is reflective of how much time the user has left, in order to view the specific time remaining they have to use the web. The user can also use the web to enroll in challenges set by sponsors, and view their total steps. As a reward for successfully completing challenges, they end-user will receive extra time added to their account. </p> 

<p align="center"><b> ADMIN:</b> Our second user story is the admin, who can utilise the management dashboard to to track the userbase. They are able to track statistics of the user, sponsors, and challenges in order to ensure the success of the product and see how others are interacting with the product. If an individual user has an issue, they are able to use the management dashboard to view their profile. Using the management dashboard, they are able to monitor and visualize the data in a user friendly way. </p>

<p align="center"><b> SPONSOR:</b>Finally, our third user story is the sponsor. The sponsor uses the website to create a profile, and then set challenges for the average user to enrol them. They are able to use these challenges as a way to promote their business and brand.</p> 

These key stories were developped in to further user stories, which can be seen in our [Gantt chart](https://uob-my.sharepoint.com/:x:/g/personal/ac16888_bristol_ac_uk/EXltfbLEnNFLrGLOGOxgZcIB2oqj_ft_TP9LevpsozfhVg?e=TUTMn7). However, the main ones can be seen in this use case diagram:

![Use case](/Portfolio/Images/dotuml.png)

<p align="center"><b>After developing the three user stories, we translated them into the following requirements for our sub-systems:</b></p>

### DESKTOP
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

### WEB
**User**
  * Login: The website must be able to retain the username upon creation/login and in case of a sign-up send the new profile information to the server 
  * Profile: The website must send a request to the server for the user profile and and all his challenge and render that information
  * Render a profile picture depending on the user name (the profile picture will be available on the webserver)
  * Enroll in Challenges: The website must request all challenges from the server, render all of them (dynamically) and inform the server if a user has selected a challenge
  * The information requested and rendered under point i.a) must be updated regurarely (i.e. send a new request to the server every second and render the updated data on the screen)
  
**Sponsor**
  * The website must have an input form for new challenges that the sponser can fill in. The input of the sponser gets validated (e.g. did he complete all fields). Upon submission the new challenge will be sent to the server
  
### M5 
When designing the interface of the M5 Stack, we were mainly focused on the End-User story. Thus, the requirements for the End-User were our main focus. In order to ensure that we satisfied these, we split our requirements in to two further subheadings.

**Back-End**
* The M5 must have a pedometer, able to accurately count the end-user's steps, and store them locally. 
* The M5 must be able to communicate with the server using the shared communication contract.

**Front-End**
* To ensure customer retention, we have to implement an enganging and appealing interface. 
* The M5 should display a live step count. 
* The M5 should display an adorable sprite (called Bean) to create an attachment with the end-user, and ensure long-term engagement. 
* The M5 must have a health bar which accurately reflects how much time Bean has left. 
* Bean's animations and general liveliness should reflect its remaining life (i.e. it should bounce less when it is closer to death).
* The M5 should display the challenges that the user is enrolled in. 
* The M5 should display the user's statistics. 


## d. The evolution of UI wireframes for key sub-systems
Our [User Story video](../Portfolio/Images/paper_prototype_video.mp4), developed during the prototype phase, demonstrates our initial design for our product. How this changed for each subsystem will be considered in this section. 

### DESKTOP
Original multi-tab wireframe design for desktop UI:
![Wireframe-desktop](/Portfolio/Images/desktop-wireframe.jpg)

Updated wireframe design for UI in a single window:
![Wireframe-final](/Portfolio/Images/final_wirefram.jpg)
### WEB

### M5
![Do Or Die System Design](/Portfolio/Images/M5Images/loadingScreenCollage.jpg)

The starting screen was replaced with a more professional logo, following user feedback.

![Do Or Die System Design](/Portfolio/Images/M5Images/animation.gif)

From the initial UI wireframe, we designed and animated a simple but responsive sprite. The screen was decluttered to allow the focus on the sprite, based upon feedback we received during the user testing session. 

![Do Or Die System Design](/Portfolio/Images/M5Images/statsCollage.jpg)

The stats screen was implemented according to the UI wireframe, however we have not implemented the sleep detection feature due to its dificulty to develop. Therefore, different statistics have been displayed. 

![Do Or Die System Design](/Portfolio/Images/M5Images/campaignShopCollage.jpg)

Initially our UI wireframe included a shop feature, however after adding a third user type (the Sponsor) we shifted our focus to implementing the challenges feature instead. The shop feature remains a valid possible future feature as dicussed in [Project Evaluation](/Portfolio/ProjectEvaluation.md). 

## e. Details of the communication protocols in use (including a rational for your choice)
Due to variability of payload attributes and sizes (especially concerning challenges), we made the decision to make a unifying request "type" parameter to work around the MQTT broker maximum character limit. A list of all valid request types made between devices is found in MQTT_request_types.txt.

### DESKTOP
Example request from database:
``` 
{
    "type": "push profile",
    "user_name": "Mario",
    "total_steps": 2200,
    "remaining_sec": 2000,
}
```

### WEB

### M5
* *Team M5 please write this section* *

## f. Details of the data persistence mechanisms in use (including a rational for your choice)

Each user, challenge and sponsor is stored as a JSON object to allow for easy parsing and sending of payloads. In order to allow persistence we used users.json, sponsors.json and challenges.json files to store respective data. This format allows the central server to send an entire user profile when recieving a request from the M5 or web device to pull a profile using the data API. Each user object contains a challenges_id array which contains all the ids of currently enrolled challenges. Challenge_id array parameter is used to refer to enrolled challenges from challenges.json in order to keep payload lengths below the MQTT maximum. Similarly, each sponsor object also contains a challenge_id array (foreign key that refers to challenges data). This structure would ideally be implemented in a SQL relational database to increase speed and maintanability. 

M5 device is stateless therefore does not store information locally apart from created variables. These are then pulled from the database via a pull_user request type. 


## g. Details of web technologies in use (including a rational for your choice)
Our website is react based and built on top of a simple react/bootstrap template.
The choice for these technologies was driven by some key needs of our website/team that ultimately led us to choose this set up:
* 1. **Ability for integration of MQTT commuication protocol:** When looking into the different framework we realized that the script Tom provided us for the MQTT communication could be easily reused and integrated into all major Javascript based frameworks (e.g. Angular, React, Vue).
* 2. **Ability to dynamicially refresh content on a regular basis in an easy way:** React turned out to be the obvious candidate to satisfy this need: Its logic is centered around an app state, with components getting rerendered every time the state changes. That way we could display a dynamic step / lifetime counter which would change in real time without refreshing the page.
* 3. **Availability of UI templates for rapid but beautiful prototyping:** React is currently [the most widely used](https://hotframeworks.com/) web framework, so there were plenty of templates available. We chose a [free template by Creative Tim](https://demos.creative-tim.com/now-ui-kit/index.html), which included some basic UI components such as a navigation and a profile page and would allow us to build rapid prototypes without bothering about the details of styling and navigation.
* 4. **Support for Object Oriented Design:** To support our object oriented design we were looking for a framework that supports the use of a strong object oriented design. React components are ideal to build class based software (see chapter 1.b).
* 5. **The MQTTclient Class:** Every page needs to be able to send or receive json messages, usually both, to and from the MQTT broker, so we have implemented an MQTT class which handles all data to prevent repetition in the design of each page. As the incoming json messages over the broker for the web profile are the most flexible in nature out of all pages, the MQTT class has conditional rendering dependent on the internal state of the class. The MQTT class running on a given system listens to incoming messages based on the username so if another user is accessing the site from elsewhere, there is no mismatch of data between the sessions and each user won't interrupt the others navigating the website. This was designed in order to be scalable, and to ensure the client continues to listen to the broker until the correct packet of information has been received, which is parsed and interpreted.


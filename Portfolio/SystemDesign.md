![Do Or Die System Design](Images/systemDesignLogo.png)

# System Design [40pts]

In the following section we will reflect on the design of our product. By the end of our System Design section, you will understand how we moved from our initial paper prototype to our [existing product](https://github.com/Team-Jag/Do-or-die-fitness-tracker#product-description). Before explaining the architecture of our system in detail, including the object oriented design of each of our key subsystems, we will first explain how we came to design our product based on the gap in the market that we were trying to fill. This includes our three key user groups, and their individual user stories. We will also explain and evaluate the design interface of our subsytems, and introduce potential areas for improvement. 

## Table of Contents
- [**Product Requirements**](#product-requirements) 
  - [Ideation and Concept Development](#ideation-and-concept-development)
  - [User Types](#user-types)
- [**User Requirements for Key Subsystems**](#user-requirements-for-key-subsystems)
  - [Desktop system requirements](#desktop-system-requirements)
  - [Web system requirements](#web-system-requirements)
  - [M5Stack system requirements](#m5stack-system-requirements)
- [**Architecture of The Entire System**](#architecture-of-the-entire-system)
- [**Object-Oriented Design of Key Subsystems**](#object-oriented-design-of-key-subsystems)
  - [Desktop design](#desktop-design)
  - [Web design](#web-design)
  - [M5Stack design](#m5stack-design)
    - [Back-end](#back-end)
    - [Front-end](#front-end)
- [**The Evolution of UI Wireframes for Key Sub-Systems**](#the-evolution-of-ui-wireframes-for-key-sub-systems)
  - [Desktop UI wireframe](#desktop-ui-wireframe)
  - [Web UI wireframe](#web-ui-wireframe)
  - [M5Stack UI wireframe](#m5stack-ui-wireframe)
- [**Details of the Communication Protocols in Use**](#details-of-the-communication-protocols-in-use)
  - [Desktop and M5Stack](#desktop-and-m5stack)
  - [Desktop and web](#desktop-and-web)
- [**Details of the Data Persistence Mechanisms in Use**](#details-of-the-data-persistence-mechanisms-in-use)
- [**Details of Web Technologies in Use**](#details-of-web-technologies-in-use)

## Product Requirements
Our [Do or Die fitness tracker](https://github.com/Team-Jag/Do-or-die-fitness-tracker#product-description) is an Internet of Things (IoT) product that we designed to operate across three different platforms; the M5Stack, the Web, and a Management Dashboard. 
### Ideation and Concept Development

<img src="Images/designSpace.JPG" width=40%>

While initially explored a number of fun and potentially successful products, we came to the conclusion that each team member was keen to develop a product that focused on the improvement of user health. We kept health at the centre of our minds while exploring our design space, and deciding what had the most chance of success. We ultimately came to the conclusion that we wanted to create a gamified fitness tracker to improve user health. When deciding what type of product to create, we took particular interest in the success of different games such as Pokemon Go, and the recent revival of the Tamagotchi. We felt that if we could combine our goal of having a fitness tracker, with the concept of a keeping a virtual pet on an Internet of Things (IoT) product, we would be addressing a gap in the market - likely very successfully. In recent years there has been a large push towards getting individuals active, which is something that we kept in mind during the ideation process. After several ideation cycles focused on the concept of health, we settled on the idea of measuring user step-count as a proxy for user fitness. 

A key requirement for the success of this project is motivation for the end-user that goes beyond just meeting a daily step goal, as this would eventially become repetitive and boring. We recognized that this had the potential to lead to a fitness plateau as the user would walk enough to keep the Bean alive and no more, thus placing a ceiling on their potential benefit from our product.To solve this we introduced the idea of challenges, to make exercise closer to a game with concrete objectives and rewards, and introduce an element of competition which will further encourage end-users to use the product longer. We considered letting users themselves upload challenges and compete against each other, however with a large playerbase we thought this would create an overwhelming amount of challenges (a scaling issue), and also remove incentive to create challenges with a suitably difficult effort/reward ratio. At the end of the ideation and creation process, we felt that the concept of our [Do or Die fitness tracker](https://github.com/Team-Jag/Do-or-die-fitness-tracker#product-description) was not too ambiguous, nor too specific, and allowed for the perfect amount of growth and development when following an Agile development process. 

### User Types

After decided what we wanted Do or Die to look like as a product, we began exploring who who would use our system, and how they would use it. Ultimately, we came to the conclusion that we would have three main user groups: the Admin, Sponsor, and End-User. These three user groups ensured that our product had a user-centred focus, and defined our test cases and requirements that were the basis of the development of our system. Each of these user types will be explained in detail, as well as example user stories that we kept at the centre of our design process. 

Our first user group, and the centre of our product, is the end-user. This is the person that is using our product to get fit, invest time and energy into gaining health for the Bean thereby increasing their own health. This person will likely either be someone who is interested in getting active, but lacks the motivation. Or someone who is already active, and would like an extra challenge or an additional motivator to push themselves even further. Regardless of why they were using our fitness tracker, we knew that each user had to be able to do a number of things to see a benefit. This includes the ability to track their steps, know the current health of their Bean, enroll in challenges, and track their overall progress. The key theme of our end-user user type is that they are experiencing some type of challenge. Whether they are setting their own daily goals, or enrolling in challenges, they should be able to track their progress and see the adition of 'life' to the health bar of their Bean. This was the core concept underpinning our product, and what would ensure our success. 

Our second user type was a sponsor. This person was likely a local gym owner, or business owner, who was looking for exposure for their business. We imagined it more likely to be a fitness business, as that would work well with our product and the type of customer base that we were likely to attract. Sponsors should be able to create challenges for our users to enroll in, which would likely advertise their business in some way (i.e. 'The Bristol Gym Challenge'). This would generate a significant amount of exposure for local business. In return for completing a challenge, a sponsor would reward extra 'life' to the user's Bean. A sponsor must be able to create a profile on the web in order to create challenges, and they should be able to track the users enrolled in the challenges. 

Finally, in order to ensure the success of the product, we knew that we needed to have an admin user type. This person would be responsible for tracking the playerbase, the success of the product, or if we are loosing users. The admin would be the person responsible for deciding whether the product needs to be modified, or adapted based on these statistics. Moreover, the admin would be in charge of fixing any issues that may arise from the users and the sponsors. This may include the pedometer not working correctly, a user's inability to sign up to challenges due to an issue on the backend, or a need to change/delete a user's details. In order to ensure the success of the product, the admin must be able to view a number of statistics relating to the userbase. This includes total numbers of currently 'dead' users, weekly statistics, and monthly statistics. The admin must also be able to pull up an individual user's profile to be able to adequately address any issues. 

<table>
<tr>
  <th><b>End-User</b></th>
  <th><b>Admin</b></th>
  <th><b>Sponsor</b></th>
</tr>
<tr>
  <td>The user walks around with the M5Stack on his arm, which counts his steps, and displays the health bar of the Bean. The health bar is reflective of how much time the user has left</td>
  <td>The admin can utilise the management dashboard to track statistics of users, sponsors, and challenges in order to ensure the success of the product and see how others are interacting with the product</td>
  <td>The sponsor uses the website to create a profile, and set challenges for the average user to enrol them.</td>
</tr>
<tr>
  <td>The user can use the web to enrol in challenges set by sponsors, and view their total steps and health</td>
  <td>The admin can use the management dashboard to view issues set by users on the website</td>
  <td>The sponsor is able to use these challenges as a way to promote their business and brand.</td>
</tr>
<tr>
  <td>The user can increase the Bean's health by either completing challenges or walking</td>
  <td>The admin can use the web to track web traffic over time</td>
  <td>N/A</td>
</tr>
</table>

A further break down of the user stories can be seen in our [Gantt chart](Images/updated_gantt.png). However, the main ones are outlined in this use case diagram:

![Use case](Images/dotuml.png)

Now that it is clear who are target users are, and how we saw them using our system, it is necessary to define the key subsystems that make up our product. Each of these subsystems became necessary to ensuring the success of Do or Die as a product: 

* **Internet of Things Device** : 
In order to ensure we track our user's fitness level, we used an M5Stack as our IoT device. This was an Arduino compatible device we used to create a pedometer. This will be worn on the user's wrist, and can accurately send steps to the Desktop application. On our IoT device the user can view a live step count, challenges they are enrolled in, and indivdiual statistics. The device was made to be stateless, and relies on the Desktop application to pull the user's data. This device worked well for our desired goals because it contains a gyroscope which can be used as a pedometer, and Wi-Fi capabilities to pull information from the central database.

* **Desktop Application** : 
To fulfil the admin user story requirements to analyse playerbase and have access to the backend, we created a Processing application which functions as a back-end. We implemented a Managment Dashboard to be used by the Admin. On our desktop application you are able to view things such as total users, an individual user's statistics, and how many users have 'died'. The back end of this subsystem sends and receives requests from MQTT client topics, parsing to make sure request is not malformed, storing user, sponsor and challenge information in a central database, and visualising general consumer data such as total users of the app. 

* **Web Application** : 
To fulfil the end-user story requirement of creating an account, and the sponsor user story of setting challenges, we implemented a web application. The application will be used by the end-users of our product, as well as the sponsors. Here they can view things like their ranking, their total steps, and can enrol in challenges. Sponsors can also use the website to create challenges.

## User requirements for key subsystems
To break each of the three key subsystems down further, and before any substantive work began, we outlined the key requirements for each system in order to understand what was eventually necessary to develop a Minimum Viable Product (MVP). This also ensured each of the team members were aware of the key functionalities of each subsystem. These will be explored in turn, before we analyse the final architecture of our system, and finally each of the key components of our architecture.

### DESKTOP SYSTEM REQUIREMENTS

Administration interface for data visualisation. Allows back-end to deal with sending and receiving requests, and front-end to track total users, sponsors and challenges currently available.

**Data visualisation UI**

* Front-end needs to pull flat totals from database for current users, sponsors, and available challenges in order to draw accurate statistics for the admin so they can track this data for further use.
* The interface must be able to split this quantative data based on a time frame, showing changes over daily, weekly and monthly periods to allow admin to see relevant changes in playerbase in an intuitive way. 
* The front-end interface must be able to look at statistics for any specific user, such as how much time they have left and global steps taken, in order for admin to track down account specific issues such as innacurate step counts, and be able to recommend a fix.
* The interface must follow colour scheme for the UI, to maintain thematic consistency across and make the product come across as more professional.

**Data processing back-end**

* System must be capable of processing JSON requests from both the web application and the M5Stack, and should be able to insert new users, sponsors and challenges into central database, while retaining this data in a persistent manner, in order to provide accurate stats for front end.
* System must be able to listen on the correct MQTT client topic for step updates for each user, and update records accordingly.
* System also calculates the life time remaining for each user's avatar based on step updates and time elapsed.
* System should automatically add rewards if user has met required goals in any challenges enrolled.

### WEB SYSTEM REQUIREMENTS

Primary interface for the sponsor and the user to handle everything related to challenges and their profile.

**User**

* Login: The website must be able to retain the username upon creation/login and in case of a sign-up send the new profile information to the server
* Profile: The website must send a request to the server for the user profile and and all his challenge and render that information
* Render a profile picture depending on the user name (the profile picture will be available on the webserver)
* Enroll in Challenges: The website must request all challenges from the server, render all of them (dynamically) and inform the server if a user has selected a challenge
* The information requested and rendered under point i.a) must be updated regurarely (i.e. send a new request to the server every second and render the updated data on the screen)
  
**Sponsor**

* The website must have an input form for new challenges that the sponser can fill in. The input of the sponser gets validated (e.g. did he complete all fields). Upon submission the new challenge will be sent to the server
  
### M5STACK SYSTEM REQUIREMENTS

When designing the interface of the M5Stack, we were mainly focused on the End-User story. Thus, the requirements for the End-User were our main focus. In order to ensure that we satisfied these, we split our requirements into two further subheadings.

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

## Architecture of the entire system
Due to several devices needed by the user requirements, our system architecture uses a central controller API which communicates with the database, and handles receiving and sending requests using MQTT protocol to communicate between different devices. In order to deliver our user stories we needed our architecture to send and store data: 

* **Data Communication** :
Due to several devices as per our user requirements, we needed to devise a way for devices to communicate via a shared contract. Data such as step data moves between the M5Stack to the Desktop, and then the Desktop to the Web. We implemented this by using a MQTT broker, which is explained in further detail in section E.

* **Data Repository** : 
To keep our data persistent, we store the data in JSON files stored locally to where the Processing app is running, similar to a server. Refer to further details and justification in the Data Persistance section.  
 
To maintain separation of concerns, all data is accessed through an API public class which allows access to a private Database class for storage of persistant data, and requests pass through a multiple channels on the MQTT broker (this ensures web and M5Stack components do not ever interact directly).

Communication between devices was devised to be as simple as possible to avoid unecessary complexity, with the concept of a common contract of User, Challenge and Sponsor classes being consistent across all devices to make the project as maintainable as possible. Unit testing each subsystem allowed for confidence of individual components working correctly and as expected during integration.

![Architecture](Images/architecture-UML.png)
The above diagram demonstrates dependancies and communication between all devices of our project. Every request passes through the database API on the Processing app, and when needed recieves a request to pull information from the database. No device has access to storage apart from the API. This is a security concern as it allows only valid requests to alter files in persistant storage, and it is a modularity concern as there is a strict contract devices must adhere by to add or request data. 

## Object-oriented design of key subsystems

Our [initial UML diagram](Images/first_uml.png) from one of our initial meetings was limited. During each sprint, the object oriented design of our product were changed depending on the tests that we had passed. In this section, we will explain the object oriented design of each of our key subsystems, while considering where there could be room for improvement during future sprints.

### DESKTOP DESIGN

Key classes for desktop app include:

* **database** - this is a private class which deals with writing and reading persistant data stored on disk. Encapsulation of this class makes the back-end modular and allows altering of the data classes and other elements of the program without needing to change database. The database class follows the liskov substitution princple, as it does not care what type of data request comes in (between sponsor, user and challenge types).
* **data classes** - database API that retrieves and updates user, sponsor, challenge information (with each data type having their separate APIs respectively to ensure encapsulation of database class). Having seperate classes for each type of data allowed for modularity when modifying request types was necessary during the project.
* **events** - receives and processes MQTT payloads, passes on information into view to rebuild UI with every new request, and into the database API to either publish (pull type requests) information into MQTT client topics or update (push type requests) the database. This class also contains event listeners for buttons and lists in the UI, and any time an event occurs (such as data being added) the view class is refreshed. This was done to enable changing statistics to be visualised in real time as opposed to after a restart.
* **tests** - the test class contains unit tests to ensure edge cases are handled gracefully. This is necessary for future integration, to have confidence that all requests work correctly.
* **view** - this class deals with data visualisation from parsed user.json, challenge.json and sponsor.json. Contains helped functions for building the UI, for building expanded lists and building charts using local JSON files obtained by requesting data from the respective APIs. The class is by necessity accessed by Events which contains listeners for incoming requests (this updates view in real time when new data is added) and for buttons in the UI (for interactivity and selecting what information the admin wants).

![Processing-uml](Images/Processing-UML.png)
The above diagram shows dependancies and relationships between classes in the Processing app. 

### WEB DESIGN

For more detail on web technologies see section **1g.** below.
React is ideal to implement object oriented design. Our website consists of functional components (classes - one for each site/view) and an MQTT class which is integrated into the different views.

* **MQTT Class:** This class handles all communication with our "server" and the associated rendering. You will find a call for the MQTT class in all the following components. The class:

  * encapsulates - it hides the detail of the server communication from the other components
  * acts abstract - with a simple interface that can be called by all components
  * inherits its basic methods from the react components
  * is polymorphic - it can handle all sorts of data: from profile to challenge data  
* **Landing Page:** Contains all the static content and the MQTT instance for creating a new profile
* **Login Page:** Contains the static UI + a MQTT instance to handle the Login
* **Profile Page:** Contains a MQTT instance which renders the full profile incl. a dynamic profile picture and  the challenges the user has signed up for
* **Challenge Choice Page:** Contains a MQTT instance which lets the user sign up for challenges
* **Common static components such as headers, navbars or footers** which can be integrated in all of the views

![web-uml](Images/web-uml.png)

### M5STACK DESIGN

#### Back-End

Since our M5Stack is effectively a stateless machine with well-developed animations, our back-end Classes are straight-forward.
We need to read in the data from the Gyroscope and use it to detect when the user takes a step. By counting steps we get an idea of how active a user is at any given time.
We need to send and receive the JSON messages that we agreed on in our shared contract. This allows the M5Stack to be a memoryless machine by pulling and pushing all the necessary data from and to the Desktop server.

* **Pedometer.h**
  * Count the steps taken by the user using the Gyroscope inside the M5Stack. (This code is taken from MPU9250 Basic Example Code by Kris, Modified by Brent Wilkins July 19, 2016).

* **Main.h**
  * This is the main class whose loop() is running at all times in the M5Stack. It publishes and reads messages on the appropriate MQTT Topics, it does so by serializing and deserializing JSON messages using the ArduinoJson.h library.
  Once a JSON message is deserialized it is placed in the correct Class, so for example Challenges data will be stored in the ChallengesView object, whereas Statistics data will be stored in the StatsView object.
  Once all data is correctly handled, Main.h selects which of the Front-End View objects to draw(), according to the screen requested by the user, through the use of the M5Stack buttons.

#### Front-End

Initally our idea for the M5Stack Front-End Classes was to have a central abstract class View which would execute all of the printing and drawing to screen. We quickly discovered that things like abstract classes, inheritance and polimorphism were too hard to implement effectively in Arduino so the 'View' abstract class does not actually exist in our code. However it is still useful to conceptualize our View classes as belonging to a figurative abstract class since they have the same methods and attributes.

![M5_HomeScreenView](Images/M5_ViewExplained.png)

* **View.h (ChallengesView.h, StatsView.h)**
  * Draw the Home screen, Challenges screen or Statistics screen using a composition of their child module Classes (TextBox.h,  Timer.h, Bar.h, Bean.h). These are effectively aggreate classes which combine the move() and draw() functions of our component classes below

* **TextBox.h**
  * Draw a simple box with given text at the bottom of the screen, used to explain what each M5Stack button does in each View

* **Timer.h**
  * Small class implementing a simple timer, we use this in each View class to control the refresh rate of our front-end frames. We also use it in Main.h to set how often we update the user information by sending a user_profile type request to the Desktop Server.

* **Bar.h**
  * Draw a simple horizontal progress bar, used to visualize the "Health" left in the Home view, the progress of a challenge in the Challenges view, and how close a user is to their personal record in the Statistics View. We ended up using a lot of progress bar in our View objects because the M5Stack graphics library provides a simple way to create such progress bars and this kind of bars communicates really well to the user how well or poorly they are performing

* **Bean.h**
  * Used in Home view to draw our main animation: a cute-looking sprite which jumps around the screen and changes it's facial expressions. The movement speed, jumping height and jumping frequency are all dynamically calculated based on the "Health" of the sprite. We spent a lot of time optimizing this class' animations because they are what's meant to keep the user attached to their bean and therefore motivated to live a healthy lifestile.

![m5-uml](Images/M5_Design.png)
On the left we show what our plan was for our M5Stack design, on the right we show what the end product actually ended up looking like. Clearly Arduino is not the best for Object Oriented Design...

## The evolution of UI wireframes for key sub-systems

Our [User Story video](Images/paper_prototype_video.mp4), developed during the prototype phase, demonstrates our initial design for our product. How this changed for each subsystem will be considered in this section.

### DESKTOP UI WIREFRAME

**Original** multi-tab wireframe design for desktop UI *(left)*, and **updated** single-tab wireframe design *(right)*:<br>

<img src="../Portfolio/Images/desktop-wireframe.jpg" width=50%><img src="../Portfolio/Images/final_wirefram.jpg" width=50%><br>

We decided on the single-tab design to simplify the dashboard UI and not have to create new graphs in different tabs, as originally shown by the first design. We picked line graphs to visualise total count of users, sponsors, and challenges respectively to best show traffic over time. A pie chart was used to easily see the proportion of current users that are alive, and bar graphs were used to quickly compare the amounts of users, sponsers, and challenges currently active.
![UI-layout](Images/dashboard-main.png)

Pulling up a user profile by either using the search bar or dropdown list, an error message to show if a user does not exist:
![UI-search](Images/search-user.png) ![UI-search](Images/null-user.png)

Selecting a specific statistic from UI to allow data to be viewed on different time frames:
![UI-select-chart](Images/select-chart.png)

Different selected charts showing data over time for each parameter, such as users, sponsors, challenges in an intuitive way.
![UI-selected-charts](Images/selected-charts.png)

### WEB UI WIREFRAME

Original web wireframe design for desktop profile:
![Wireframe-web](Images/web-wireframe.jpg)

Simplified but dynamic profile page, user can choose from several profile pictures, steps, time and ranking get updated once per second.
![Web-screenshot](Images/web-screenshot.PNG)

Sign-up screen draft
![Web-signupdraft](Images/signup-draft.png)

Final sign-up screen, with the sponsor checkbox. Sponsors will be forwarded to the create challanges page, users to their profile page.
![Web-signupfinal](Images/signup-final.PNG)

### M5STACK UI WIREFRAME

![Do Or Die System Design](Images/M5Images/loadingScreenCollage.jpg)

The starting screen was replaced with a more professional logo, following user feedback.

![Do Or Die System Design](Images/M5Images/animation.gif)

From the initial UI wireframe, we designed and animated a simple but responsive sprite. The screen was decluttered to allow the focus on the sprite, based upon feedback we received during the user testing session.

![Do Or Die System Design](Images/M5Images/statsCollage.jpg)

The stats screen was implemented according to the UI wireframe, however we have not implemented the sleep detection feature due to its dificulty to develop. Therefore, different statistics have been displayed.

![Do Or Die System Design](Images/M5Images/campaignShopCollage.jpg)

Initially our UI wireframe included a shop feature, however after adding a third user type (the Sponsor) we shifted our focus to implementing the challenges feature instead. The shop feature remains a valid possible future feature as dicussed in [Project Evaluation](ProjectEvaluation.md).

## Details of the communication protocols in use

Our Internet of Things product was developed utilising the M5Stack platform. Due to the use of this platform, we utilised WiFi connectivity to allow for communication between our subsystems. This allowed for data to move between web to desktop, M5Stack to desktop and desktop to both the Web and M5Stack. Further, we used MQTT(Message Queue Telemetry Tansport) as our communication protocol rather than something like HTTP web services. We made this decision for a few reasons:

* As HTTP is a synchronous protocol, the client is required to wait for the server to respond. On the other hand, with MQTT the client connects to the broker and subscribes to the message "topic" in the broker. The MQTT is able to receive all messages from the clients and route the messages to the relevant clients. This allows for us to communication across subsystems at the same time.

* HTTP is a one-way connection, this means that the client (ie. our M5Stack) is not able to passively receive messags from the server. By utilising the MQTT protocol, the client can subscribe to the topic and receive all messages. This allows for real-time updated data.

* MQTT allows for scalability of our product, when there are a number of devices connected across the platform. This is due to the fact that it utilises reduced network bandwith to move the data between subsystems, which would then lower operation costs.

* MQTT has become the standard for IoT communication, due to its flexibility and efficiency which made it an easy choice. Due to the fact that responses are received virtually instantaneously, it is the ideal choice to send data such as the user's live health bar (this is particularly useful in accurately showing when the user's Bean "dies").

To implement the MQTT communication protocol in our IoT product, we used [HiveMQ](https://www.hivemq.com). Our team established two topics, 'doordie_web' and 'doordie_steps'. Only one request type uses 'doordie_steps', which is detailed below.

Due to variability of payload attributes and sizes (especially concerning challenges), we made the decision to make a unifying request "type" parameter. For almost all request types, we chose to include a "user" parameter. Together, these two parameters allow our subsystems to ignore all messages in that topic unless there is an exact match. A list of all valid request types made between devices is found in [MQTT_request_types.txt](/Documentation/Mqtt_request_types.txt), this document was used by our group to ensure clear communication between subsystems. We will expand on the key communication protocols and the request types below.

### DESKTOP AND M5STACK

To send a user's profile data to the M5Stack from the database:

```
{
     "type": "push profile",
     "user_name": "Mario",
     "total_steps": 2200,
     "remaining_sec": 2000
}
```

This is only sent when M5 sends a request to the MQTT broker:

```
{
     "type": "pull profile",
     "user_name": "Mario"
}
```

Processing sends all challenges a user is enrolled in to be updated on their M5Stack:

```
{
    "type": "push user challenges",
    "user_name": "Mario",
    "challenges": [
    {
        "challenge_id": "1",
        "challenge_name": "10K Step Challenge",
        "description": "stepstep",
        "end_time": 1589500800,    
        "step_goal": 10000,
        "reward": 800
    },
  
    {
        "challenge_id": "2",
        "challenge_name": "Challenge 2",
        "description": "runrun",
        "end_time": 1589500800,
        "step_goal": 2000,
        "reward": 200
    }]
}
```

This is sent when the M5Stack requests the challenges of the user:

```
{
    "type": "pull user challenges",
 "user_name": "Mario"
}
```

To update the statistics of the user on the M5Stack:

```
{
 "type": "pull user stats",
 "user_name": "Mario"
}
```

The database uses the following request type to send stats to the M5Stack:

```
{
 "type": "push user stats",
 "user_name": "Mario",
 "daily_record": 10000,
 "weekly_record": 39000,
 "weekly_current": 18032
}
```

The M5Stack uses this request type to increment one step in the database, but there will be no response from the database. It is only for this request type that the 'doordie_steps' topic is used, as we expect steps to be sent every second. This allows for scalability of our product as the number of users increases:

```
{
     "type": "push step",
      "user_name": "Mario"
}
```

### DESKTOP AND WEB

When the web pushes a new profile to the database, there is no response from the database:

```
{ 
 "type":"push new profile",
 "user_name":"Mario",
 "user_type":"sponsor",
 "joined_date":1587980814845
}

```

The web requests a user profile from the database:

```
{
    "type": "pull web profile",
    "user_name": "Mario"
}
```

The database uses the same request type as it does for the M5Stack to send a user profile:

```
{
    "type": "push web profile",
    "user_name": "Mario",
    "total_steps": "2200",
    "remaining_sec": "2000",
    "challenges": [
    {
        "challenge_id": "1",
        "challenge_name": "10K Step Challenge",
        "description": "stepstep",
        "end_time": 1589500800,    
        "step_goal": 10000,
        "reward": 800
    },
  
    {
        "challenge_id": "2",
        "challenge_name": "Challenge 2",
        "description": "runrun",
        "end_time": 1589500800,
        "step_goal": 2000,
        "reward": 200
    }]
}
```

The web requests all challenges that the user is enrolled in with:

```
{
    "type": "pull user challenges",
    "user_name": "Mario"
}
```

The database responds with the same request type used for the M5Stack to send all challenges an individual user is enrolled in:

```
{
    "type": "push user challenges",
    "user_name": "Mario",
    "challenges": [
    {
        "challenge_id": "1",
        "challenge_name": "10K Step Challenge",
        "description": "stepstep",
        "end_time": 1589500800,    
        "step_goal": 10000,
        "reward": 800
    },
  
    {
        "challenge_id": "2",
        "challenge_name": "Challenge 2",
        "description": "runrun",
        "end_time": 1589500800,
        "step_goal": 2000,
        "reward": 200
    }]
}
```

The web requests all challenges:

```
{
    "type": "pull all challenges"
}
```

The database sends all current challenges to the web:

```
{
    "type": "push all challenges",
    "challenge": [
    {
        "challenge_id": "1",
        "challenge_name": "10K Step Challenge",
        "description": "stepstep",
        "end_time": 1589500800,    
        "step_goal": 10000,
        "reward": 800
    },
  
    {
        "challenge_id": "2",
        "challenge_name": "Challenge 2",
        "description": "runrun",
        "end_time": 1589500800,
        "step_goal": 2000,
        "reward": 200
    }]
}
```

When a sponsor adds new challenges, there is no response from the database:

```
{
    "type": "push new challenge",
    "challenge_id": "3",
    "challenge_name": "Challenge 2",
    "description": "runrun",
    "end_time": 1589500800,
    "step_goal": 2000,
    "reward": 200
}
```

When the user selects a challenge, there is no response from the database:

```
{
    "type": "push select challenge",
    "user_name": "Mario",
    "challenge_id": "1"
}
```

## Details of the data persistence mechanisms in use

Each user, challenge and sponsor is stored as a JSON object to allow for easy parsing and sending of payloads. The JSON format was used because parsing libraries exist for all devices. 

  In order to allow persistence we used users.json, sponsors.json and challenges.json files to store respective data. This format allows the central server to send an entire user profile when recieving a request from the M5 or web device to pull a profile using the data API. Each user object contains a challenges_id array which contains all the ids of currently enrolled challenges. Challenge_id array parameter is used to refer to enrolled challenges from challenges.json in order to keep payload lengths below the MQTT maximum. Similarly, each sponsor object also contains a challenge_id array (foreign key that refers to challenges data). This structure would ideally be implemented in a SQL relational database to increase speed and maintanability, as mentioned in project evaluation.

M5 device is stateless therefore does not store information locally apart from created variables such as the username, which is required to pull data from the database when the M5 first starts up. These are then pulled from the database via a pull user profile request type. Keeping the M5 stack stateless allowed for more modularity and reliability of the system, as even if the device breaks (which is a significant risk considering it is used for fitness and will be physically moved a lot) it can be replaced without loss of user data. If the device is stolen or lost, the user data is still stored on the central server and not the device, which means it can be removed and not leak information on the M5 stack. 

## Details of web technologies in use

Our website is react based and built on top of a simple react/bootstrap template.
The choice for these technologies was driven by some key needs of our website/team that ultimately led us to choose this set up:

* **Ability for integration of MQTT commuication protocol:** When looking into the different framework we realized that the script Tom provided us for the MQTT communication could be easily reused and integrated into all major Javascript based frameworks (e.g. Angular, React, Vue).
* **Ability to dynamicially refresh content on a regular basis in an easy way:** React turned out to be the obvious candidate to satisfy this need: Its logic is centered around an app state, with components getting rerendered every time the state changes. That way we could display a dynamic step / lifetime counter which would change in real time without refreshing the page.
* **Availability of UI templates for rapid but beautiful prototyping:** React is currently [the most widely used](https://hotframeworks.com/) web framework, so there were plenty of templates available. We chose a [free template by Creative Tim](https://demos.creative-tim.com/now-ui-kit/index.html), which included some basic UI components such as a navigation and a profile page and would allow us to build rapid prototypes without bothering about the details of styling and navigation.
* **Support for Object Oriented Design:** To support our object oriented design we were looking for a framework that supports the use of a strong object oriented design. React components are ideal to build class based software (see chapter 1.b).
* **The MQTTclient Class:** Every page needs to be able to send or receive json messages, usually both, to and from the MQTT broker, so we have implemented an MQTT class which handles all data to prevent repetition in the design of each page. As the incoming json messages over the broker for the web profile are the most flexible in nature out of all pages, the MQTT class has conditional rendering dependent on the internal state of the class. The MQTT class running on a given system listens to incoming messages based on the username so if another user is accessing the site from elsewhere, there is no mismatch of data between the sessions and each user won't interrupt the others navigating the website. This was designed in order to be scalable, and to ensure the client continues to listen to the broker until the correct packet of information has been received, which is parsed and interpreted.

![Do or Die System Implementation](Images/SystemImpLogo.png)
# 2. System Implementation [40pts]:
## a. Breakdown of project into sprints (showing the users stories implemented in each).

We organised our work as a series of one-week sprints from early March to mid-May. We met in person or talk as a group over Google hangouts each Monday at 3pm for a sprint review/retrospective. The work over from the last week was presented and discussed, with completed items marked as "done". The to-does for the coming week/sprint as well as the backlog for later sprints was agreed upon. The coding pairs for the different substreams had bilateral "stand-ups" to check on how the work is progressing and problem-solve. Also, we discussed interactions between subsystems as needed during the week. In the following week we listed all the items for the week as “WIP” (Work-in-progress) or “Done”. The backlog was moved to later sprints, with only items remaining in the done column in the end. 

As one of the key foundations of Agile software development is to have self-organising teams, we knew that it was important to collectively focus on the most important user stories to be implemented during each sprint. We were confident in our capabilities to successfully maintain a minimum viable product during each week's sprint. In order to keep this clear, we created a Gantt chart to be used between each of the teams working on the different subsystems. This was used in conjunction with our project's [Kanban Board](https://github.com/Team-Jag/Do-or-die-fitness-tracker/projects/1). Both of these features were useful to keep our work user focused, while ensuring cohesion between each subsystem. 
![Updated Gantt Chart](Images/updated_gantt.png)

In the follow section we will break down our goals of each sprint, list what was completed per subsystem, the key user stories implemented, and what remained in our Backlog in terms of WIP. 

### Sprint 1 : Define Architecture & Interactions (2.3-9.3) 
The goal of this sprint was to agree upon our architecture and the interactions so that the workstream would know how to design their sub-systems. During this sprint we decided on how we would move forward in developing our product. This included the creation of our Github repository, and beginning to familiarise ourselves with how we would use different features including the Kanban boards, Pull Requests and Issues. 

**DONE:**
* Defined and agreed on overall infrastructure (shared on Slack)
* Defined minimum viable product (MVP) with functions/classes/variables
* Defined interactions between subsystems including the function calls and their JSON syntax 
* Establish Github protocol (including how we would use the project board, as well as pull request and issue protocol)
* Design up a basic UI interface mockup for admin user story

**WIP:**
* Implementation of communication protocol 

### Sprint 2 : First Prototype (9.3-16.3) 
The goal of this sprint was to create a very basic proof of concept. Our team agreed that this was mainly focused on turning the M5Stack in to a pedometer, and that Processing is able to receive step data from the M5Stack and process it accordingly. 

**User Stories Implemented:**
* End-user able to use pedometer accurately, steps counts persists between sessions

**DONE:**
* M5Stack able to send a notification to server (Processing) for each new step
* Desktop able to process the notification, increment the total steps and ensure data persisted, and sends the updated user profile back to the M5
* M5 able to process message from processing and display total steps
* Created web design and mockup pages
* Decided on a UI interface for admin user story, and made a mockup Processing interface using dummy cp5 elements

**WIP:**
* Improve the accuracy of the step count

### NO SPRINT : Fight COVID-19 (16.3-30.3) 
Due to COVID-19, the team agreed to push all work to the backlog and not meet until after the deadline. As our team followed an Agile method for development, each of the sub-teams worked to ensure that we had completed what we had previously agreed to before continuing meetings the following Monday. This also allowed for us to restructure the goals of our project, and ensure that the way we had prioritised user stories was sufficient for ensuring our MVP. 

### Sprint 3 : [Alpha Version](https://github.com/Team-Jag/Do-or-die-fitness-tracker/pull/7) Release (30.3-6.4) 
The goal of this sprint was to release the Alpha version of our product, by pushing our MVP to the master branch. This involved ensuring all subsystems could receive, process, and send the intended MQTT commands. During this sprint, our main goal was to ensure that all three subsystems could interact with each other, and were accurately conforming to the [shared contract](https://github.com/Team-Jag/Do-or-die-fitness-tracker/blob/develop/Documentation/Mqtt_request_types.txt). 

**User Stories Implemented:**
* Implemented a health bar on the M5 stack, so that the user can visualize the Bean's remaining life
* Added a Bean sprite for the user's M5 stack, without animation
* Added dummy charts in admin view for visualisation of data

**DONE:**
* Improved accuracy of the step count
* Improve the view for the M5 stack (including the above additions of the Bean sprite and the health bar)
* Desktop database API able to add challenge to user, sends challenges enrolled by user, add new user sent from web, and add new challenges
* Web able to send and receive dummy data from the broker

**WIP:**
* All subsystem able to receive, process and send the intended MQTT request types
* All subsystems provide a basic version of the agreed visualization 
* MQTT message length issue with M5 Stack 

### Sprint 4 : Resolving Issues and Enhancing Features (6.4-13.4) 
The goal of this sprint was be to get to advance our prototye, which fixed interaction issues that arose during the sprint review on 6th of April. During this sprint, mainly with the End-User in mind, we decided to focus on improving design and visuals as well as extending basic functionalities. This included viewing their statistics on the M5Stack, and the creation of custom challenges for Sponsors on the Web.

**User Stories Implemented:**
* Basic animation for Bean sprite implemented
* User can see the challenges that they are enrolled in on M5 stack (dummy data)
* User can see basic statistics about their step count on M5 stack (dummy data)
* Web can see their full user information and challenges if they are logged in (dummy data)
* Web can create new customised challenges for all users
* Admin can see charts of total users, challenges, sponsors
* Admin dashboard pulls data from backend database API

**DONE:**
* All subsystems able to receive, process and send the intended MQTT commands
* All subsystems provide a basic version of the agreed visualization 
* M5 home view enhanced with animation 
* Implementation of statistic and challenge view on M5 stack, had to use dummy data due to the MQTT message length issue
* Agreed on how user death would work across subsystems

**WIP:**
* MQTT message length issue with M5 Stack 
* Real data for statistics and challenges on M5 stack
* All subsytems to handle user death 

### Sprint 5 : [Beta Version](https://github.com/Team-Jag/Do-or-die-fitness-tracker/pull/44) Release (13.4-20.4) 
The goal of this sprint was to release the Beta version of our product, and push it to the master branch. During this sprint we were able to replace the dummy data for challenges that we had on the M5Stack. Also, the database was now able to automatically update when the user reached a goal of the challenge that they had enrolled in and appropriately add the time reward to the user's account. 

**User Stories Implemented:**
* User now able to see real-time challenge data on M5 stack and on the Web
* Animation for Bean now based on life left on M5 stack
* Death screen if the time left is zero on M5 stack
* Admin can see a list of all users and proportion of players currently alive

**DONE:**
* MQTT message length issue resolved 
* Replaced dummy data with appropriate server requests on M5 stack for challenges
* Implemented life timer countdown in desktop user API
* Database automatically updated when user reaches any goal of challenges enrolled and adds rewards
* Improved sprite animation: fequency and height of bounces linearly scales with time left
* M5 stack handles user death by printing a death screen once, and then executing empty loops until shut down

**WIP:**
* Implement interaction feature on M5 stack
* Replace statistics dummy data with data from server on M5 stack
* Add sponsor API to desktop
* Adding new user should initialise user data with default values

### Sprint 6 : [Version 1.0](https://github.com/Team-Jag/Do-or-die-fitness-tracker/pull/115) Release (20.3-27.4) 
The goal of this sprint was to clean up our code, and implement any final features before releasing Version 1.0 of our product. In the lead up to the end of our sprint, we realized that there was an issue between the database and the web. 

**User Stories Implemented:**
* User able to see their statistics accurately reflected on statistic view
* Admin can search for a specific user profile and see their information
* Admin can see charts that track playerbase over time on a daily, weekly and monthly timescale
* Sponsor redirected to the create challenge page on the web 
* On creating an account on Web, user can decide if they are a user or a sponsor, to determine if they can create challenges

**DONE:**
* Replaced dummy data with appropriate server requests on M5 stack for statistics
* Added statistics data into user.json
* Implemented sponsor API in desktop and push new challenge from web will add challenge to sponsor data
* Desktop automatically enrols new user to a maximum of 10 challenges, and initialises default values

**WIP:**
* Implement interaction feature on M5 stack

### Sprint 7 : Version 1.1 (optional) and Write-Up (27.4-4.5) 
The goal of this sprint will be to do the write-up, as well as address any issues that arise from the release of Version 1.0 and implement any final features. In order to undertake the writing of our portfolio, our group chose to create a second [Kanban board](https://github.com/Team-Jag/Do-or-die-fitness-tracker/projects/2) to continue using the same Agile working methods that we had development of our software.

**User Stories Implemented:**
* The End-User is able to interact personally with their Bean. 

**DONE:**
* Implemented interaction feature on M5 stack

**WIP:**
* 

## b. Details of how you evaluated your designs (techniques used & awareness of their limitations)

Initially for the design idea of the base product we wanted to produce, the minimum viable product, we used a design evaluation matrix with scoring from 0 to 5 for each small feature in order to determine its value based on the strategic outcomes. The metrics used to determine the scores were: the idea's potential impact, the timeline to implement said idea, and difficulty to learn the technologies required to implement. The features shown in the first sprint above were these initial features decided by the evaluation matrix.

Potential limitations of using the evaluation matrix are the chance of concentrating on features of too little significance, instead of concentrating on user centric features we instead focused on what was achievable in a given sprint timeframe. The scores assigned to each metric are also entirely subjective, so a more complex analysis would have been more appropriate to critically determine the value of a feature.

As we were following the Agile method for development of our product, at the end of each sprint we performed exhaustive tests on each sub-system where the results were discussed in our scrum meetings performed over Google Hangout. Once these tested features were tested and working, we decided on each successive feature to implement in the design based on an informal SWOT analysis first as individual pairs from each team, then agreeding as an overall team on pre-approved ideas from the pairs dependent on timeline and other subteam requirements. We believed the SWOT evaluation method to be more useful in our design approach over each sprint than the evaluation matrix.

## c. Social and Ethical Implications of Do or Die Fitness Tracker
### Social Benefits
We designed our fitness tracker in hopes of providing incentives to individuals to maintain a healthy lifestyle and keep active. Our choice in the gamification of a fitness tracker was aimed to associate exercise with positive feelings of motivation and fun, while also providing a challenge (the Bean's life timer countdown). These were attempted to be achieved by implementing challenges that can significantly boost the lifetime of the user's Bean as well as small lifetime rewards when the user walks/runs around. There is also a ranking system implemented on the website as a way to further motivate the user to achieve higher ranks by effectively exercising more. We also hope to provide the user companionship with the Bean, a character which behaves like a pet/tamagotchi.

### Data Privacy
For our prototype, we currently only require a username to be able to create an account on the website and use our fitness tracker. It is also possible to provide other types of information on the web account, such as a profile photo and biography. Our device only collects data on steps taken and only physically stores the username and Wi-Fi password, but no geolocation data is stored. When the device syncs with the database, data on the number of steps taken is transferred. For each user, the management database stores the username, steps taken, challenges enrolled or finished, and the lifetime of the Bean. Although data provided by users are limited and only few identifiers are stored (username, which can be a fake or real name, and profile picture), this data can potentially be exploited by hackers. Another issue also arises in data withdrawal, as presently our software has no implementations yet to be able to remove all user data provided and collected.

### Data Usage
There are possible concerns on how personal fitness data can be used in the future. Such recent concerns include the John Hancock program, in which an insurance company required a fitness tracker to sell their interactive policies based on the user's activity level recorded. As fitness trackers are essentially pedometers, they may not be able to track accurate fitness data in other forms of exercises, such as cycling or swimming. Moreover, our fitness tracker has not been tested or adapted to the less well-able bodied, such as the handicapped. Hence, a possible issue was raised in which the disadvantaged could be forced to buy more expensive insurance policies due to the inaccurate fitness data gathered.

### Social Implications
As our platform relies on both rewards and punishments, in the forms of increasing the life timer and the Bean dying respectively, there may be implications on the user's state of mental health. Attachment to the Bean and its impending doom and subsequent death might lead to a sense of significant loss. Additional potential stressors include the leaderboard ranking system implemented based on the number of steps taken by the user that can be viewed on the website. The user then might relate their fitness levels with their rankings, which might discourage them further to attempt exercising if they are constantly stuck with low rankings.

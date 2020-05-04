![Do or Die System Implementation](Images/SystemImpLogo.png)
# System Implementation [40pts]:

Now that we have highlighted how we settled on the [design of our system](SystemDesign.md), we will explain how the key aspects of our system were implemented. We will demonstrate how we used the architectural design that we created for our system to meet and implement each of our user stories, as well as how we maintained a minimum viable product by breaking our project into sprints. We will also evaluate the design of our system, and highlight the social and ethical implications of our product. 

## Table of Contents

- [**Software Development Cycle**](#software-development-cycle)
- [**Breakdown of project into sprints**](#breakdown-of-project-into-sprints)
  - [Sprint 1 : Define architecture & interactions (2.3-9.3)](#sprint-1--define-architecture--interactions-23-93)
  - [Sprint 2 : First prototype (9.3-16.3)](#sprint-2--first-prototype-93-163)
  - [NO SPRINT : Fight COVID-19 (16.3-30.3)](#no-sprint--fight-covid-19-163-303)
  - [Sprint 3 : Alpha version release (30.3-6.4)](#sprint-3--alpha-version-release-303-64)
  - [Sprint 4 : Resolving issues and enhancing features (6.4-13.4)](#sprint-4--resolving-issues-and-enhancing-features-64-134)
  - [Sprint 5 : Beta version release (13.4-20.4)](#sprint-5--beta-version-release-134-204)
  - [Sprint 6 : Version 1.0 release (20.3-27.4)](#sprint-6--version-10-release-203-274)
  - [Sprint 7 : Version 1.1 (optional) and write-up (27.4-4.5)](#sprint-7--version-11-optional-and-write-up-274-45)
- [**Details of design evaluation (techniques used & limitations)**](#details-of-design-evaluation)
  - [Initial Evaluation](#initial-evaluation)
  - [Evaluating the Quality Requirements](#evaluating-the-quality-requirements)
  - [User Testing and Evaluation](#user-testing-and-evaluation)
  - [Unit Testing](#unit-testing)
  - [System Integration](#system-integration)
  - [Reflection on Evaluation](#final-reflection-on-evaluation)
- [**Social and ethical implications**](#social-and-ethical-implications)
  - [Code of ethics](#code-of-ethics)
  - [Social benefits](#social-benefits)
  - [Data privacy and security](#data-privacy-and-security)
  - [Data usage](#data-usage)
  - [Social implications](#social-implications)
  
## Software Development Cycle
Prior to exploring how our team broke our project in to sprints, and how we evaluated our designs, it is first necessary to explain the development cycle that we used. Our team chose to follow an Agile model for development, that is focusing on incremental and iterative development. One of the key aspects of Agile development is active user involvement, which affected the way that we evaluated our designs. Using this method, we ensured that we always had a valuable product in the master branch of our Github. Our Github processes will be explained in further detail when we [evaluate our project](ProjectEvaluation.md). 

Using the Agile model allowed for faster software development. At the beginning of each sprint we decided the features that we would implement during that sprint, the tests that we expected each subsystem to pass, and the user stories that we expected to be satisfied by the implementation of those features. During each iteration we defined the requirements based on the backlog from previous sprints, and test user feedback. We then designed the software based on the requirements that we had established as a group, before coming back together during our weekly sprint review to undertake quality assurance testing and intergration testing. We then integrated our product by merging all changes to the master branch of our Github. Finally, we evaluated our previous version before defining the requirements for the next sprint. 

![Agile](Images/agile.png)

The above diagram, copied from this [website](https://hackernoon.com/a-case-study-type-insight-into-agile-methodologies-for-software-development-cd5932c6), demonstrates the development cycle that our team followed during the creation of our product. 

## Breakdown of project into sprints

We organised our work as a series of one-week sprints from early March to mid-May. We met in person or talk as a group over Google hangouts each Monday at 3pm for a sprint review/retrospective. The work over from the last week was presented and discussed, with completed items marked as "done". The to-does for the coming week/sprint as well as the backlog for later sprints was agreed upon. The coding pairs for the different substreams had bilateral "stand-ups" to check on how the work is progressing and problem-solve. Also, we discussed interactions between subsystems as needed during the week. In the following week we listed all the items for the week as “WIP” (Work-in-progress) or “Done”. The backlog was moved to later sprints, with only items remaining in the done column in the end. 

As one of the key foundations of Agile software development is to have self-organising teams, we knew that it was important to collectively focus on the most important user stories to be implemented during each sprint. We were confident in our capabilities to successfully maintain a minimum viable product during each week's sprint. In order to keep this clear, we created a Gantt chart to be used between each of the teams working on the different subsystems. This was used in conjunction with our project's [Kanban Board](https://github.com/Team-Jag/Do-or-die-fitness-tracker/projects/1). We used the Kanban board to keep it clear which requirements needed to be done, what people were currently working on, and what was completed. We also added a backlog column for features that we pushed for later iterations. Both of these features were useful to keep our work user focused, while ensuring cohesion between each subsystem. 
![Updated Gantt Chart](Images/updated_gantt.png)

In the follow section we will break down our goals of each sprint, list what was completed per subsystem, the key user stories implemented, and what remained in our Backlog in terms of WIP. 

### Sprint 1 : Define Architecture & Interactions (2.3-9.3) 
The goal of this sprint was to agree upon our architecture and the interactions so that the workstream would know how to design their sub-systems. During this sprint we decided on how we would move forward in developing our product. This included the creation of our Github repository, and beginning to familiarise ourselves with how we would use different features including the Kanban boards, Pull Requests and Issues. This also included the ideation stage, and definition of the communication protocol between devices so that different teams could begin implementation autonomously.

**DONE:**
* Defined and agreed on overall infrastructure (shared on Slack)
* Defined minimum viable product (MVP) with functions/classes/variables
* Defined interactions between subsystems including a first iteration of the request types and their JSON syntax 
* Establish Github protocol (including how we would use the project board, as well as pull request and issue protocol)
* Design a basic UI interface mockup for admin user story

**WIP:**
* Implementation of communication protocol 

**User Stories To Prioritize in next sprint**
The most important of our user stories is that of the end-user, so our first sprint should focus on delivering a fitness tracking feature onto the M5Stack in the form of a simple step counter.
In order to allow the user to keep track of their steps between sessions, we need to make thestep data persistent, so we also need to develop a basic first version of our desktop server.

### Sprint 2 : First Prototype (9.3-16.3) 
The goal of this sprint was to create a basic proof of concept to demonstrate the key feature of incrementing step count, a vital user requirement of the end-user story. Our team agreed that this was mainly focused on turning the M5Stack in to a pedometer, and that Processing is able to receive step data from the M5Stack and process it accordingly. 

**User Stories Implemented:**
* The End-user is able to use the M5Stack to track their steps. The step count persists between sessions.

**DONE:**
* M5Stack able to send a notification to Desktop server for each new step
* Desktop able to process the notification, increment the total steps and ensure data persisted, and sends the updated user profile back to the M5
* M5 able to process message from processing and display total steps
* Created web design and mockup pages
* Decided on a UI interface for admin user story, and made a mockup Processing interface using dummy cp5 elements

**WIP:**
* Improve the accuracy of the step count

**User Stories to Prioritize in next sprint**
The next key user-story is that of the sponsor, so in the next sprint we should focus on delivering a web interface where a sponsor can sign-up and create challenges for the end-user. 
We must keep a secondary focus on beginning to design an interface for our Desktop server from where the Admin can monitor the performance of the product.

<table>
<tr>
  <th>Technology</th>
  <th>Key User Stories Implemented</th>
  <th>Issues Encountered</th>
</tr>
<tr>
  <td>Desktop</td>
  <td>End-user is able to use the M5Stack as a pedometer and view total step count. This is implemented by parsing the push step request sent from the M5Stack and incrementing the step count in the database. The admin has a basic screen and can see dummy elements creating a basic mockup of the final view.</td>
  <td>No issues were discovered in this sprint.</td>
</tr>
<tr>
  <td>Web</td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td>M5Stack</td>
  <td>Developed step counter on M5Stack using external library to interpret gyroscope data. Implemented basic communication mechanism </td>
  <td></td>
</tr>
</table>


### NO SPRINT : Fight COVID-19 (16.3-30.3) 
Due to COVID-19, the team agreed to push all work to the backlog and not meet until after the deadline. As our team followed an Agile method for development, each of the sub-teams worked to ensure that we had completed what we had previously agreed to before continuing meetings the following Monday. This also allowed for us to restructure the goals of our project, and ensure that the way we had prioritised user stories was sufficient for ensuring our MVP. 

### Sprint 3 : [Alpha Version](https://github.com/Team-Jag/Do-or-die-fitness-tracker/pull/7) Release (30.3-6.4) 
The goal of this sprint was to release the Alpha version of our product, by pushing our MVP to the master branch. This involved ensuring all subsystems could receive, process, and send the intended MQTT commands. During this sprint, our main goal was to ensure that all three subsystems could interact with each other, and were accurately conforming to the [shared contract](https://github.com/Team-Jag/Do-or-die-fitness-tracker/blob/develop/Documentation/Mqtt_request_types.txt). 

**User Stories Implemented:**
* The sponsor is now able to create an account and create new challenges through our web interface.
* The end-user is now able to create an account and enrol in challenges on our web interface.
* We added a Bean sprite on the M5Stack's interface, without animation, along with a health bar representing its remaining life. This should elicit an emotional response in the user leading to an increase in motivation.
* The Admin can now visualize product performance (dummy) data in the Desktop app

**DONE:**
* Improved the view for the M5 stack (including the above additions of the Bean sprite and the health bar)
* Desktop database API able to add challenge to user, sends challenges enrolled by user, add new user sent from web, and add new challenges
* Web able to send and receive dummy data from the broker

**WIP:**
* All subsystems provide a basic version of the agreed visualization

**User stories to Prioritize in next sprint**
At this point each of our user stories has been at least partially delivered, so our work will now focus on improve each of the user stories.
The next task is to work on our user interfaces in order to improve user experience across all user-stories.

<table>
<tr>
  <th>Technology</th>
  <th>Key User Stories Implemented</th>
  <th>Issues Encountered/Addressed</th>
  <th>Issue Handling</th>
</tr>
<tr>
  <td>Desktop</td>
  <td>User is able view and select challenges, sponsor can add new challenges, user is also able to create new profile. Admin can see basic charts showing analytics of dummy data.</td>
  <td>As data sent from the web to create new profile did not add default values for other required data (e.g. remaining_sec), the system will crash if a request for this faulty data was fetched and attempted to be sent.</td>
  <td>As the issue encountered was due to the lack of testing on how the API handles null JSON objects, future implementations should include relevant testing. However, due to limited time for the project, this was not carried out and the extent of the implementation of a working system was only for the sake of the demo.</td>
</tr>
<tr>
  <td>Web</td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td>M5Stack</td>
  <td></td>
  <td></td>
</tr>
</table>


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

**User stories to prioritize for next sprint**
Now that our devices are communicating effectively and the data is displayed properly on each of our subsystems, our focus is going to be on polishing our systems and replace dummy data with real data obtained with appropriate requests from device to device.
It sould also be made evident on the M5Stack when the Bean's health reaches zero. 

<table>
<tr>
  <th>Technology</th>
  <th>Key User Stories Implemented</th>
  <th>Issues Encountered/Addressed</th>
</tr>
<tr>
  <td>Desktop</td>
  <td>Admin now has access to real data analytics pulled from the database, and can track flat totals of sponsors, users and challenges.</td>
  <td></td>
</tr>
<tr>
  <td>Web</td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td>M5Stack</td>
  <td></td>
  <td>When attempting to replace Challenges and Statistics dummy data on the M5Stack with appropriate requests on the MQTT Topics, we found that the M5Stack ignored all messages on the MQTT Topic that were above a certain length.</td>
</tr>
</table>


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

**User stories to prioritize for next sprint**
Now that our devices are communicating effectively and the data is displayed properly on each of our subsystems, our focus is going to be on polishing our systems and replace dummy data with real data obtained with appropriate requests from device to device.
It sould also be made evident on the M5Stack when the Bean's health reaches zero. 

<table>
<tr>
  <th>Technology</th>
  <th>User Stories Implemented</th>
  <th>Issues Encountered/Addressed</th>
</tr>
<tr>
  <td>Desktop</td>
  <td>User is able to see life timer countdown and finishing challenges will add rewards to health. Admin can see statistics updating in real time as the proportion of currently "alive" users changes.</td>
  <td>As this is only a prototype, we decided not to implement a 'real' timer which would countdown even when the system is down. It was implemented this way just for convenience for the demo, so dummy data does not have to be initialised new every time.</td>
</tr>
<tr>
  <td>Web</td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td>M5Stack</td>
  <td></td>
  <td></td>
</tr>
</table>


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

<table>
<tr>
  <th>Technology</th>
  <th>Key User Stories Implemented</th>
  <th>Issues Encountered/Addressed</th>
</tr>
<tr>
  <td>Desktop</td>
  <td>New end-user will be automatically enrolled to a maximum of 10 available challenges.</td>
  <td>As there was a limit of in what the M5Stack is able to parse from JSON Arrays, a limit of 10 challenges for each user was determined. However, no extensive testing (including attempts in integration to select more than 10 challenges from the web) has been done to ensure correct implementation.</td>
</tr>
<tr>
  <td></td>
  <td>All user, sponsor, and challenges data can be viewed in real-time through requests between devices. The admin can now access profile information for a specific user and see challenges they have completed and are currently enrolled in.</td>
  <td>During our attempts at integrating all systems for our video demo, the desktop app frequently crashed when large amounts of requests were received from the web. We tried to investigate the problem, it seemed that the issue lies in how we implemented the refreshDashboard for the admin.</td>
</tr>
<tr>
  <td>M5Stack</td>
  <td></td>
  <td></td>
</tr>
</table>


### Sprint 7 : Version 1.1 (optional) and Write-Up (27.4-4.5) 
The goal of this sprint will be to do the write-up, as well as address any issues that arise from the release of Version 1.0 and implement any final features. In order to undertake the writing of our portfolio, our group chose to create a second [Kanban board](https://github.com/Team-Jag/Do-or-die-fitness-tracker/projects/2) to continue using the same Agile working methods that we had development of our software.

**User Stories Implemented:**
* The End-User is able to interact personally with their Bean. 

**DONE:**
* Implemented interaction feature on M5 stack

**WIP:**
* 

<table>
<tr>
  <th>Technology</th>
  <th>User Stories Implemented</th>
  <th>Issues Encountered</th>
</tr>
<tr>
  <td>Desktop</td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td>Web</td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td>M5Stack</td>
  <td></td>
  <td></td>
</tr>
</table>


## Details of design evaluation

A key aspect of our software development cycle came from our weekly software and design evaluation during our meetings. Each of our techniques for evaluating our design will be considered in turn in the following section, as well as their limitations. Going hand in hand with our software design cycle and during each sprint, we also found that we had - in some ways - a design evaluation cycle. At the beginning of each sprint, we would have a preliminary design that we expected we would develop during that sprint. This included the user stories that we wanted to implement, and how we would do this. During the sprint we would implement these, as highlighted above, however within our design cycle we would then have a number of forms of evaluation at the end of our sprint. This stage of our design cycle allowed us to shape and form our requirements for the next sprint, as well as reprioritize the user stories where necessary. During the design evaluation phase, we would utilise a number of methods and techniques for evaluation. The main methods for our design evaluation involved some form of testing to ensure that our design was working as expected. 

### Initial Evaluation
Initially for the design idea of the base product we wanted to produce, the minimum viable product, we used a design evaluation matrix with scoring from 0 to 5 for each small feature in order to determine its value based on the strategic outcomes. The metrics used to determine the scores were: the idea's potential impact, the timeline to implement said idea, and difficulty to learn the technologies required to implement. The features shown in the first sprint above were these initial features decided by the evaluation matrix.

Potential limitations of using the evaluation matrix are the chance of concentrating on features of too little significance, instead of concentrating on user centric features we instead focused on what was achievable in a given sprint timeframe. The scores assigned to each metric are also entirely subjective, so a more complex analysis would have been more appropriate to critically determine the value of a feature. However, our team found as we moved further in to evaluating our design during each sprint, that this evaluation method was not as useful as we had first thought. 

### Evaluating the Quality Requirements
We knew when designing our system initially that we wanted to focus largely on the non-functional requirements. These included the security of our system, the maintainability, the ease of use, and the reliability of our system as a whole. This relied in large part on testing our system in an integrated manner, which will be explored further below. However, we will first consider each of these "non-functional" requirements and how evaluating them during our sprints changed the design of our system. 

#### Security
From the design stage (link to design doc here?) to the implementation stage, security was considered an intergral part of the system as a whole. Implementing the database class as abstract and private allowed for request validation before the persistent files were accessed, which seperates the physical data from other devices. This lowers the chance of injection attacks, and consequently having unvalidated data reflected back to the user (cross-site scripting on the web side, arbitrary code injection on the M5 side). Additionally this seperatation protects the database files themselves from being malformed and causing a Denial of Service attack or non-malicious issues stemming from malformed requests.

Additionally, we took great care in implementing the M5 device as stateless. While lacking authentication, even if the device was stolen or lost, user information can be removed as everything is stored on the back-end of the processing app.

#### Maintability
While our team was a relatively small team, and could easily maintain our product if necessary, we wanted to develop it in a way that allowed it to be maintained by a larger team. This meant developing each part of our system to conform with our shared contract, to allow us to meet new requirements. Moreover, make the code in each part of our system as clear as possible to allow for quick changes. 

Code was implemented with modularity in mind, which allowed each device team to update their subsystem without breaking the entire codebase. 

#### Ease of Use

#### Reliability

### User Testing and Evaluation
The one key concept that our team kept coming back to was that our product was made for someone, and thus our main focus was on the end-user when designing and implementing our product. If the end-user was not happy, or not able to use our product, then there would be no need for the admin or the sponsor. While our user testing was affected by our move to remote working, prior to this we used this method to evaluate our design extensively during each sprint. We had our peers and friends use different aspects of our product, and comment on what they liked and did not like. Moreover, we watched how they interacted with the different parts of our system in order to see what needed to potentially be changed, and what could be made easier so that the user did not feel like accessing different parts of our system were a chore. 

This method for evaluating our design was incredibly effective, we were able to simplify certain parts of our architecture such as what we expected from the M5Stack. Once we realized that most users would be content to first have a simple step tracker with their Bean animated, we put our focus on this user story rather than trying to implement too much at once. This evaluation technique allowed us to step back and help us to realize what was most important from our design. 

Moreover, it ensured that we prioritised what needed to change. One example of this was the decision to change the log in feature on the web. While designing our product we decided that you would need to log in with a username as well as an email, however we quickly realized that this was cumbersome for the user and it would make more sense for them to just log in with their username. This was due to user evaluation of our design. 

### Unit Testing
At every stage of the implementation process we aimed to have a set of tests for each component in order to verify they worked correctly. In particular, the Processing backend up utilized a testing class which compared dummy JSON payloads against existing files in the database to ensure the correct information was pulled. Additionally, tests were added to show the app could handle edge cases. This included purposefully malformed requests (to make sure the app did not crash), and insertion/deletion of null objects, in order to be certain the database API could handle any type of input. The front-end of the desktop app relied on visual user testing due to its dependancy on the draw() function, but crafted JSON objects were manually added to the database storage and this was compared against the totals drawn to make sure they were accurate. 

Due to the physical nature of the M5 device, the gyroscope had to be tested by physically moving it and comparing the expected step increments with what resolved through the step function.

### System Integration 
As the success of our product relied on our three key subsystems working together, it was necessary to perform extensive integration testing at the end of each sprint. This would take place during our weekly scrum. During this aspect of evaluating our design, we would go through our shared contract to ensure that all systems preformed as expected when using the shared contract. During earlier sprints, it was clear that there was unnecessary information included in certain request types and that these would have to be adjusted. The success of this method of evaluation, however, relied on ensuring that each unit was thoroughly tested individually. Once we were certain of this, we tested them together. 

Due to the fact that we implemented a shared contract between all subsystems, it was easy to test them together. We chose to take an incremental approach to integrating our subsystems during each sprint. By doing it in this manner, we were able to first test that the web and desktop, for example, integrated as expected and both responded correctly to the same request types. Once we certain of this, we were able to test the M5Stack with the desktop before then testing all subsystems as a single unit. As the web and M5Stack did not directly interact, this allowed for ease of testing. 

#### Test Scenarios
After integrating our system for the first time, we realized that we needed a more effective way of ensuring that our systems had integrated correctly. Thus, we decided to focus on testing the user stories that we had outlined at the beginning of the sprint during each scrum. Doing this allowed us to ensure that we had not only successfully implemented that user story, but that our subsystems were also working as expected. While undertaking the testing scenarios, we would make note of any bugs that arose and ensure that they were prioritised to be fixed during the next sprint. 

By ensuring that we executed each user story on our integrated system, we knew that we were successfully implementing those user stories. For example, when implementing the user story of having the end-user log on to the web to view their live step count we were able to test all three subsytems. We knew that the M5Stack was accurately sending the step information to the database. From there, the database correctly sent the updated step count for that user to the web as well as calculated how much time they had left, and the web was then able to display that information. 

Our team felt that this was one of the most effective ways of evaluating our system, and often highlighted certain issues that we had to address. This included, for example, the fact that we noticed during one sprint that the web and M5Stack were displaying different step data. Thus, prior to integrating our systems in the master branch, we had to address that issue. This was easily fixed when we realized that one team was using an outdated version of our shared contract. 

We do recognize that there are certain limitations to this method, mainly that we were limited in the amount of test data that we could use. We would have to adjust the process when scaling the project for a larger userbase, and be prepared with a large amount of mock data. Moreover, it was possible that we could have had more test cases to ensure that all aspects of our system were working as expected. During each iteration, we attempted to implement as many test cases as possible to reflect this. 

### Final Reflection on Evaluation

Our team was happy in the effectiveness of this approach, as rather than waiting until the end of developing our software, we knew that we always had a minimum viable product in our master branch.

## Social and ethical implications
### Code of ethics
To ensure that we develop software for the greater good, we follow the [BCS Code of Conduct](https://www.bcs.org/membership/become-a-member/bcs-code-of-conduct/) in developing our software. Hence, regarding our prototype software, we will address **public interest** (social benefits, data privacy and security), how we uphold our **professional competence and integrity**, **duty to relevant authority**, and **duty to the professions** in the following sections:

### Social benefits
We designed our fitness tracker in hopes of providing incentives to individuals to maintain a healthy lifestyle and keep active. Our choice in the gamification of a fitness tracker was aimed to associate exercise with positive feelings of motivation and fun, while also providing a challenge (the Bean's life timer countdown). These were attempted to be achieved by implementing challenges that can significantly boost the lifetime of the user's Bean as well as small lifetime rewards when the user walks/runs around. There is also a ranking system implemented on the website as a way to further motivate the user to achieve higher ranks by effectively exercising more. We also hope to provide the user companionship with the Bean, a character which behaves like a pet/tamagotchi.

### Data privacy and security
The data we collect from users and sponsors for our prototype is limited. We currently only require a username to be able to create an account on the website and use our fitness tracker. It is also possible to provide other types of information on the web account, such as a profile photo and biography. Our device only collects data on steps taken but always updates its data from the database, and only physically stores the username and Wi-Fi password (no geolocation data is stored). Only the management database will store all data such as the username, steps taken, challenges enrolled or finished, and the lifetime of the Bean; data is only gathered and used by our Services and will not be shared to any other platforms, unless lawfully required.

However, this data can potentially be exploited by hackers, as we have not encrypted our data storage, nor the transfer of data during communication between devices. If the MQTT topic is known, anyone can subscribe onto the topics and view personal information. Another issue also arises in data withdrawal, as presently our software has no implementations yet to be able to remove any user data provided and collected if the user/sponsor wishes to remove their account. This is indeed a violation of General Data Protection Regulation (GDPR), hence we cannot deploy our software for public use until this is addressed.

### Data usage
There are possible concerns on how personal fitness data can be used in the future. Such recent concerns include the John Hancock program, in which an insurance company required a fitness tracker to sell their interactive policies based on the user's activity level recorded. As fitness trackers are essentially pedometers, they may not be able to track accurate fitness data in other forms of exercises, such as cycling or swimming. Moreover, our fitness tracker has not been tested or adapted to the less well-able bodied, such as the handicapped. Hence, a possible issue was raised in which the disadvantaged could be forced to buy more expensive insurance policies due to the inaccurate fitness data gathered. We encourage other software developers to equally critically evaluate of how their software can be adopted to be more inclusive of the disadvantaged community.

### Social implications
As our platform relies on both rewards and punishments, in the forms of increasing the life timer and the Bean dying respectively, there may be implications on the user's state of mental health. Attachment to the Bean and its impending doom and subsequent death might lead to a sense of significant loss. Additional potential stressors include the leaderboard ranking system implemented based on the number of steps taken by the user that can be viewed on the website. The user then might relate their fitness levels with their rankings, which might discourage them further to attempt exercising if they are constantly stuck with low rankings. Additionally, addiction to our gamified fitness tracker might be possible, although this is not clear whether this could be an issue as we only require healthy activities to play our product.

![Do or Die System Implementation](/Portfolio/Images/SystemImpLogo.png)
# 2. System Implementation [40pts]:
## a. Breakdown of project into sprints (showing the users stories implemented in each).

We organised our work as a series of one-week sprints from early March to mid-May. We met in person or talk as a group over Google hangouts each Monday at 3pm for a sprint review/retrospective. The work over from the last week was presented and discussed, with completed items marked as "done". The to-does for the coming week/sprint as well as the backlog for later sprints was agreed upon. The coding pairs for the different substreams had bilateral "stand-ups" to check on how the work is progressing and problem-solve. Also, we discussed interactions between subsystems as needed during the week. In the following week we listed all the items for the week as “WIP” (Work-in-progress) or “Done”. The backlog was moved to later sprints, with only items remaining in the done column in the end. 

In order to keep it clear which user stories were implemented during each sprint, we created a Gantt chart to be used between each of the teams working on the different subsystems. This was useful to keep our work user focused, while ensuring cohesion between each subsystem. You can view the [full Gantt chart](https://uob-my.sharepoint.com/:x:/g/personal/ac16888_bristol_ac_uk/EXltfbLEnNFLrGLOGOxgZcIB2oqj_ft_TP9LevpsozfhVg?e=TUTMn7) of the user stories that we implemented during each sprint. 

### Sprint 1 Define Architecture & Interactions (2.3-9.3) 
The goal of this sprint was to agree upon our architecture and the interactions so that the workstream would know how to design their sub-systems.

**DONE:**
* Defined and agreed on overall infrastructure (shared on Slack)
* Defined minimum viable product(MVP) with functions/classes/variables
* Defined interactions between subsystems including the function calls and their JSON syntax 
* Establish Github protocol (including how we would use the project board, as well as pull request and issue protocol)

**WIP:**
* Implementation of communication protocol 

### Sprint 2 First Prototype (9.3-16.3) 
The goal of this sprint was to create a very basic proof of concept.

**User Stories Implemented:**
* End-user able to use pedometer accurately, steps counts persists between sessions

**DONE:**
* M5 Stack able to send a notification to server (Processing) for each new step
* Processing able to process the notification, calculate the total steps and send it back to the M5
* M5 able to process message from processing and display total steps
* Created web design and mockup pages

**WIP:**
* Improve the accuracy of the step count

### NO SPRINT : Fight COVID-19 (16.3-30.3) 
Due to COVID-19, the team agreed to push all work to the backlog and not meet until after the deadline. 

### Sprint 3 Alpha Version Release (30.3-6.4) 
The goal of this sprint was to release the Alpha version of our product, by pushing our MVP to the master branch. This involved:

**User Stories Implemented:**
* Implemented a health bar, so that the user can visualize the Bean's remaining life 
* Added a Bean sprite for the user's M5 stack, without animation

**DONE:**

**WIP:**
* All subsystem able to receive, process and send the intended MQTT commands
* All subsystems provide a basic version of the agreed visualization 

### Sprint 4 Beta Version (6.4-13.4) 
The goal of this sprint will be to get to advance our prototye, including:
* Fix interaction issues that arise in the sprint review on 6th of April
* Improve design and visuals
* Extend functionalities (TBD)

**User Stories Implemented:**
* 

**DONE:**
* 

**WIP:**
* 

### Sprint 5 Beta Version Release (13.4-20.4) 
The goal of this sprint was to release the Beta version of our product, and push it to the master branch. 

**User Stories Implemented:**
* 

**DONE:**
* 

**WIP:**
* 

### Sprint 6 Version 1.0 Release (20.3-27.4) 
The goal of this sprint was to clean up our code, and implement any final features before releasing Version 1.0 of our product. 

**User Stories Implemented:**
* 

**DONE:**
* 

**WIP:**
* 

### Sprint 7 Version 1.1 (optional) and Write-Up (27.4-4.5) 
The goal of this sprint will be to do the write-up, as well as address any issues that arise from the release of Version 1.0 and implement any final features. 

**User Stories Implemented:**
* 

**DONE:**
* 

**WIP:**
* 

## b. Details of how you evaluated your designs (techniques used & awareness of their
limitations)
## c. Discussion of Social and Ethical implications of the work

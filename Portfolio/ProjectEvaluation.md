![Do or Die Project Evaluation](/Portfolio/Images/projectEvalLogo.png)

# 3. Project Evaluation [20pts]:
## a. Reflective discussion of the success of the project
## b. Discussion of future work (in terms of design, development and evaluation)
## c. Group Working Practices
Our group undertook an Agile workflow while completing our project. This allowed us to embrace changing requirements, and ensured that when our working methods had to become remote, we were prepared and did not fall behind. Our working practices, methods for communication, and their relative success in terms of our group's working practice, will be considered in turn. 

### AGILE COMMUNICATION 

Our working process was highly centred on the Agile principle, which are evident in a number of our working practices. We also focused mainly on using the Kanban framework, as it ensured that we had a full transparency of the work that was left to be done. We also chose to implement some methods of the Scrum process in our team, in particular organising weekly code sprints with the aim of deploying a working version of our code at the end of each sprint. In terms of indivdiual work, we chose to pair-program in respect to each of our key subsytems (web, management dashboard, and m5 stack). 

We began work on our project by breaking down our work in to user stories which are described in further detail in [the System Design section](../Portfolio/SystemDesign.md) of our portfolio. We began by ensuring that we had a clear focus of project requirements, as well as how long we expected each requirement to take, and prioritise which would come first. 

While it was tempting at times to work solely on the subsystem that you were focused on, we found it easier to visualize our work in a [Gantt chart](https://uob-my.sharepoint.com/:x:/g/personal/ac16888_bristol_ac_uk/EXltfbLEnNFLrGLOGOxgZcIB2oqj_ft_TP9LevpsozfhVg?e=TUTMn7). Doing this allowed our team to see how each key user story was being implemented, when it was complete, and how each user story linked together between the subsystems. By making these user stories our priority during each of our sprints, we were able to focus on what was most important to delivering our final product, and also ensure that each story was given the appropriate time during our project. 

Our group measured our progress by working at a constant pace, and constantly ensuring that we had a working system. One of our first goals as a group was to ensure that our key subsystems were able to communicate between each other, and we constnatly maintained this by breaking away each week to work on the subsystems and coming together to test them. During our weekly testing meetings, we would ensure that we had a current working project. Once we were satisfied with the quality of our code, and that everything worked as it should, we released Version 0.1 and 0.2 of our product two weeks a part. Following this, we released Version 1.0 and Version 1.1. 

These releases were planned in advance, by utilising the milestone feature on Github we were able to work towards each milestone and prioritise which issues had to be addressed before our first release. To ensure that all the work was transparent, we utilised the Kanban project board on Github in combination with Github issues. This will be addressed later on in this section. 

**KANBAN AND SCRUM FRAMEWORKS**

We mainly used the Scrum framework to ensure that we had an Agile working practice. One team member acted as the Scrum master, dictating the timelines on Github and ensuring that they were outlined on Slack as well. This ensured that we had a clear agreement amongst our team as to when our deliverables were expected by, and which user stories we were currently focused on implementing. 

The deliverables in our group were determined by the [sprints that we set](../Portfolio/SystemImplementation.md), which were typically a week long but during the switch to remote working include a two week sprint. In order to delegate and prioritize our week, we used the Kanban project board on Github. Each one of our sprints relied on the success of the one before, as we aimed to push a deliverable product to our Master branch on Github every two sprints. 

### GITHUB PROCCESS

Our team utilised Github in a number of ways. In order to keep it clear across team members how we wanted to push code to our develop branch, we developed the following method for using Github: 

<p align="center"> 
  1. Create a new branch for each feature and ensure that you pull from develop frequently.
  
  2. When you are done working on that feature, create a pull request. 
  
  3. If applicable, link it to an existing issue to be clear what you are fixing. Likewise, link it to the applicable project Kanban board so the other team members can see the work that is being done. 
  
  4. Another team member, typically your partner working on the same subsystem, will either approve your pull request, or request changes. 
  
  5. You can then merge your branch with develop, marking the issue as closed. 
  
  6. Ensure that you attach your pull request to the applicable milestone (each version that we planned to release, including Alpha and Beta versions). 
  
  7. Delete the branch and repeat!</p> 

Linking our [Kanban board](https://github.com/Team-Jag/Do-or-die-fitness-tracker/projects/1) with our issues helped to greater clarify who was responsible for what issues, and whether they were still in the 'To Do' category or 'In Progress'. Similarly, by then linking it with the pull requests each team member was able to see the work that was being completed and the attached code. This ensured that every team member was on the same page as to the work that was being done, who needed to complete it, and when it had been done. This was [method](https://github.com/Team-Jag/Do-or-die-fitness-tracker/projects/2) was also useful when writing our portfolio remotely. 

The greatest negative to our team's use of Github was the relative inexperience that each team member had with a large number of the features. It took each of us a while to get used to the test driven development cycle, and to ensure that we were branching off of develop and creating a pull request for each new feature. However, once we all began to get in to the habit of following the above work cycle the success became clear and our progress began to excelerate. Similarly, there was less confusion as to who was responsible for which parts of the project. 

### COMMUNICATION TOOLS

While our group communicated most frequently through Facebook messenger, due to it being the most popular messaging platform amongst our group, we chose to use [Slack](https://slack.com/intl/en-gb/) to keep track of more important messages. 
![Slack](/Portfolio/Images/slack.png) 
The main channels that we used in our Slack organisation were core_functionalities, general, issues, and ideas. 
* **core_functionalities**: this channel was used to keep track of our MQTT request types, and our diagrams on how we planned for our subsystems to interact. 
* **general**: this channel was used for more general questions, resources, and important messages that we did not want to loose in our messenger chat. 
* **issues**: prior to creating an issue on github, we used this channel to highlight any specific issues we thought may arise and whether others thought that they needed to be addressed. 
* **ideas**: here we each posted future functionalities and ideas we had about how to improve our product. 

By linking our Github with Slack, each team member was also notified when another team member had created a pull request or pushed to Github. 

Slack was incredibly useful for linked our Google accounts, Github project, and keeping track of our most important resources. It also allowed for a clear platform to keep our messages focused on the Project, so that nothing would get lost. Moreover, it allowed for clear communication between each team member working on the different subsystems. 

### MANAGEMENT OF ISSUES

By linking cards on our Project board with Github issues, it became easy to see who was responsible for what and what level of priority they had (based on which milestone we aimed to have them completed for). In the beginning, a large part of our working issues came from the lack of communication between each of the group members, and an unclear direction of where we saw the project going. In order to rectify this, we began to implement frequent stand-ups for 10-15 minutes between lectures to ensure that we were on the same page in terms of the work that was currently being undertaken. 

When our work moved remotely, we made the pair programming partners permanent to allow for the fact that some team members had technically difficulties with certain aspects of the project, and only one team member had access to the M5 stack. To ensure that our communication did not break down, each of the partners had bi-weekly stand ups on top of our weekly team meetings to review the work completed in the sprint. 

During these weekly video call meetings, we were also able to test each of the subsystems to ensure that they still worked together over MQTT. Moreover, we used these meetings to bring up any potential issues, update any of the backlog on our Kanban board, and prioritise what needed to be done during our next sprint to have a working product for the following week. We also took this time to show the other team members what we had implemented, which you can see in the screenshot below.

![Group Meeting](/Portfolio/Images/groupMeetings.JPG) 

### OVERALL REFLECTION ON GROUP WORKING PRACTICES

While Agile was a new concept to most members of our group, and some of us were hesitant to focus our work around it, we found that it was incredibly beneficial especially when our working practices changed in mid-March. Without in-person interactions, we relied heavily on the Kanban board and our weekly Google Hangout meetings that our code sprints were focused around. This allowed for us to adapt to issues as they arose, and ensure that we constantly had a working product in our master branch. Moreover, it kept each member of the team on the same page as to what work everyone else was doing, and we made for clear communication that we did not feel was affected to drastically by our move to working remotely. 

## d. This is a chance to reflect on how coronavirus has affected your project (remote
working practices etc)

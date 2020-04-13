# 1. System Design :
## a. Architecture of the entire system
Ana
## b. Object-Oriented design of key sub-systems (e.g. Desktop Application, Web
Application etc.)
### Desktop
Team
### Web
Team
### M5
Team

## c. Requirements of key sub-systems (in the form of selected user stories)
### Desktop
### Web
### M5
## d. The evolution of UI wireframes for key sub-systems
### Desktop
### Web
### M5
## e. Details of the communication protocols in use (including a rational for your choice)
Team M5
## f. Details of the data persistence mechanisms in use (including a rational for your
choice)
Team Processing
## g. Details of web technologies in use (including a rational for your choice)
Our website is react based and build on top of a simple react/bootsrap template.
The choice for these technologies was driven by some key needs of our website/team that ultimately led us to choose this set up:
* 1. **Ability for integration of MQTT commuication protocol:** When looking into the different framework we realized that the script Tom provided us for the MQTT communication could be easily reused and integrated into all major Javascript based frameworks (e.g. Angualar, React, Vue).
* 2. **Ability to dynamicially refresh content on a regular basis in an easy way:** Ract turned out to be the obvious candidate to satisfy this need: It's logic is centered around an app state, with components getting rerendered every time the state changes. That way we could display a dynamic step / lifetime counter which would change in real time without refreshing the page.
* 3. **Availability of UI templates for rapid but beautiful prototyping:** React is currently [the most widely used](https://hotframeworks.com/) web framework, so there were plenty of templates available. We chose a [free template by Creative Tim](https://demos.creative-tim.com/now-ui-kit/index.html), which included some basic UI components such as a navigation and a profile page and would allow us to build rapid prototypes without bottering about the details of styling and navigation.


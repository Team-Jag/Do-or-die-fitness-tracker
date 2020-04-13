# 1. System Design :
## a. Architecture of the entire system
Ana
## b. Object-Oriented design of key sub-systems (e.g. Desktop Application, Web
Application etc.)
### Desktop
Team
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
* 4. **Support for Object Oriented Design:** To support our object oriented design we were looking for a framwork that supports the use of a strong object oriented design. React components are ideal to build class based software (see chapter 1.b).

The key component of our design is the Mqtt class.


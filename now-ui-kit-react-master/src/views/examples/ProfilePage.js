import React from "react";

import { BrowserRouter, Route } from 'react-router-dom'

// reactstrap components
import {
  Button,
  Container,
  Row,
  Col,
  UncontrolledTooltip
} from "reactstrap";

// core components
import ExamplesNavbar from "components/Navbars/ExamplesNavbar.js";
import ProfilePageHeader from "components/Headers/ProfilePageHeader.js";
import DefaultFooter from "components/Footers/DefaultFooter.js";
import Mqtt from "./MQTTclient.js";

function ProfilePage(state) {
  // console.log(state.location.state.login_username);

  React.useEffect(() => {
    document.body.classList.add("profile-page");
    document.body.classList.add("sidebar-collapse");
    document.documentElement.classList.remove("nav-open");
    return function cleanup() {
      document.body.classList.remove("profile-page");
      document.body.classList.remove("sidebar-collapse");
    };
  });
  return (
    <>
      <ExamplesNavbar />
      <div className="wrapper">
        <ProfilePageHeader />
        <div className="section">
          <Container>
            <div className="button-container">
              <Button className="btn-round" color="info" size="lg">
                Follow
              </Button>
              <Button
                className="btn-round btn-icon"
                color="default"
                id="tooltip515203352"
                size="lg"
              >
                <i className="fab fa-twitter"></i>
              </Button>
              <UncontrolledTooltip delay={0} target="tooltip515203352">
                Follow me on Twitter
              </UncontrolledTooltip>
              <Button
                className="btn-round btn-icon"
                color="default"
                id="tooltip340339231"
                size="lg"
              >
                <i className="fab fa-instagram"></i>
              </Button>
              <UncontrolledTooltip delay={0} target="tooltip340339231">
                Follow me on Instagram
              </UncontrolledTooltip>
            </div>
            <h3 className="title">About me</h3>
            <h5 className="description">
              I only take credit bets with rankers in the top 1000, if you're
              not in that group, don't @ me. First user to reach 10,000km walked
              within a month, and only user to ever hold the #1 spot in the
              leaderboards. Also I'm F2P.
            </h5>
<h3 className="title">Ongoing Challenges</h3>
<Row>
	    <Col>
			<p>A Mile A Day</p>
                        <img
                          alt="..."
                          className="img-raised"
                          src={require("assets/img/walkicon1.png")}
                        ></img>
   			<p>1.6km<br/>
  			14hr50m<br/><br/></p>
			<p>Never Stop</p>
			<img
                          alt="..."
                          className="img-raised"
                          src={require("assets/img/shoewalk1.png")}
                        ></img>
   			<p>&infin;km<br/>
   			1hr<br/><br/></p>
                      </Col>
                      <Col>
			<p>Group Walking</p>
			<img
                          alt="..."
                          className="img-raised"
                          src={require("assets/img/groupwalk1.png")}
                        ></img>
   			<p>20km<br/>
   			6d10hr25m<br/><br/></p>
			<p>Run From Life</p>
  			<img
                          alt="..."
                          className="img-raised"
                          src={require("assets/img/run1.png")}
                        ></img>
   			<p>100km<br/>
			8hr17m<br/><br/></p>
                      </Col>
   </Row>
<h3 className="title">Achievements</h3>
            <Row>
                      <Col>
			<p>Extreme Strider</p>
                        <img
                          alt="..."
                          className="img-raised"
                          src={require("assets/img/tired1.png")}
                        ></img><br/><br/><br/><br/>
			<p>Close Call</p>
                        <img
                          alt="..."
                          className="img-raised"
                          src={require("assets/img/neardeath1.png")}
                        ></img><br/><br/><br/><br/>
                      </Col>
                      <Col>
			<p>Champion</p>
                        <img
                          alt="..."
                          className="img-raised"
                          src={require("assets/img/winicon1.png")}
                        ></img><br/><br/><br/><br/>
			<p >In The Red</p>
                        <img
                          alt="..."
                          className="img-raised"
                          src={require("assets/img/death1.png")}
                        ></img><br/><br/><br/><br/>
                      </Col>
                    </Row>


          </Container>
        </div>
        <DefaultFooter />
      </div>
    </>
  );
}

export default ProfilePage;

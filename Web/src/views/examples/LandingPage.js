import React from "react";
import Mqtt from './MQTTclient.js';

// reactstrap components
import {
  Button,
  Container,
  Row,
  Col
} from "reactstrap";

// core components
import ExamplesNavbar from "components/Navbars/ExamplesNavbar.js";
import LandingPageHeader from "components/Headers/LandingPageHeader.js";
import DefaultFooter from "components/Footers/DefaultFooter.js";

function LandingPage() {

  React.useEffect(() => {
    document.body.classList.add("landing-page");
    document.body.classList.add("sidebar-collapse");
    document.documentElement.classList.remove("nav-open");
    return function cleanup() {
      document.body.classList.remove("landing-page");
      document.body.classList.remove("sidebar-collapse");
    };
  });
  return (
    <>
      <ExamplesNavbar />
      <div className="wrapper">
        <LandingPageHeader />
        <div className="section section-about-us">
          <Container>
            <Row>
              <Col className="ml-auto mr-auto text-center" md="8">
                <h2 className="title">Do Or Die</h2>
                <h4 className="description">
                Do or Die is the untimate game of 2020. Keep your avatar alive by staying active, rest for too long and it will die. It is your choice!
                Register now, connect to your existing Step-Tracker or Smartphone and start playing.
                </h4>

                <Button className="btn-round" color="primary" outline size="lg"
                href="#id1"
                >
                <i className="fa fa-heart" />
                <span> </span>
                Create my Account
                </Button>
              </Col>
            </Row>
            <div className="separator separator-primary"></div>
            <div className="section-story-overview">
              <Row>
                <Col md="6">
                  <div
                    className="image-container image-left"
                    style={{
                      backgroundImage:
                        "url(" + require("assets/img/pic1.jpg") + ")"
                    }}
                  >
                    <p className="blockquote blockquote-info">
                      "Do. Or do not. There is no try" <br></br>
                      <small>-Master Yoda</small>
                    </p>
                  </div>
                  <div
                    className="image-container"
                    style={{
                      backgroundImage:
                        "url(" + require("assets/img/pic3.jpg") + ")"
                    }}
                  ></div>
                </Col>
                <Col md="5">
                  <div
                    className="image-container image-right"
                    style={{
                      backgroundImage:
                        "url(" + require("assets/img/pic2.jpg") + ")"
                    }}
                  ></div>
                  <h3>
                    The more active you are the longer your avatar lives. Stop and it dies...
                  </h3>
                  <p>
                    Do or Die is a wearable fitness tracker, designed to inspire
                    users to get active and have fun while doing so. There to
                    motivate you is the your new friend Bean, found on the face
                    of your fitness tracker. The more active you are, the more time
                    that is added to Bean's health bar. However, if you fail to meet
                    your step goals, Bean's health bar will slowly decrease. So be
                    careful as once the health bar reaches zero, Bean will die. Get
                    active, meet your step goals, and keep Bean alive.
                  </p>
                  <p>
                    If setting your own goals is not enough motivation, meet
                    our Sponsors! With new challenges weekly, and amazing prizes
                    up for grabs, there's even more reason to keep your Bean's health
                    level up. On top of that, once you register with Do or Die
                    you can access your account details on our website where you can
                    keep track of long term progress, and challenge your friends along the way.
                  </p>
                  <p>
                    The goal is therefore simple, keep the Bean's health bar
                    above zero by getting out and getting active. This is Do or Die, do
                    you have what it takes?
                  </p>
                </Col>
              </Row>
            </div>
          </Container>
        </div>
        <div className="section section-team text-center">
          <Container>
            <h2 className="title">What our players and challenge sponsors say</h2>
            <div className="team">
              <Row>
                <Col md="4">
                  <div className="team-player">
                    <img
                      alt="..."
                      className="rounded-circle img-fluid img-raised"
                      src={require("assets/img/grace.jpg")}
                    ></img>
                    <h4 className="title">Grace</h4>
                    <p className="category text-info">Player</p>
                    <p className="description">
                      This game changed my life, everyday feels like a new challenge. Before I was mostly looking at {" "}
                      <a href="https://www.facebook.com/photo.php?fbid=10207688649325270&set=t.639414625&type=3&theater"
                      target="_blank"
                      rel="noopener noreferrer"
                      >cat pictures</a>
                      {" "}
                      But now I am exercising all the time.
                    </p>
                    <Button
                      className="btn-icon btn-round"
                      color="info"
                      //href="https://www.facebook.com/christoph.buhler.927"
                      onClick={()=> window.open("https://www.facebook.com/graciella.w.putri", "_blank")}
                    >
                      <i className="fab fa-facebook-square"></i>
                    </Button>
                  </div>
                </Col>
                <Col md="4">
                  <div className="team-player">
                    <img
                      alt="..."
                      className="rounded-circle img-fluid img-raised"
                      src={require("assets/img/oli.jpg")}
                    ></img>
                    <h4 className="title">Oli</h4>
                    <p className="category text-info">Player</p>
                    <p className="description">
                      Absolutely love this game. I am killing it!{" "}
                      <a href="https://www.facebook.com/photo.php?fbid=10208294300620020&set=pob.100006272557266&type=3&theater"
                      target="_blank"
                      rel="noopener noreferrer"
                      >See
                      </a>{" "}
                      for yourslef what I have achieved so far. Please sign up now and compete with me.
                    </p>
                    <Button
                      className="btn-icon btn-round"
                      color="info"
                      //href="https://www.facebook.com/christoph.buhler.927"
                      onClick={()=> window.open("https://www.facebook.com/OliverSkeates", "_blank")}
                    >
                      <i className="fab fa-facebook-square"></i>
                    </Button>
                  </div>
                </Col>
                <Col md="4">
                  <div className="team-player">
                    <img
                      alt="..."
                      className="rounded-circle img-fluid img-raised"
                      src={require("assets/img/chris.jpg")}
                    ></img>
                    <h4 className="title">Chris</h4>
                    <p className="category text-info">Sponsor</p>
                    <p className="description">
                      This app it took to make {" "}
                      <a href="https://www.facebook.com/photo.php?fbid=864115786953645&set=t.1467280468&type=3&theater"
                      target="_blank"
                      rel="noopener noreferrer"
                      >
                        my gym
                      </a>{" "}
                      successful. Since we are working with Do Or Die new members come to my gym all the time to complete their challenges.
                    </p>
                    <Button
                      className="btn-icon btn-round"
                      color="info"
                      //href="https://www.facebook.com/christoph.buhler.927"
                      onClick={()=> window.open("https://www.facebook.com/christoph.buhler.927", "_blank")}
                    >
                      <i className="fab fa-facebook-square"></i>
                    </Button>
                  </div>
                </Col>
              </Row>
            </div>
          </Container>
        </div>
        <div className="section section-contact-us text-center" id='id1'>
          <Container>
            <h2 className="title">Want to play?</h2>
            <h4 className="description">We cannot wait to have you with us! it takes 1 minute register and give life to your avatar. <br />
            Start now, your clock is ticking...</h4>
            <Row>

                <Mqtt type = "sign-up" />

            </Row>
          </Container>
        </div>
        <DefaultFooter />
      </div>
    </>
  );
}

export default LandingPage;

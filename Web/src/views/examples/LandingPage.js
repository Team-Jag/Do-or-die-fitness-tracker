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
                Do Or Die is the untimate game of 2020. Keep your avatar alive by staying active, rest for to long and it will die. It is you choice!
                Register now, connect to your existing Step-Tracker or Smartphone and start playing. d
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
                    Text...The Arctic Ocean freezes every winter and much of the
                    sea-ice then thaws every summer, and that process will
                    continue whatever happens with climate change. Even if the
                    Arctic continues to be one of the fastest-warming regions of
                    the world, it will always be plunged into bitterly cold
                    polar dark every winter. And year-by-year, for all kinds of
                    natural reasons, there’s huge variety of the state of the
                    ice.
                  </p>
                  <p>
                    For a start, it does not automatically follow that a record
                    amount of ice will melt this summer. More important for
                    determining the size of the annual thaw is the state of the
                    weather as the midnight sun approaches and temperatures
                    rise. But over the more than 30 years of satellite records,
                    scientists have observed a clear pattern of decline,
                    decade-by-decade.
                  </p>
                  <p>
                    The Arctic Ocean freezes every winter and much of the
                    sea-ice then thaws every summer, and that process will
                    continue whatever happens with climate change.
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

import React from "react";

// reactstrap components
import {
  Container,
} from "reactstrap";

// core components
import ExamplesNavbar from "components/Navbars/ExamplesNavbar.js";
import ChallengeChoiceHeader from "components/Headers/ChallengeChoiceHeader.js";
import DefaultFooter from "components/Footers/DefaultFooter.js";
import Mqtt from "./MQTTclient.js";

function ChallengeChoicePage() {
  // const [pills, setPills] = React.useState("2");
  React.useEffect(() => {
    document.body.classList.add("sidebar-collapse");
    document.documentElement.classList.remove("nav-open");
    return function cleanup() {
      document.body.classList.remove("sidebar-collapse");
    };
  });
  return (
    <>
      <ExamplesNavbar />
      <div className="wrapper">
        <ChallengeChoiceHeader />
        <div className="section">
          <Container>

          <Mqtt type = "challenges" />

            <div align="middle" class="tg-wrap"></div>
          </Container>
        </div>
        <DefaultFooter />
      </div>
    </>
  );
}

export default ChallengeChoicePage;

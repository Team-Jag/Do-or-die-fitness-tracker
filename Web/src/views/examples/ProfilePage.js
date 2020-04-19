import React from "react";

// reactstrap components
import {
  Container
} from "reactstrap";

// core components
import ExamplesNavbar from "components/Navbars/ExamplesNavbar.js";
import DefaultFooter from "components/Footers/DefaultFooter.js";
import Mqtt from "./MQTTclient.js";

function ProfilePage(state) {
  // console.log(state.location.state.login_username);

  React.useEffect(() => {
    document.body.classList.add("profile-page");
    document.body.classList.add("sidebar-collapse");
    document.documentElement.classList.remove("nav-open");
    window.scrollTo(0, 0);
    return function cleanup() {
      document.body.classList.remove("profile-page");
      document.body.classList.remove("sidebar-collapse");
    };
  });

  return (
    <>
    <div
      className="background"
      style={{backgroundImage: "url(" + require("assets/img/blue.jpg") + ")"}}
    >
    <Container>
      <ExamplesNavbar />

          <Mqtt type = "profile" />
        <DefaultFooter />
      </Container>
      </div>
    </>
  );
}

export default ProfilePage;

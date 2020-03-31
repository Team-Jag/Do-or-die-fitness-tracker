import React from "react";

// reactstrap components
import {
  Button,
  Container,
} from "reactstrap";

// core components
import ExamplesNavbar from "components/Navbars/ExamplesNavbar.js";
import ChallengeChoiceHeader from "components/Headers/ChallengeChoiceHeader.js";
import DefaultFooter from "components/Footers/DefaultFooter.js";

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
            <div align="middle" class="tg-wrap"><table id="tg-VvxLO">
  <tr>
    <th>Name</th>
    <th>Requirement (km)</th>
    <th>Duration</th>
    <th>Reward</th>
    <th>Location</th>
    <th>Select</th>
  </tr>
  <tr>
    <td>Can't Stop Won't Stop</td>
    <td>2</td>
    <td>1 hour</td>
    <td>10 Crystals</td>
    <td></td>
    <td><Button variant="outlined" size="large" color="primary">Accept Challenge</Button></td>
  </tr>
  <tr>
    <td>Godly Marathon</td>
    <td>5000</td>
    <td>1 year</td>
    <td>Legendary Bundle</td>
    <td></td>
    <td><Button variant="outlined" size="large" color="primary">Accept Challenge</Button></td>
  </tr>
  <tr>
    <td>Group Activities</td>
    <td>10</td>
    <td>1 day</td>
    <td>x2 Rewards (12 Hours)</td>
    <td>PureGym, Bristol</td>
    <td><Button variant="outlined" size="large" color="primary">Accept Challenge</Button></td>
  </tr>
  <tr>
    <td>Offering to Xenu</td>
    <td>25</td>
    <td>4 days</td>
    <td>+3 Days of Life</td>
    <td>Church of Scientology</td>
    <td><Button variant="outlined" size="large" color="primary">Accept Challenge</Button></td>
  </tr>
</table></div>
          </Container>
        </div>
        <DefaultFooter />
      </div>
    </>
  );
}

export default ChallengeChoicePage;

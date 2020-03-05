/*eslint-disable*/
import React from "react";

// reactstrap components
import { Container } from "reactstrap";

// core components

function DefaultFooter() {
  return (
    <>
      <footer className="footer footer-default">
        <Container>
          <nav>
            <ul>
              <li>
                <a
                  href="https://www.google.com/search?q=team+jaguar"
                  target="_blank"
                >
                  About Us
                </a>
              </li>
              <li>
                <a
                  //href="link tbd"
                  target="_blank"
                >
                  Blog
                </a>
              </li>
            </ul>
          </nav>
          <div className="copyright" id="copyright">
          © {new Date().getFullYear()}, Designed and coded by Team Jaguar
          </div>
        </Container>
      </footer>
    </>
  );
}

export default DefaultFooter;

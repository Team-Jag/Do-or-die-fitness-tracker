/*eslint-disable*/
import React from "react";

// reactstrap components
import { Container } from "reactstrap";

function TransparentFooter() {
  return (
    <footer className="footer">
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

          </ul>
        </nav>
        <div className="copyright" id="copyright">
        © {new Date().getFullYear()}, Designed and coded by Team Jaguar
        </div>
      </Container>
    </footer>
  );
}

export default TransparentFooter;

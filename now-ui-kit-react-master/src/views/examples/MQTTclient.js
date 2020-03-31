// Create a client instance, we create a random id so the broker will allow multiple sessions
import React from "react";
// import jQuery from 'jquery';
import Paho from 'paho-mqtt';
import { Redirect } from "react-router-dom";


import {
  Button,
  Input,
  InputGroupAddon,
  InputGroupText,
  InputGroup,
  Col,
  Row,

} from "reactstrap";


class Mqtt extends React.Component {

  constructor(props) {
    super(props);

    this.state = {
        mqttConnected: false,
      //new challenge page
        challenge_name: '',
        challenge_description: '',
        challenge_step_goal: '',
        challenge_end_date: '20-03-31',
        challenge_reward: '',
        challenge_loaded: false,
      //login/signup page
        login_username: '',
        redirect: false,
      //ProfilePage
        total_steps: 0,
        remaining_sec: 0,
        ranking: 8364,
        dummy_counter: 0, // used to calculate a dummy ranking

    };
    this.handleChange = this.handleChange.bind(this);
    this.pushNewChallenge = this.pushNewChallenge.bind(this);
    this.onMessageArrived = this.onMessageArrived.bind(this);
  }

  componentDidMount() {
    this.client = new Paho.Client("broker.mqttdashboard.com", 8000, "clientId" + this.makeid(3) );
    this.client.connect({onSuccess: this.onConnect.bind(this)});
    this.client.onConnectionLost = this.onConnectionLost;
    this.client.onMessageArrived = this.onMessageArrived;
  }

  render(){
      if(this.props.type === "set-challenge"){
        return(this.renderSetChallenge())
      }
      if(this.props.type === "login"){
        return(this.renderLogin())
      }
      if(this.props.type === "sign-up"){
        return(this.rendersignup())
      }
      if(this.props.type === "profile"){
        return(this.renderProfile())
      }
      if(this.props.type === "challenges"){
        return(this.renderGetChallenges())
      }
  }

renderProfile(){
  if (this.state.mqttConnected === true){
    this.requestProfile();
  }
  return(
    <div>
    <p className="category">Your Stats</p>
    <div className="content">
      <div className="social-description">
        <h2>{this.state.total_steps}</h2>
        <p>Steps</p>
      </div>
      <div className="social-description">
        <h2>{this.state.remaining_sec}</h2>
        <p>Seconds Lifetime</p>
      </div>
      <div className="social-description">
        <h2>#{this.state.ranking}</h2>
        <p>Ranking</p>
      </div>
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
              <p>A Mile A Day</p>  <img  alt="..."  className="img-raised"  src={require("assets/img/walkicon1.png")} ></img>
              <p>1.6km<br/>
              14hr50m<br/><br/></p>
              <p>Never Stop</p>
              <img alt="..."  className="img-raised" src={require("assets/img/shoewalk1.png")} ></img>
              <p>&infin;km<br/>
              1hr<br/><br/></p>
          </Col>
          <Col>
              <p>Group Walking</p>
              <img  alt="..."  className="img-raised"  src={require("assets/img/groupwalk1.png")} ></img>
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
  </div>

  )
}

requestProfile(){
  if(this.state.total_steps !== 0){
    this.wait(1000);
  }
  console.log("Requesting profile...");
  var newRequest = {
    type: "pull profile",
    user_name: global.userName
  }
  this.requestToServer(JSON.stringify(newRequest));
}

rendersignup(){
  return(
    <Col className="text-center ml-auto mr-auto" lg="6" md="8">
    <InputGroup>
      <InputGroupAddon addonType="prepend">
        <InputGroupText>
          <i className="now-ui-icons users_circle-08"></i>
        </InputGroupText>
      </InputGroupAddon>
      <Input
        placeholder="User Name..."
        type="text"
        value={this.state.login_username}
        onChange={(event) => this.loginChange('login_username', event)}
      ></Input>
    </InputGroup>
    <div className="send-button">
    {this.redirectToProfile()}
      <Button
        block
        className="btn-round"
        color="info"
        size="lg"
        onClick={this.handleLogin.bind(this)}
      >
      Sign up now
      </Button>
      <div className="pull-middle">
        <h6>
          <a
            className="link"
            href="/login-page"
          >
            Login to existing Account
          </a>
        </h6>
      </div>
    </div>
    </Col>
  )
}

redirectToProfile(){
  if (this.state.redirect) {
    return(
         <Redirect to={{
               pathname: '/profile-page',
           }} />)
  }
}

handleLogin(){
  this.setState({
  redirect: true
})
}

loginChange(type,event){
  this.setState({[type]: event.target.value});
  global.userName= event.target.value;
}

handleChange(type,event) {
   this.setState({[type]: event.target.value});
}

renderLogin(){
  return(
    <form >
    <InputGroup
      >
      <InputGroupAddon addonType="prepend">
        <InputGroupText>
          <i className="now-ui-icons users_circle-08"></i>
        </InputGroupText>
      </InputGroupAddon>
      <Input
        placeholder="User Name..."
        type="text"
        value={this.state.login_username}
        onChange={(event) => this.loginChange('login_username', event)}
      ></Input>
    </InputGroup>
    <InputGroup>
      <InputGroupAddon addonType="prepend">
        <InputGroupText>
          <i className="now-ui-icons text_caps-small"></i>
        </InputGroupText>
      </InputGroupAddon>
      <Input
        placeholder="Password..."
        type="password"
      ></Input>
    </InputGroup>
    {this.redirectToProfile()}
    <Button
      block
      className="btn-round"
      color="info"
      onClick={this.handleLogin.bind(this)}
      size="lg"
      >    Login
    </Button>
    </form>
  );
}
  
renderGetChallenges(){
   if(this.state.mqttConnected === true){
    this.requestChallenges()
  }  
   return(
    <div>
    <div className="content">
      <div className="social-description">
        <h2>{this.state.challenge_name}</h2>
        <p>name</p>
      </div>
      <div className="social-description">
        <h2>{this.state.challenge_reward}</h2>
        <p>reward</p>
      </div>
      <div className="social-description">
        <h2>{this.state.challenge_end_date}</h2>
        <p>end date</p>
      </div>
    </div>
  
  )
}

requestChallenges(){
  console.log("Requesting challenges...")
  var newRequest1 = {
    type: "pull all challenges"
 }
  this.requestToServer(JSON.stringify(newRequest1))
}

renderSetChallenge(){
  return(
    <form align="left" onSubmit={this.validateChallengeInput.bind(this)} >
    <label className ="form-label">Challenge Name:  </label>
    <input type="text"  value={this.state.challenge_name} onChange={(event) => this.handleChange('challenge_name', event)} /><p/>
    <label className ="form-label">Description:  </label>
    <input type="text" className='challenge-textfield' value={this.state.challenge_description} onChange={(event) => this.handleChange('challenge_description', event)} /><p/>
    <label className ="form-label">End Date: </label>
    <input type="date"  value={this.state.challenge_end_date} onChange={(event) => this.handleChange('challenge_end_date', event)} /><p/>
    <label className ="form-label">Step Goal: </label>
    <input type="number"  value={this.state.challenge_step_goal} onChange={(event) => this.handleChange('challenge_step_goal', event)}/><p/>
    <label className ="form-label">User Reward: </label>
    <input type="number"  value={this.state.challenge_reward} onChange={(event) => this.handleChange('challenge_reward', event)}/><p/>

    <button className="submit-button">Create Challenge</button>
    </form>
  )
}

  validateChallengeInput(event){
    event.preventDefault();
    if(this.state.challenge_name === '' || this.state.challenge_description === '' || this.state.challenge_reward === '' || this.state.challenge_step_goal === ''){
      alert("Please complete all fields");
    }
    else if(this.state.challenge_reward >=0 && this.state.challenge_step_goal >=0){
      this.pushNewChallenge(event);
    }
    else{
      alert("Please enter positive numbers");
    }
  }

  pushNewChallenge(event){
    console.log(JSON.stringify(this.state.challenge_name));
    console.log("Pushing New Challenge");
    var today = new Date(),
    date = today.getFullYear() + '-' + (today.getMonth() + 1) + '-' + today.getDate()+'T'+today.getHours()+':'+today.getMinutes()+':'+today.getSeconds()+'.'+today.getMilliseconds()+'Z';
  	var newChallenge = {
      type: "push new challenge",
      challenge_id: "C" + this.makeid(6),
      challenge_name: this.state.challenge_name,
      description: this.state.challenge_description,
      end_time: this.state.challenge_end_date,
      step_goal: this.state.challenge_step_goal,
      reward: this.state.challenge_reward,
      current_time: date
    }

  	this.requestToServer(JSON.stringify(newChallenge));
    alert("You successfully created a new challenge");
  }

  // called when the client connects
  onConnect() {
    // Once a connection has been made report.
    console.log("Connected");
    this.setState({
    mqttConnected: true
  });

    // this.state.mqttConnected = true;
  }
  // called when the client connects
  requestToServer(payload) {
    // Once a connection has been made, make a subscription and send a message.
    console.log("Request to server");
    this.client.subscribe("doordie_web");
    var message = new Paho.Message(payload);
    message.destinationName = "doordie_web";
    this.client.send(message);
  }
  // called to generate the IDs
  makeid(length) {
     var result           = '';
     var characters       = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
     var charactersLength = characters.length;
     for ( var i = 0; i < length; i++ ) {
        result += characters.charAt(Math.floor(Math.random() * charactersLength));
     }
     return result;
  }

  // called when the client loses its connection
  onConnectionLost(responseObject) {
    if (responseObject.errorCode !== 0) {
      console.log("Mqtt.onConnectionLost:"+responseObject.errorMessage);
    }
  }

  // called when a message arrives
  onMessageArrived(message) {
    console.log("Mgtt.onMessageArrived:"+message.payloadString);
    var json_message = JSON.parse(message.payloadString);

    if(json_message.type === 'push profile' && json_message.user_name === global.userName){
      console.log("HELLLO");
      this.setState({
        total_steps: json_message.total_steps,
        remaining_sec: json_message.remaining_sec,
        ranking: Math.max(1, Math.round(8378 -json_message.total_steps +this.state.dummy_counter/3,0)), //dummy formula: so that it looks like your ranking changes when the step count goes up
        dummy_counter: this.state.dummy_counter + 1
      })
    }
  }
  //wait function called after sever request, to avoid spaming the server
  wait(ms){
   var start = new Date().getTime();
   var end = start;
   while(end < start + ms) {
     end = new Date().getTime();
  }
  }

}
export default Mqtt;

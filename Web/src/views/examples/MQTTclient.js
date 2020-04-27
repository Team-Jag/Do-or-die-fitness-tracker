// Create a client instance, we create a random id so the broker will allow multiple sessions
import React from "react";
// import jQuery from 'jquery';
import Paho from 'paho-mqtt';
import { Redirect } from "react-router-dom";
import {Link} from 'react-router-dom';

import {
  Button,
  Input,
  InputGroupAddon,
  InputGroupText,
  InputGroup,
  Col,
} from "reactstrap";

class Mqtt extends React.Component {

  constructor(props) {
    super(props);
    this.moment = require('moment');

    this.state = {
        mqttConnected: false,
        page_name: '',
        account_exists: false,
        data_received: false,
      //new challenge page
        challenge_id: '',
        challenge_name: '',
        challenge_description: '',
        challenge_step_goal: '',
        challenge_end_date: '20-03-31',
        challenge_reward: '',
        challenges_loaded: false,
        challenge_array: [],
      //login/signup page
        login_username: '',
        is_sponsor: false,
        redirect: false,
      //ProfilePage
        total_steps: -1,
        remaining_sec: 0,
        ranking: 8364,
        user_challenges: [],
        image_name: "default-avatar.jpg",
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
      if(this.props.type === "set-challenge"){
        return(this.renderSetChallenge())
      }
  }

renderProfile(){
  console.log(this.state.user_challenges);
  if (this.state.mqttConnected === true){
    this.requestProfile();
  }
  if(this.state.total_steps === -1)
  {
    return(
    <div align="middle"><br/><br/><br/><br/>
      <img alt="" src={process.env.PUBLIC_URL + '/img/loading.gif'}></img>
      <br/><br/><br/><br/>
    </div>
    )
  }
  else if(this.state.user_challenges.length === 0){
  return(
    <div>
        <div className="profile_photo">
          <img alt="..." src={process.env.PUBLIC_URL + '/img/'+this.state.image_name}></img>
        </div>
        <div align="middle" >
          <select onChange={(event) => this.handleImgChange('image_name', event)} id="choices">
            <option value='default-avatar'>Default</option>
            <option value='virus'>Quentin Quarantino</option>
            <option value='skull'>Skully</option>
            <option value='octo'>Dr Octo</option>
            <option value='penguin'>Very Happy Feet</option>
          </select>
        </div>
        <h2 className="title">{global.userName}</h2><br/>
    <h4 className="category">My Stats</h4>
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
    </div>
  )}
  else {
  return(
    <div>
        <div className="profile_photo">
          <img alt="..." src={process.env.PUBLIC_URL + '/img/'+this.state.image_name}></img>
        </div>
        <div align="middle" >
          <select onChange={(event) => this.handleImgChange('image_name', event)} id="choices">
            <option value='default-avatar'>Default</option>
            <option value='virus'>Quentin Quarantino</option>
            <option value='skull'>Skully</option>
            <option value='octo'>Dr Octo</option>
            <option value='penguin'>Very Happy Feet</option>
          </select>
        </div>
        <h2 className="title">{global.userName}</h2><br/>
    <h4 className="category">My Stats</h4>
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
      <h3 className="title">My Challenges</h3>
      <React.Fragment>
         <div align="middle" className="tg-wrap"><table className="ccp">
         <tr>
           <th>Name</th>
           <th>Description</th>
           <th>Step Goal</th>
           <th>End Date</th>
           <th>Reward</th>
           <th></th>
         </tr>
         {this.state.user_challenges.map(listitem => (
           <tr>
             <td>{listitem.challenge_name}</td>
             <td>{listitem.description}</td>
             <td>{listitem.step_goal}</td>
             <td>{this.moment(listitem.end_time*1000).format('YYYY-MM-DD HH:mm').replace('Invalid date','')}</td>
             <td>{listitem.reward}</td>
           </tr>
         ))}
         </table></div>
      </React.Fragment><br/><br/>
      <Link to='/challenge-choice-page'>
      <Button
        className="btn-round back-btn">
        See all available Challenges
      </Button>
      </Link>
      <br></br>
  </div>

)}
}

createNewProfile(){
  console.log("Creating new profile...");
  const now = Date.now();
  var newRequest = {
    type: "push new profile",
    user_name: global.userName,
    user_type: global.profile_type,
    joined_date: now
  }
  this.requestToServer(JSON.stringify(newRequest));
}

requestProfile(){
  if(this.state.total_steps !== 0){
    this.wait(1000);
  }
  console.log("Requesting profile...");
  var newRequest = {
    type: "pull web profile",
    user_name: global.userName
  }
  this.requestToServer(JSON.stringify(newRequest));
}

rendersignup(){
  if(this.state.page_name !== 'sign-up')
  {
    this.setState({page_name: 'sign-up'})
  }
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
    <input
      type="checkbox"
      checked={this.state.is_sponsor}
      onChange={(event) => this.handleCheckBox('is_sponsor', event)}
    ></input> I am a sponsor
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
  if(this.state.mqttConnected === true && this.state.data_received === true)
  {
    if(this.state.page_name === 'login')
    {
      console.log("we're on the login page")
        if(this.state.account_exists === true)
        {
          console.log("redirect changed to true")
          this.setState({redirect: true})
        }
    }
    if(this.state.page_name === 'sign-up')
    {
        console.log("we're on the sign up page")
        if(this.state.account_exists === false)
        {
          this.createNewProfile()
          this.setState({redirect: true})
        }
    }
  }
  if (this.state.redirect)
  {
    if(this.state.page_name === 'sign-up' && global.profile_type==='sponsor')
    {
      return(
           <Redirect to={{
                 pathname: '/challenge-page',
             }} />)
    }
    else
    {
      return(
           <Redirect to={{
                 pathname: '/profile-page',
             }} />)
    }
  }
}

handleLogin()
{
  this.requestProfile()
}

loginChange(type,event){
  this.setState({[type]: event.target.value});
  global.userName= event.target.value;
}

handleChange(type,event) {
   this.setState({[type]: event.target.value});
   console.log('type is: ' + type + ' and value is ' + event.target.value)
}

handleCheckBox(type,event) {
  this.setState({[type]: event.target.checked});
  console.log('type is: ' + type + ' and value is ' + event.target.checked)
  if(event.target.checked === true)
  {
    global.profile_type='sponsor'
  }
  if(event.target.checked === false)
  {
    global.profile_type='user'
  }
}

handleImgChange(type,event) {
   this.setState({[type]: event.target.value + '.jpg'});
   console.log('type is: ' + type + ' and value is ' + event.target.value)
}

renderLogin(){
  if(this.state.page_name !== 'login')
  {
    this.setState({page_name: 'login'})
  }
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

requestChallenges(){
  console.log("Requesting challenges...")
  var newRequest1 = {
    type: "pull all challenges"
  }
  this.requestToServer(JSON.stringify(newRequest1))
}

renderGetChallenges(){
  console.log(global.userName);
   if(this.state.mqttConnected === true && this.state.challenges_loaded === false){
    this.requestChallenges()
    this.setState({challenges_loaded: true})
  }
  if(this.state.challenge_array.length === 0)
  {
    return(
    <div align="middle"><br/><br/><br/><br/>
      <img alt="" src={process.env.PUBLIC_URL + '/img/loading.gif'}></img>
      <br/><br/><br/><br/>
    </div>)
  }
  else{
   return(
     <React.Fragment>
        <div align="middle" className="tg-wrap"><table className="ccp">
        <tr>
          <th>Name</th>
          <th>Description</th>
          <th>Step Goal</th>
          <th>End Date</th>
          <th>Reward</th>
          <th></th>
        </tr>
          {this.state.challenge_array.map(listitem => (
            <tr>
              <td>{listitem.challenge_name}</td>
              <td>{listitem.description}</td>
              <td>{listitem.step_goal}</td>
              <td>{this.moment(listitem.end_time*1000).format('YYYY-MM-DD HH:mm').replace('Invalid date','')}</td>
              <td>{listitem.reward}</td>
              <td><Button className="submit-button" onClick={(event) => this.pushSelectedChallenge(event,listitem.challenge_id)} variant="outlined" size="large" color="primary">Accept Challenge</Button></td>
            </tr>
          ))}
        </table></div>
        <Link to='/profile-page'>
        <Button
          className="btn-round back-btn">
          Back to Profile
        </Button>
        </Link>
      </React.Fragment>

  );
}
}

pushSelectedChallenge(event,id){
var selectedChallenge = {
  type: "push select challenge",
  user_name: global.userName,
  challenge_id: id
  }
  this.requestToServer(JSON.stringify(selectedChallenge));
  alert("You successfully joined this challenge");
}

renderSetChallenge(){
return(
    <div>
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
    </div>
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
  	var newChallenge = {
      type: "push new challenge",
      challenge_id: "C" + this.makeid(6),
      challenge_name: this.state.challenge_name,
      description: this.state.challenge_description,
      end_time: this.state.challenge_end_date,
      step_goal: this.state.challenge_step_goal,
      reward: this.state.challenge_reward,
      creator_id: global.userName
    }
    if(global.profile_type === 'sponsor')
    {
      this.requestToServer(JSON.stringify(newChallenge));
      alert("You successfully created a new challenge");
    }
    else
    {
      alert("You don't have the authority to create a challenge");
    }
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

    if(json_message.type === 'push all challenges'){
      console.log("attempt to get array");
      this.setState({challenge_array: json_message.challenge})
    }

    if(json_message.type === 'push web profile' && json_message.user_name === global.userName){
      console.log(json_message.hasOwnProperty("total_steps"));
      this.setState({
        total_steps: json_message.total_steps,
        remaining_sec: json_message.remaining_sec,
        account_exists: json_message.hasOwnProperty("total_steps"),
        data_received: true,
        user_challenges: json_message.challenges,
        ranking: Math.max(1, Math.round(8378 -json_message.total_steps +this.state.dummy_counter/3,0)), //dummy formula: so that it looks like your ranking changes when the step count goes up
        dummy_counter: this.state.dummy_counter + 1
      })
      global.profile_type=json_message.user_type
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

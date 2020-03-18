// Create a client instance, we create a random id so the broker will allow multiple sessions
import React from "react";
import jQuery from 'jquery';
import Paho from 'paho-mqtt';
import { BrowserRouter, Route, Switch, Redirect } from "react-router-dom";


import {
  Button,
  Input,
  InputGroupAddon,
  InputGroupText,
  InputGroup,

} from "reactstrap";

import ProfilePage from "views/examples/ProfilePage.js";


class Mqtt extends React.Component {

  constructor(props) {
    super(props);


    this.state = {
        challenge_name: '',
        challenge_description: '',
        challenge_step_goal: '',
        challenge_end_date: '20-03-31',
        challenge_reward: '',
        login_username: '',
        redirectState: false,
    };
    this.handleChange = this.handleChange.bind(this);
    this.pushNewChallenge = this.pushNewChallenge.bind(this);

    this.client = new Paho.Client("broker.mqttdashboard.com", 8000, "clientId" + this.makeid(3) );
    this.client.connect({onSuccess: this.onConnect});
    this.client.onConnectionLost = this.onConnectionLost;
    this.client.onMessageArrived = this.onMessageArrived;
    this.redirect = '';
  }

  render(){
      if(this.props.type === "set-challenge"){
        return(this.renderSetChallenge())
      }
      if(this.props.type === "login"){
        return(this.renderLogin())
      }

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


redirectToProfile(){
  if (this.state.redirect) {
    return(
         <Redirect to={{
               pathname: '/profile-page',
               // state: {login_username: this.state.login_username}
           }} />)
  }
}

handleLogin(){
  this.setState({
  redirect: true
})
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
      // href="/profile-page"
      onClick={this.handleLogin.bind(this)}
      size="lg"
      >    Login
    </Button>
    </form>
  );

}

  loginChange(type,event){
    this.setState({[type]: event.target.value});
    global.userName= event.target.value;
  }



  handleChange(type,event) {
     this.setState({[type]: event.target.value});
  }

  // called when the client connects
  onConnect() {
    // Once a connection has been made report.
    console.log("Connected");
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
    // var x = Mqtt.getByValue("challenge-name");
    console.log("Pushing New Challenge");
    var today = new Date(),
    date = today.getFullYear() + '-' + (today.getMonth() + 1) + '-' + today.getDate()+'T'+today.getHours()+':'+today.getMinutes()+':'+today.getSeconds()+'.'+today.getMilliseconds()+'Z';
  	var newOrder = {
      type: "push new challenge",
      challenge_id: "C" + this.makeid(6),
      challenge_name: this.state.challenge_name,
      description: this.state.challenge_description,
      end_time: this.state.challenge_end_date,
      step_goal: this.state.challenge_step_goal,
      reward: this.state.challenge_reward,
      current_time: date
    }
       //x.elements[3].value,
    	// delivery_address: x.elements[4].value,
    	// delivery_coordinates: x.elements[5].value
    // document.getElementById("order").innerHTML = JSON.stringify(newOrder);
  	// document.getElementById("status").innerHTML = newOrder.order_status;
  	this.onSubmit(JSON.stringify(newOrder));
  }

  // called when the client connects
  onSubmit(payload) {
    // Once a connection has been made, make a subscription and send a message.
    console.log("onSubmit");
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
  }

}
export default Mqtt;

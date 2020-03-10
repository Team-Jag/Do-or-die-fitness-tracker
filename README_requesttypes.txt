// From database sending user profile
{
    "type": "push profile",
    "user_id": "1",
    "challenge_id": ["1", "2"],
    "user_name": "Mario",
    "total_steps": "2200",
    "remaining_sec": "2000",
    "current_time": "2020-02-30T08:35:30.0108Z"
}
  
// From M5Stack/web requesting user profile from database
{
    "type": "pull profile",
    "user_id": "1"
}
 
// From web/M5Stack requesting database to send all challenges that user are enrolled in
{
    "type": "pull user challenges",
    "user_id": "1"
}
  
// From database sending all challenges that user is enrolled in
{
    "type": "push user challenges",
    "challenge": [
    {
        "challenge_id": "1",
        "challenge_name": "10K Step Challenge",
        "description": "stepstep",
        "end_time": "20-02-28 14:20",
        "step_goal": "10000",
        "reward": "800",
        "current_time": "2020-02-30T08:35:30.0108Z"
    },
  
    {
        "challenge_id": "2",
        "challenge_name": "Challenge 2",
        "description": "runrun",
        "end_time": "20-02-28 14:20",
        "step_goal": "2000",
        "reward": "200",
        "current_time": "2020-02-30T08:35:30.0108Z"
    }]
}
  
// From web requesting database to send challenges
{
    "type": "pull all challenges"
}
 
// From database, send all challenges data to web
{
    "type": "push all challenges",
    "challenge": [
    {
        "challenge_id": "1",
        "challenge_name": "10K Step Challenge",
        "description": "stepstep",
        "end_time": "20-02-28 14:20",
        "step_goal": "10000",
        "reward": "800",
        "current_time": "2020-02-30T08:35:30.0108Z"
    },
  
    {
        "challenge_id": "2",
        "challenge_name": "Challenge 2",
        "description": "runrun",
        "end_time": "20-02-28 14:20",
        "step_goal": "2000",
        "reward": "200",
        "current_time": "2020-02-30T08:35:30.0108Z"
    }]
}
  
// From M5Stack, increment one step in database, no response from database
{
    "type": "push step",
    "user_id": "1"
}

// From web, when sponsor adds new challenge, no response from database
{
    "type": "push new challenge",
    "challenge_id": "3",
    "challenge_name": "Challenge 2",
    "description": "runrun",
    "end_time": "20-02-28 14:20",
    "step_goal": "2000",
    "reward": "200",
    "current_time": "2020-02-30T08:35:30.0108Z"
}

// From web, when user selects challenge, no response from database - additional functionality
{
    "type": "push select challenge",
    "user_id": "3",
    "challenge_id": "1"
}
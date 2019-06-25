# Execution Service
A rosservice-based hack to control execution of a ROS node.

This package is an implementation of a custom service that can be used to start and stop the publishers and subscribers of a node as and when required, or to also cleanly kill the node.

## Installation
Create a catkin workspace if you don't have one already:
``` bash
mkdir -p ~/catkin_ws/src
cd catkin_ws/src
catkin init
```

Clone this repository into the `src` subfolder of the workspace, then build it:
``` bash
git clone https://github.com/ashwin2802/execution_srv.git
catkin build terminator
source ~/catkin_ws/devel/setup.zsh
```

## Nodes

### Publisher
Publishes an incremental stream of integers:  
**Topics Published:** `/input`  
**Topics Subscribed:** `None`

### Server
Provides the actual execution service, and also republishes data from the publisher.  
**Topics Published:** `/output`  
**Topics Subscribed:** `/input`  
**Services:** `/terminate`  

### Client
Provides a client that be used to call the service instead of having to use `rosservice call`. Takes the signal value as an argument.  
**Topics Published:** `None`  
**Topics Subscribed:** `None`   

## Usage

The service takes an integer `signal`, which can be either of `-1`, `0` or `1`, as input and returns a boolean indicating whether the service was successfully called. `-1` kills the server node, `0` stops the publisher and subscriber of the server node and `1` restarts them.

You can call the service from the terminal using either ``` rosservice call /terminate "signal :0" ``` or ``` rosrun terminator client 0 ```. (replace `0` with `-1` or `1` accordingly)
 

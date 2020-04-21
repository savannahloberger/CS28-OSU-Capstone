# CS-Capstone
Oregon State CS-Capstone
CS Group 28 Capstone Project Repository

<!-- ![banner]() -->

[![license](https://img.shields.io/github/license/savannahloberger/CS-Capstone)](LICENSE)
[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)


## Table of Contents

- [Background](#background)
  * [Problem Description](#problem-description)
  * [Project Description](#project-description)
- [Install](#install)
  * [Dependencies](#dependencies)
  * [Steps](#steps)
- [Usage](#usage)
  * [Notes](#notes)
  * [Steps](#steps)
- [System Design and Requirements](#System-Design-and-Requirements)
  * [Design](#design)
  * [Requirements](#requirements)
- [Software Design and Requirements](#Software-Design-and-Requirements)
  * [Design](#design)
  * [Requirements](#requirements)
- [API](#api)
- [Contributing](#contributing)
- [License](#license)
- [Original Project Members](#original-project-members)



## Background 

Head Tracker software for helicopter pilots to make use of AR (Augmented Reality) within their displays, they need to have their head movements tracked accurately and with little latency.


### Problem Description 

During real time flights, pilots can use tools that display augmented reality to users. However, if there is a discrepancy between the real world and what is being shown to a pilot, there can be miscommunication, loss of information, or poor decisions made by pilots based on faulty information. Because of this, our client’s goal is to create a system that is able to display an augmented reality that matches the real world with additional information to the user.

Even when using accurate sensors for reading changes in the environment, there is possibilities for errrors in the readings. By combining and averaging 6 different sensors position readings, we hope to minimize error as much as possible. 

### Project Description

Our project is a low cost, accurate, and low-latency implementation of a head tracker that is desinged for pilots. By combining a Raspberry Pi, 6 IMU sensors, and software, we can display and track an accurate location of the pilots head. 

The software will read the data from the sensors, calculate the head position based on the data, and send the head position to the display system in real time for testing. The software will be applied to an AR system which used to improve the pilots’ safety and operation during their flight. For this project, the software is designed to read data from six IMU units and run on Linux that is installed on a Raspberry Pi. Fast, accurate, and lightweight software used for helicopter pilots display head positioning that averages IMU sensor data and corrects drift. 

Primary software tools and languages: python, C, multithreading, microcontrollers, and sensor data. 

Benefits of new design: 
* Light weight
* Accurate
* Low cost 


## Install
### Dependencies

- There are no software libraries required outside of the basic gcc compiler and C libraries. The necessary library files required to run are included.
- This software has been tested and confirmed to run on: gcc version 4.8.5 
- The hardware dependencies that has been emulated with the dummy data and can be ran in linux/unix environments with the compiler mentioned above.

### Steps

Steps for installing the head tracking software: 

1. There are two options for run environments: 
  1. Log into the ENGR servers at: flip1.engr.oregonstate.edu 
More directions and information about that can be found here: 
  2. Run the software on your local machine:

*As of now, the software has been tested mainly on the Oregon State engineering servers and that environment is what we encourage you to use.*


2. Clone the repo to your local machine to run 
```
$ git clone http://github.com/savannahloberger/CS28-OSU-Capstone
```

3. Then run make to build the program
```
$ make
```

4. Follow [Usage](#usage) steps below to run the program


## Usage

### Notes

There are hardware dependencies that has been emulated with the dummy data. The software runs using the provided "dummy data" that simulates the output of sensor data. The testing of the integration of the software with the project hardware will happen at a later time. 

### Steps

Steps for running the head tracking software after following the install directions above: 

To run the program:
```
$ ./tracker
```

*WIP*

*To run the unit testing*
```
$ ./testing
```


To clean up the files: 
```
$ make clean
```


## System Design and Requirements 

### Design

There are 4 steps that the data flows through: 
1. The sensors collect data readings 
2. The sensor data is interpreted and averaged on a microcontroller (in our case a Raspberry Pi) 
3. The data is then sent to a server and the AR display software modifies the image based on the input
4. The pilot sees the updated display on their glasses 

![System Design](/images/HT%20Software%20Diagram.jpg)


### Requirements 
 
Main functions that will be included in the software are: 
- Calculate data from other systems / sensors 
- Functionally read sensors over time
- Correct drift in the inertial sensors *WIP*
- Calculate and correct drift at 10Hz *WIP* 
- Display and send real time position
- Store data in file(s) with timestamps
- Output data through system socket interface *WIP* 

## Software Design and Requirements

### Design 
 
For this software we focused on the parameters, keeping the overall system light weight and fast. The software can be described as two main components, the software library and the main function. 

The library supports the functionality required of the software:  
- Average
- Check connections
- Data 
- Display 
- Dummy (practice data)
- Logging 
- Read data 
- Run time 
- Utilities 


### Requirements
- Communication with External interfaces: 
  - Raspberry Pi to IMU sensors and Raspberry Pi to trigger system
- Press a button to start (physical or keyboard)
- Built-In Test for communication with the hardware
- SW functions: 
  - calculate drift at 10 Hz when system is parked *WIP*
  - read sensors over time and store data in file with time change
- Sensors: 9 degrees of freedom of the chip x 6 chips 
- Track relative drift and flag anomalies *WIP*



## API

More API documentation coming soon! 


## Contributing

Further contributing documentation coming soon! 

PRs accepted.

Small note: If editing the Readme, please conform to the [standard-readme](https://github.com/RichardLitt/standard-readme) specification.


## License

License is included with the software: 
[MIT © Richard McRichface.](LICENSE)


## Original Project Members
Team members: Eric Sisson, Jianlong Huang, and Savannah Loberger

# FESA : FlightStation Software Project

> ***DISCLAIMER***: This project was developed by the FESA Electronics & Software subteam for the TEKNOFEST Fighter UAV competition. Although the team successfully
reached the final stage, the project could not be completed due to unexpected delays in material procurement and an underestimation of the workload by team members.
However, for future reference and further development, we have decided to make our incomplete work available to the open-source community. Half of the software has been implemented,
and the system design is nearly complete.

  FlightStation is one of the four main repositories of the FESA project. This software is designed to control the PX4 autopilot using MAVLink messages based on commands received 
from the ground station. It facilitates communication with the Pixhawk controller, processes raw camera outputs through a deep learning model, and streams as well as saves the 
processed video using efficient compression protocols such as H.264 and H.265.

  This software was built on [TSML](https://github.com/enessanc/TSML), a generic library that I developed. This library provides a modular way to communicate between independent threads and manage the lifecycle of that thread (starting, looping, exception handling nad finishing). Also this software uses a TCP multi client-one server networking library named [NL](https://github.com/enessanc/NL) , which is also developed by me by using asio library from boost framework. 
  
  Additionally, to simplify the development process and ensure the software's modularity, I implemented a modular CMake system. With this system, each module can be built separately and tested independently.

  During the development process, I focused on creating clear and maintainable code. To achieve this, we adhered to SOLID principles and incorporated design patterns where appropriate, 
avoiding unnecessary overengineering. This approach not only streamlined development but also significantly enhanced our skills and understanding throughout the project.

## FESA Avionic System Design
## FESA Sofware System Design
### FSClient Module System Design
### PX4Controller Module System Design
### VideoStreaner Module System Design

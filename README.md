# Drone_Package_Delivery
In this section we will explain and justify why we design the path as in the video simulation, also we will justify and explain some security rules that we consider to avoid any privacy problem with the residents. The path that we design is with a coordinates protocol to make autonomous, but in case that the operator want to control the drone could do and make semi-autonomous with this two protocols we are able to access to any kind of places. For this path we consider a delivery of 10 package on a residential with different types of buildings and with a nonspecific order of delivery, we attached the top-view of the residential to explain how the done operate.

## Requirements
  - Download Webots R2022a version https://cyberbotics.com/
  - Run the world that is atthached to got the enviroment and the drone desing.
  - Apply the code of the drone to got the controller Project/Project/controllers/Drone/Drone.c. 

![6](https://github.com/EmmanuelRd02/Drone_Package_Delivery/assets/152221492/0ee11c7a-642d-4095-8b1d-0d1de1cb030a)

## Procedure 
  1. For the procedure to initialize the simulator we must run the world file that is attached on the Project carpet (Project/Project/worlds/Project.wbt).
On the carpet of the Project we have two worlds the one that said Project Test.wbt is the one that we use to controll the drone with our board, and the one that said Project.wbt is the one that is autonomous the one that you must open is the autonomous one to achive our goals to make an autnonomous simulator. 

![1](https://github.com/EmmanuelRd02/Drone_Package_Delivery/assets/152221492/a54b3b56-3491-49b9-8022-6224d8352cb3)

     
  2. We must put stop to the simulation to avoid any warning of the software.

![7](https://github.com/EmmanuelRd02/Drone_Package_Delivery/assets/152221492/9815964e-619b-419e-b850-f6c5d1712c18)

   
  3. Once we have the world on the webots software we have to upload the code that also is attached on the main files (Project/Project/controllers/Drone/Drone.c).

![8](https://github.com/EmmanuelRd02/Drone_Package_Delivery/assets/152221492/7ecbf576-7b50-487a-8c10-901a6859eea1)


  4. Define the coordinates of the path, in this case the code already has a path that will deliver 10 package to different residences one by one. 

![3](https://github.com/EmmanuelRd02/Drone_Package_Delivery/assets/152221492/0dc8d2a1-16f7-45cf-a7ee-5eb1b16fac92)

  5. Once we have upload the code we are ready to start the simulation and analyse the simulator and end the simulation, we can edit the coordinates for changing the trajectories.

## Results 
On the next video we can see the simulation that we already have done with the trajectories that the drone code already have, the simulation time is a bit longer so you can put another velocity. 

https://winliveudlap-my.sharepoint.com/:f:/r/personal/kevin_vazquezcs_udlap_mx/Documents/SELECTED%20THEMES%20I?csf=1&web=1&e=MgM256

https://winliveudlap-my.sharepoint.com/:v:/r/personal/kevin_vazquezcs_udlap_mx/Documents/TEMAS1/Simulation.mkv?csf=1&web=1&nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0RpcmVjdCJ9fQ&e=ZOfktk



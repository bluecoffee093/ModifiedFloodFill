# MicroMouse Modified FloodFill Algorithm :mouse:

> Implementation of Algorithm used widely in maze searching competitions called MicroMouse.

This project contains a driver code of a simulated micromouse which runs in a maze and searches a path to the center. The competition rules are available [here](https://ewh.ieee.org/sb/columbus/devry/sacFiles/MicromouseRules.pdf) on the official IEEE site. The competition requires a intricate balance of hardware with a good amount of software skill.



![](https://github.com/bluecoffee093/modified-floodfill/modified-floodfill.gif)



## Simulation Software:

* This project uses a simulation software [`mackorone/mms `](https://github.com/mackorone/mms) **credits: [Mackorone](https://github.com/mackorone)**

* It is used to simulate a max solving robot namely MicroMouse.

* The software provides API Library to interface with the maze. The commands to the program are sent through the `STDOUT` stream and for logging `STDERR` stream is used. Please refer the `README.md` file of the [repo](https://github.com/mackorone/mms) for further info. 

  

## Documentation:

* The code provides some insights towards implementation of a modified FloodFill algorithm used by our simulated bot to find a the shortest path (not necessarily the quickest path) to the goal point which is generally located in the center four blocks in `16x16` maze.

* The FloodFill Algorithm pseudocode is as follows:

  ```
  def FloodFillAlgo(wallmaze)    
      valuemaze := int[16][16]
      all cells in distmze := empty
      start := (0,0)
      checks := queue of cells to verify
      checks.push(start)
      while(checks !empty)
          cellCheck := checks.pop
          if (neighbour_cellCheck has 0 value) and (does not have a wall inbetween):
              valuemaze[neighbour_cellCheck] := valuemaze[cellCheck] + 1
              checks.push(neighbour_cellCheck)
          advance to next neighbour_cellCheck
      return valuemaze   
  ```

* This Algorithm returns a `16x16` array with values such that when values are followed in descending order we will directly reach the goal node if the `wallmaze` provided is complete. 
* In *Modified* FloodFill Algorithm, the flood fill algorithm is continuously called each time the agent moves a step and learns more about the environment.

***Stay tuned for more info about the project.***


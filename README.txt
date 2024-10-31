# Project: Sim City
A text-based city simulation that models urban development through residential, commercial,
and industrial zones and resource management.

## Table of Contents
1. Developers
2. Prerequisites
3. Installation
4. Compilation & Running Instructions
5. Configuration Guide
6. Features Implemented
7. Usage Guide
8. Error Handling

## 1. Developers
- Austin Naftal
- Ian Jackson
- Ibrahim Chaudhry
- Bhargav Reddy
- Michael Romero
- Brandon Miranda

## 2. Prerequisites
Ensure that 'g++' is installed on your system to compile c++ programs.
- g++ compiler (C++11 or later)
- Terminal, Command Prompt, or other CLI

## 3. Installation
1. Download or clone the project files to your computer.
- Option 1: Download from the GitLab repository (Click the "Download" button to download the source code)
- Option 2: Clone the repository using this command:
  git clone https://csegitlab.engineering.unt.edu/ikc0014/simcity_project.git
2. Make sure all the files are in the same folder/directory.

## 4. Compilation Instructions:
1. Make a project folder with all the project files in it.
2. Open a command line interface (CLI) such as Terminal (macOS) or Command Prompt (Windows).
3. Navigate to the project directory using the CLI.
4. Run the following command to compile the project:
  g++ *.cpp

This will compile all the '.cpp' files in the directory.

Run Instructions:
1. After compilation, you can execute the program with:
  ./a.out
2. Enter the configuration file name (e.g., "config.txt") when prompted to start the simulation.

## 5. Configuration Guide
A. Config File Format (config.txt)
  Required parameters:
  - Region Layout: [filename.csv] - Path to the region layout file
  - Time Limit: [integer] - Maximum number of simulation steps
  - Refresh Rate: [integer] - How often to display the region map

  Example config.txt:
  Region Layout: region.csv
  Time Limit: 20
  Refresh Rate: 1

B. Region File Format (region.csv)
  Defines the initial layout using the following symbols:
  - R: Residential Zone
  - I: Industrial Zone
  - C: Commercial Zone
  - -: Road
  - T: Powerline
  - #: Road with Powerline
  - P: Power Plant
  - /: Empty cell

Cells should be comma-separated. Example region.csv:
/,/,T,#,T,T,T,/
I,I,I,-,C,C,T,/
I,I,I,-,C,C,T,P
I,I,I,-,C,C,T,/
-,-,-,-,-,-,#,-
/,/,-,R,R,R,T,/
/,/,-,R,R,R,/,/
/,/,-,R,R,R,/,/

## 6. Features Implemented
1. Zone Types and Growth:
  - Residential Zones (population 0-5)
  - Industrial Zones (population 0-3)
  - Commercial Zones (population 0-2)
  - Population growth based on adjacent zones & powerlines

2. City Infrastructure:
  - Roads
  - Power Plants
  - Powerlines for population growth
  - Roads with Powerlines

3. Simulation Features:
  - Time-step based simulation
  - Worker allocation and tracking
  - Goods distribution and tracking
  - Pollution simulation and spread
  - Region analysis

4. Visualization:
  - ASCII region map
  - Population tracking
  - Coordinate-based region analysis

5. User Interface:
  - Interactive time step progression
  - Final state reporting
  - Region coordinate analysis
  - Error handling for invalid inputs

## 7. Usage Example
1. Start the program
2. Enter config file name when prompted
3. View initial region state
4. For each time step:
  - View current region state
  - Check resource counts
  - Choose to continue or quit simulation
5. After simulation ends:
  - View final region state
  - View population totals
  - View pollution totals
  - Analyze specific region areas

## 8. Error Handling
The program handles various errors including:
  - Invalid/missing config file
  - Invalid/missing region file
  - Invalid region coordinates during analysis
  - Invalid user inputs

Bonus implemented: No
# Minimal Process Scheduler

The **Minimal Process Scheduler** is a project that simulates a process scheduler. It generates random processes based on user input and allows simulation of multiple scheduling algorithms, including FIFO, Priority, SRT (Shortest Remaining Time), Round Robin, and Multilevel. Additionally, the project features a dynamic menu with an option to add other scheduling algorithms. The graphical user interface (GUI) is implemented using GTK3.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features

- Process generation with random attributes.
- Support for various scheduling algorithms: FIFO, Priority, SRT, Round Robin, Multilevel.
- Dynamic menu with an option to add custom scheduling algorithms.
- Graphical User Interface (GUI) implemented using GTK3.
- Easy simulation and visualization of scheduling algorithms.

## Requirements

Before running the project, ensure you have the following dependencies installed:

- Linux distro (tested on fedora and ubuntu)
- GCC
- Make
- GTK3

### on Debian distros

    ```bash
    sudo apt-get install gcc && sudo apt-get install make && sudo apt-get install libgtk-3-dev
    ```
    
### on Fedora / Arch

    ```bash
    sudo dnf install gcc && sudo dnf install make && sudo dnf install gtk3-devel
    ```

## Installation

1. **Clone the repository:**

    ```bash
    git clone https://github.com/Iheb-Aouini/Minimal-Process-Scheduler.git
    ```
2. **Change to the project directory:**

    ```bash
    cd Minimal-Process-Scheduler/Project
    ```

3. **Build the project:**

    ```bash
    make all
    ```

## Usage

1. **Run the executable:**

    ```bash
    ./menu processes_list.txt
    ```

2. **Enjoy exploring the project and experimenting with various scheduling scenarios.**


3. **clean the build:**
    ```bash
    make clean
    ```  
## Contributing

Contributions are welcome! Feel free to fork the repository and submit pull requests.

## License

 Feel free to use, modify, and distribute it as per the terms of the license.

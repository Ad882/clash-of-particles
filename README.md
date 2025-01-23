<h1 align='center'> Clash of particles 💥 </h1>

A school project designed to modelize gas particules colliding.   
*Note: Comments are exclusively in French 🇫🇷.*

<br>

## 🗂️ Project structure

Here's the current structure of the project:

```
phishing-simulator/
├── conf/                           # Configuration folder
│   └── doxygen.conf                # Doxygen configuration file
│
├── data/                           # Contains initial configurations            
│   ├── data-toread-error.txt       # Format error example
│   ├── data-toread-formated.txt    # Data example
│   ├── iliad.txt                   # Format error example (text only)
│   ├── newton-simple.txt           # Newton's pendulum
│   ├── one-particle-simple.txt     # 1 particle
│   ├── particles-tests.txt         # Data for test-particles.c
│   ├── random-50.txt               # 50 particles
│   ├── random-100.txt              # 100 particles
│   ├── random-1000.txt             # 1000 particles
│   ├── random-2000.txt             # 2000 particles
│   └── two-particle-simple.txt     # 2 particles
│
├── doc/                            # Doxygen documentation folder
│   ├── html                        # HTML files
│   │   ├── ...                     # 
│   │   └── ...                     # 
│   └── latex                       # Latex files
│       ├── ...                     # 
│       └── ...                     # 
│
├── include/                        # Include folder
│   ├── disc.h                      # disc
│   ├── events.h                    # events
│   ├── loader.h                    # loader
│   ├── particle.h                  # particle
│   └── simulation.h                # simulation
│
├── scripts/                        # Auxiliary folder
│   └── plot_heap_complexity.py     # Compute the heap complexity
│
├── src/                            # Source folder
│   ├── disc.c                      # Draws discs with SDL
│   ├── events.c                    # Handles events
│   ├── example-main.c              # Guide for main file
│   ├── loader.c                    # Initialize particles from data file
│   ├── particle.c                  # Handles particles
│   ├── read-file-formatted.c       # Guide to read formatted data from file
│   ├── read-file-text.c            # Guide to read text lines from file
│   ├── simulation.c                # Main loop
│   ├── snow.c                      # Simulates snow falls
│   └── write-fact.c                # Guide to write text into a file
│
├── tests/                          # Test folder
│   ├── clash-of-particles.c        # main executable
│   ├── test-events.c               # events.c test
│   ├── test-loader.c               # lodaer.c test
│   └── test-particle.c             # particles.c test
│
├── .gitignore                      # Git ignore file
├── LICENSE                         # Project license
├── Makefile                        # Makefile file
└── README.md                       # Project documentation (this file)
```


<br>

## ⚙️ **Installation & Setup**  

### **System Requirements**  

- **Operating System**: Linux (Ubuntu recommended) 🐧  
- **Doxygen**: Required to make the documentation  
- **Graphviz**: Required to plot the particles    
- **SDL**: Required to provide support for 2D pixel operations

---

### Installation steps 🛠️

1. **Clone the repository:**

   ```bash
   git clone https://github.com/Ad882/clash-of-particles.git
   ```
<br>

2. **Install Doxygen:**
  a) Check if Doxygen is installed:
  Type the following command in the terminal to check if Doxygen is installed:

    ```bash
    doxygen --version
    ```
    
    If there is an error, it means it is not installed.
    b) Install Doxygen:

    ```bash
    sudo apt update
    sudo apt install doxygen
    ```
<br>

3. **Install Graphviz:**
```bash
sudo apt update
sudo apt install graphviz
```
After installation, verify that Graphviz is available by running:

```bash
dot -V
```

This should display the version of Graphviz, confirming that the installation was successful.
<br>

4. **Install SDL:**
```bash
sudo apt update
sudo apt install libsdl1.2-dev
```
- For SDL2 (newer):
```bash
sudo apt install libsdl2-dev
```

Then check if the library is installed:
```bash
dpkg -l | grep libsdl
```
<br>

 
## **⚡ Quick Start**
After ensuring that all installations are complete, it is possible to compile:
   ```bash
   make clean
   make compile-all
   ```

Then, run the clash-of-particles executable, choosing the data file:
   ```bash
   ./clash-of-particles data/...
   ```

*Note: The `data/random-50.txt` or `data/random-100.txt` files are the most interesting.*     


<br>

## 🧪 **Running tests**

Test files are also provided. It is possible to run them after the `make copile-all` command. Choose the test to run and execute it.   
Example:
  ```bash
  ./test-events
  ```

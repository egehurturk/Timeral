

# Timeral 

## About
Timeral is a terminal timer (![timer + terminal = timeral](https://latex.codecogs.com/svg.latex?timer&space;+&space;terminal&space;=&space;timeral) ). It is a small (~500 lines) app that lets you use a timer in your terminal.

## Installation
Installation is via cloning the repository and building from the source code:
1. Clone this repository:
    ```bash
    $ git clone <repo_url>
    ```
2. Build the source code:
    ```bash
    $ make
    ```
3. Install the executable to your system:
    ```bash
    $ make install
    ```
Done :) 
You can now use `timeral` directly in your terminal:

```bash
$ timeral start -s 45 -h 2 -m 43
```

## User Guide:

1. **Starting the timer**: You can start the timer with:
   ```bash
   $ timeral start <options>
   ```
   You can specify the duration (hours, minutes, seconds) with the following command line arguments:
   * `-s` or `--seconds`: for specifying the seconds
   * `-m` or `--minutes`: for specifying the minutes
   * `-h` or `--hours`: for specifying the hours
   * `-d` or `--display`: for displaying the timer in the terminal (as opposed to being daemon)
  For example, `timer -s 40 -m 30 -h 2` will have a duration of 2 hours, 30 minutes, and 40 seconds.

      * If you have values that are bigger than `60`, e.g., if you set the minutes value to `79`, it will be displayed as hours: `1hr 19 min` (the same applies to minutes-seconds and seconds-hours). 
  
    Once you start the timer, if you include the `-d|--display` option, it will display a progress bar that shows how much of the duration is completed.
    &nbsp;

    
    If you close the terminal window, the timer will continue to run in the background. See listing active timers for more information.   
    &nbsp;
2. **List active timers**: You can list active timers (timers that haven't completed their duration yet) with:
    ```bash
    $ timeral ls
    ```
    This will give you a nicely formatted output of timers with progress bars (either *daemon* or currently running in a terminal window), their IDs, and their durations. ID is required for stopping the timers. 
    &nbsp;
3. **Stopping active timers**: You can stop any active timer with:
    ```bash
    $ timeral stop <ID>
    ```
    The ID is the identifier number of the timer that can be retrieved from listing the timers. 
    &nbsp;

4. **Resetting active timers**: You can reset any active timer with:
    ```bash
    $ timeral reset <ID>
    ```
    Again, the ID can be found from listing the timers.

5. **Displaying a daemon timer**: You can display the timer in the current terminal with:
    ```bash
    $ timeral display <ID>
    ```
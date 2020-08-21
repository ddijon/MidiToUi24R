# MidiToUi24R
ESP32 based project to control Ui24R device with midi controler

Hello everybody,
I would like to create a MIDI interface to Ui24R.

First, I tried to use it throw a program on PC but I found another more practical solution.
I would like to use a ESP32 microprocessor module.
The advantage of using such a module is that it is low power consumption, standalone, connectable with WIFI...

Here is the purpose of the project:
- The device will have a MIDI in DIN plug to be able to connect any MIDI controller (footswitch or whatever)
- UI24R actions table could be defined related to MIDI events and saved into ESP32 memory.
- No display needed, just maybe a LED to show MIDI received events.
- Configuration table could be inserted throw a web server on the device using a button to switch from configuration (web server) to operation (web client to Ui34R) mode. When in configuration mode, the device could be accessed just as UI24R throw WIFI on another IP.
I know this is technically possible, any help would be appreciated. I want this project to be public and open source.
This project is not easy to make, so it will takes some time to complete (at least 4 months).

Tell me what you think about this project, any ideas are welcome...

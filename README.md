# RTEP
A github to demonstrate workings of RTE project. 

"Employ EMG as a method of user input to a gaming environment”

**The aim**

The general aim of this project is to develop a system which detects EMG signals from the bicep and tricep muscles and use these signal to innervate movement in a video game. **Get your flex on!**

Firstly we aim to hack simple, existing games as a proof of concept. We can then develop our own, or hack more complicated games. The more more stuff going on in a game, the better it must be! No?


**Methodology**

The methodology is to use two standard Ag/AgCl electrodes placed 20cm apart on the muscle.
The signal from these electrodes is sent through a two stage amplifer, the first stage being the differential stage, 
the second being a gain stage. The output of the amplifier is sent to an ADC and then passed to a Raspberry Pi for post-processing and game connection. 

**Potential Uses**

The primary use of this system is to increase the submersion effect of the player into a virtual envinroment.

The system also has uses in the field of rehabilitation, and could be used to encourage otherwise unpleasent rehabilitation programs.

This system could be used in combination with FES stimulation to assist those with muscular or neuronal pathologies.

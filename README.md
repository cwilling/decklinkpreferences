# decklinkpreferences

A way to set preferences for Decklink cards from the command line.

### Features
As a proof of concept, we only set the video input port at the moment; maybe other features later.

Systems with multiple Decklink cards have _not_ been considered - in this case use at your own risk!

### Building
Run:
```
	qmake
	make
```
to produce the decklinkpreferences executable.

### Usage:

```
decklinkprefences [-l] [-p portId] [-s]
	-l           List current configuration
	-p portId    Set input port to one of those listed by the -l option
	-s           Save configuration across reboots
```

It is suggested to first run decklinkpreferences with the -l option
since that will display the display id numbers that are valid for this device
(probably some subset of 0, 2, 4, 8, 16, 32). Running with the -p option
sets the video input to the given port but the result is not saved anywhere
and the setting will not survive reboots. Running with the -s option saves
the current configuration so that it survives reboots of the system.


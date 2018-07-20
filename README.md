Please note that any further development of this project now occcurs at https://gitlab.com/chris.willing/decklinkpreferences

# decklinkpreferences

A way to set preferences for Decklink cards from the command line.

### Features
Since this is just a proof of concept, we only set the video input port at the moment; maybe other features later.

Systems with multiple Decklink cards could use the code in the `develop` branch. Until more local testing of that code (or many reports of success elsewhere) the master branch does not yet support systems with multiple cards.

### Building
The Blackmagic Design SDK is required to build from source code.

Run:
```
	qmake SDK_PATH=path_to_your_black_magic_sdk_include_catalog
	make
```
to produce the _decklinkpreferences_ executable.
If building fails, check decklinkprefences.pro for correct paths
to decklink include files and DeckLinkAPIDispatch.cpp (supplied from the SDK);
then run qmake and make again.

### Usage:

```
decklinkprefences [-l] [-p portId] [-s]
	-l           List current configuration
	-p portId    Set input port to one of those listed by the -l option
	-s           Save configuration across reboots
```

It is suggested to first run _decklinkpreferences_ with the -l option
since that will display the input port id numbers that are valid for this device
(probably some subset of 1, 2, 4, 8, 16, 32). Running with the -p option
sets the video input to the given port but the result is not saved anywhere
and the setting will not survive reboots. Running with the -s option saves
the current configuration so that it survives reboots of the system.


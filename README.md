# Stellar Ledger Prosthesis (*1.0.0*)

**Stellar Ledger Prosthesis** is a standalone, fan-made tool for [Stellaris](https://store.steampowered.com/app/281990/Stellaris/) - a 4X video game made by Paradox Interactive. It allows you to read saved game states and display some information about each empire/star system/planet/etc. present in the game's universe.

*Tested on Windows 10. The application might or might not work on other version of Windows, or when launched using [Wine](https://www.winehq.org/).*

## FAQ

### How do I download it?

Go to the [Releases tab](https://github.com/DreamCobbler/StellarLedgerProsthesis/releases) on SLP's GitHub page: available versions of the application are listed there - find the newest one. (Tip: it's the one at the top of the list.) Then, at the bottom of the specific version's section, are download links: just download the one named "Stellar Ledger Prosthesis x.x.x.zip" (with "x.x.x" being the version number).

### How do I run it?

Just download the archive and unpack it anywhere, then launch "Stellar Ledger Prosthesis.exe". The application doesn't require installation.

### There's some error when the program starts.

By default, SLP looks for saved game states in the "[Your Documents Folder]\\Paradox Interactive\\Stellaris\\save games\\" folder. If this folder doesn't exist, it displays an error message, then a dialog allowing you to choose a folder containing saved games. Just choose the right folder (usually called "save games"). If saved game states aren't in their usual location, you're probably responsible for moving them elsewhere, so you ought to know where they are.

### The list of saved game states on the left is empty.

Well, that means that SLP found the folder that ought to contain saved games - otherwise it would display an error message - but couldn't find any readable save game file. Perhaps there aren't any? Perhaps all of your saved games are with *Ironman* mode enabled? (SLP isn't capable of reading *Ironman* saves.)

## License

**GNU GPL 3**. The text of the license is provided in the *Docs/License.txt* file.

## Changelog

All changelogs can be found in the *Docs/Changelogs* directory.

## Technical

### Documentation

You can generate code documentation using [**Doxygen**](https://www.doxygen.nl/index.html); the relevant configuration file is *Docs/Doxygen/Docs.doxygen*. Generated files will appear in the *Docs/Doxygen/Code Documentation* directory.

### Build Instructions

You can build SLP yourself by following instructions from *Docs/Build Instructions.md*.
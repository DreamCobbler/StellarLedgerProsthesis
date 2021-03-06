# Stellar Ledger Prosthesis (*1.0.0*)

![Screenshot 1](/Screenshots/1.png?raw=true)

**Stellar Ledger Prosthesis** is a standalone, fan-made tool for [Stellaris](https://store.steampowered.com/app/281990/Stellaris/) - a 4X video game made by Paradox Interactive. It allows you to read saved game states and display some information about each empire/star system/planet/etc. present in the game's universe.

## FAQ

### How do I download it?

Go to the **[Releases tab](https://github.com/DreamCobbler/StellarLedgerProsthesis/releases)** on SLP's GitHub page: available versions of the application are listed there. Find the newest one - it's the one at the top of the list. At the bottom of any specific version's section are download links: just download the file named *Stellar Ledger Prosthesis x.x.x.zip* (with "x.x.x" being the version number).

### How do I run it?

Just download the archive and unpack it anywhere, then launch *Stellar Ledger Prosthesis.exe*. The application doesn't require installation.

### There's some error when the program starts.

By default, SLP looks for saved game states in the *[Your Documents Folder]\\Paradox Interactive\\Stellaris\\save games\\* folder. If this folder doesn't exist, it displays an error message, then a dialog allowing you to choose a folder containing saved games. Just choose the right folder (usually called "save games"). If saved game states aren't in their usual location, you're probably responsible for moving them elsewhere, so you ought to know where they are.

### That's not the error it shows.

Huh. In that case please go to the **[Issues tab](https://github.com/DreamCobbler/StellarLedgerProsthesis/issues)** on SLP's GitHub page and post the error message there. I'll see what I can do about it.

### The list of saved game states on the left is empty.

Well, that means that SLP *did* find the folder that ought to contain saved games - otherwise it would display an error message - but couldn't find any readable save game file. Either there are no saved game states, or SLP for some reason can't read them.

## License

**GNU GPL 3**. The text of the license is provided in the *Docs/License.txt* file.

## Changelog

All changelogs can be found in the *Docs/Changelogs* directory.

## Technical

### Documentation

You can generate code documentation using [**Doxygen**](https://www.doxygen.nl/index.html); the relevant configuration file is *Docs/Doxygen/Docs.doxygen*. Generated files will appear in the *Docs/Doxygen/Code Documentation* directory.

### Build Instructions

You can build SLP yourself by following instructions from *Docs/Build Instructions.md*.
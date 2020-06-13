####
#
# Stellar Ledger Prosthesis
# Copyright (C) (2020) Benedykt Synakiewicz (dreamcobbler@outlook.com)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
####

#
#
# Imports.
#
#

from pathlib import Path
from shutil import copy
from typing import List, Optional

#
#
# Constants.
#
#

BinariesDirectoryPath = Path("../Build/Release/")
DocsDirectoryPath = Path("../Docs/")

OutputDirectoryPath = Path("../Environment/")

#
#
# Functions.
#
#

def Main():

    ##
    #
    # The main function.
    #
    ##

    OutputDirectoryPath.mkdir(parents = True, exist_ok = True)

    for file in FindFiles(BinariesDirectoryPath, [".dll", ".exe"]):
        copy(file, OutputDirectoryPath)

    for file in FindFiles(DocsDirectoryPath, [".txt"]):
        copy(file, OutputDirectoryPath)

def FindFiles(path: Optional[Path] = None, suffixes: Optional[List[str]] = None) -> List[Path]:

    ##
    #
    # A utility for locating files in directories.
    #
    # @param path     The directory path. If **None**, then it's current directory.
    # @param suffixes A list of acceptable file name suffixes. If **None**, then every suffix is
    #                 considered acceptable.
    #
    # @return A list of file paths found in given directory.
    #
    ##

	path = Path(path) or Path()
	files = [item for item in path.glob("**/*") if item.is_file()]

	suffixes = [suffix.lower() for suffix in suffixes] if suffixes else None

	return files if not suffixes else [item for item in files if item.suffix.lower() in suffixes]

#
#
# The start-up routine.
#
#

if "__main__" == __name__:

    Main()
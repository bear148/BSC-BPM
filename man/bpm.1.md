% BPM(1) bpm 4.2.1
% Michael S.
% August 2021

# NAME
bpm --help (Main command for general overview of arguments.)

# USAGE
- bpm <option> <argument> <- (Applies to most commands)
- bpm <option> <argument> <argument1> <- (Only applies to 'bpm install --link <link>')
- bpm remove <package>
- bpm install <package>
- bpm --update-log
- bpm --version
- bpm --help
- bpm --package --list
- bpm --compile <package>
- bpm --update <- (To update, you need to install the updater by 'bpm install update-util', and then 'bpm --compile update-util')

# VALID OPTIONS
There are currently 7 options available.
remove, install, --update-log, --version, --help, --package, --compile,and --update. (--package has 1 arg: '--list')

# DESCRIPTION
bpm is a efficient and versatile package manager, made to be easy to use, and easily accessible. bpm is 
written in C and is fairly easy to configure.

# SEE ALSO
bpm(1)

# BUGS
No Known Bugs

# LICENSE
GNU General Public License 3.0

# EXTRA
W.I.P This is a Work-In-Progress! Do not expect to get the full scoop of info from 
this manpage! This will change in the near future.
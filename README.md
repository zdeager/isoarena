# IsoArena (working title)

## Installing SDL/lua

To install SDL and lua on mac, use brew:
`brew install sdl2 sdl2_image sdl2_mixer sdl2_net sdl2_ttf lua`

## Formatting

#### VSCode C/CPP format style

```
{ BasedOnStyle: Google, UseTab: Never, IndentWidth: 2, TabWidth: 2, BreakBeforeBraces: Allman, AllowShortIfStatementsOnASingleLine: true, IndentCaseLabels: false, ColumnLimit: 80, AccessModifierOffset: -4 }
```

Also would recommend setting default Tab Size to 2 (spaces).

#### VSCode C/CPP properties

For Intellisense to work properly, you will need to create a file `{PROJECTDIR}/.vscode/c_cpp_properties.json` with the contents:

```
{
    "configurations": [
        {
            "name": "Mac",
            "includePath": [
                "/usr/local/include",
                "${workspaceFolder}/include",
                "/usr/local/Cellar/sdl2/2.0.14_1/include/SDL2",
                "/usr/local/Cellar/sdl2_image/2.0.5/include/SDL2"
            ],
            "macFrameworkPath": [
                "/System/Library/Frameworks",
                "/Library/Frameworks"
            ],
            "intelliSenseMode": "macos-clang-x64",
            "compilerPath": "/usr/bin/clang",
            "cStandard": "c17",
            "cppStandard": "c++98"
        }
    ],
    "version": 4
}
```

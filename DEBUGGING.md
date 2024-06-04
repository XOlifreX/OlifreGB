# Debugging

This project is setup to use GCC with C++03. I currently develop it in VSCode with GDB. Setup your launch.json file like this:

```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/OlifreGB.exe",
            "cwd": "${workspaceFolder}",
            "args": [""],
            "stopAtEntry": false,
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "your/dbg/location", // set your gdb location
            "setupCommands": [
                {"text": "set substitute-path D:/ /cygdrive/d/"}, // replace with the drive you're working in
            ],
            "launchCompleteCommand": "exec-run",
            "preLaunchTask": "build",
        }
    ]
}
```
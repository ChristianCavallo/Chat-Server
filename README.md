# Chat-Server
This project has been developed for Advanced Programming Languages's course in University of Catania.

Client repository: [https://github.com/ChristianCavallo/Chat-Client]

## Features
-	Multi-Threading
-	Symmetric & Asymmetric security
-	Support to send media files
-	Push notifications
-	Last access support
-	Groups support
-	Media files caching system
-	No relational database (MongoDB)
-	Fast (C++)

This project make use of CMake!

CMake is an open-source, cross-platform family of tools designed to build, test and package software.

## Required Packages
- rapidJson
- mongocxx & bsoncxx
- OpenSSL

## How to install it
If you are using <b>Windows</b>, we suggest you to use <b>vcpkg</b> from microsoft [https://github.com/microsoft/vcpkg].
Install it and type the following commands:
1) vcpkg install rapidjson
2) vcpkg install mongocxx
3) vcpkg install openssl

If you are using Visual Studio, also type "vcpkg integrate" in order to integrate everything directly to your ide.
Alternatively, you can use chaining to link your ide to vcpkg's path.

## Credits
- Noemi Buggea [https://github.com/Noemi-Buggea]
- Christian Cavallo [https://github.com/ChristianCavallo]

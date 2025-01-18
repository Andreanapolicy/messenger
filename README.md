# Messenger without GUI
This is my final project of OTUS courses.

## Description
The messenger consists of two applications: server and client.
Server listens on localhost:8080. To change the configuration, you need to change `/src/common/infrastructure/ServerSettings.h`

## Build

For build you need to install Docker

After set bin directory
```bash
export PATH=~/Projects/desktop_releaser/bin:$PATH
source ~/.bashrc
```

Run for build
```bash
messenger-build.sh
```

Run for build and run tests
```bash
messenger-build-and-run-test.sh
```

After that in `src/build` dir will be two applications: `client` and `server`, and some tests.

## Utils
For more comfortable work with code style and coding convention was written script `run_clang_format.sh`

## Architecture

```mermaid
    C4Context
      title C4 context for application Messenger
      Person(customerA, "First user", "Messenger user")
	  System(Messenger, "Messenger", "Helps users to hang out staying home")
      Person(customerB, "Second user", "Messenger user")

      Rel(customerA, Messenger, "Opens messenger and write")

      Rel(customerB, Messenger, "Opens messenger and write")
```

```mermaid
    C4Container
      title C4 containers for application Messenger
      Person(customerA, "First user", "Messenger user")
      Person(customerB, "Second user", "Messenger user")
	  Person_Ext(admin, "Admin of messenger", "Has rights to manage system")

	  Container_Boundary(c1, "Messener") {
	  	Container(Client, "Client App", "C++, Proto, Boost", "Provides UI for client and connection to chat with other users")
	  	Container(Server, "Server App", "C++, Proto, Boost", "Provides connection with users and delivering messages")
	  }

	  Rel(customerA, Client, "Opens messenger and write")
	  Rel(customerB, Client, "Opens messenger and write")
	  Rel(Client, Server, "Send new message to notify all chats participants")
	  Rel(Server, Client, "Send new message for current user")
	  Rel(admin, Server, "Configurate and start")

      UpdateRelStyle(Client, Server, $offsetY="-60", $offsetX="-90")
      UpdateRelStyle(Server, Client, $offsetY="40", $offsetX="-40")
      UpdateRelStyle(customerA, Client, $offsetY="40")
      UpdateRelStyle(customerB, Client, $offsetY="-40")
      UpdateRelStyle(admin, Server, $offsetY="40")
```
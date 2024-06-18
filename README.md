<p align="center">
  <!--
  <img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" width="100" alt="project-logo">
  -->
</p>
<p align="center">
    <h1 align="center">PPNet</h1>
</p>
<p align="center">
    <em>Streamline your connection, empower your code.</em>
</p>
<p align="center">
	<img src="https://img.shields.io/github/license/PagoPlus/ppnet?style=default&logo=opensourceinitiative&logoColor=white&color=0080ff" alt="license">
	<img src="https://img.shields.io/github/last-commit/PagoPlus/ppnet?style=default&logo=git&logoColor=white&color=0080ff" alt="last-commit">
	<img src="https://img.shields.io/github/languages/top/PagoPlus/ppnet?style=default&color=0080ff" alt="repo-top-language">
	<img src="https://img.shields.io/github/languages/count/PagoPlus/ppnet?style=default&color=0080ff" alt="repo-language-count">
<p>
<p align="center">
	<!-- default option, no dependency badges. -->
</p>

<br><!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary><br>

- [ Overview](#-overview)
- [ Features](#-features)
- [ Repository Structure](#-repository-structure)
- [ Modules](#-modules)
- [ Getting Started](#-getting-started)
  - [ Installation](#-installation)
  - [ Usage](#-usage)
  - [ Tests](#-tests)
- [ Project Roadmap](#-project-roadmap)
- [ Contributing](#-contributing)
- [ License](#-license)
- [ Acknowledgments](#-acknowledgments)
</details>
<hr>

##  Overview

PPNet is a software project designed to facilitate communication between embedded devices and servers over serial connections. It provides a library for processing and encoding messages, allowing developers to integrate it seamlessly with their PlatformIO projects. The project enables the creation of applications that utilize PPNets message transmission capabilities, such as random number generation and server connection establishment. With automated testing through its CI workflow, the PPNet library ensures robust code execution and deployment, making it an invaluable tool for developing software solutions for embedded systems.

---

##  Features

|    |   Feature          | Description  |
|----|-------------------|---------------------------------------------------------------|
| ⚙️   | **Architecture**   | Modular architecture with clear separation between core functionality (`src/PPNet. cpp`) and utilities (`test/*`). PlatformIO integration enables seamless testing and deployment. |
| 🔩  | **Code Quality**   | Consistent code style and naming conventions. Well-organized and well-commented codebase, making it easy to understand and maintain. |
| 📄  | **Documentation**  | Limited documentation in the repository; mostly focusing on specific components and features. A CI workflow (`github/workflows/ci.yml`) automates building, testing, and deployment, providing some degree of transparency. |
| 🔌  | **Integrations**   | Integrates with PlatformIO for project management and testing, utilizing libraries like `MsgPack` and frameworks like `Arduino`. Simulates a serial interface (`test/fake-serial.hpp`) for testing purposes. |
| 🧩  | **Modularity**     | Decoupled architecture enables independent development, maintenance, and reuse of components (e.g., `src/PPNet.cpp`, `test/*`). Well-factored code promotes extensibility. |
| 🧪  | **Testing**        | Utilizes Google Test framework for unit testing (`pio/main.cpp`) and simulates serial interfaces for message encoding and decoding validation (`test/message-encoding.cpp`). |
| ⚡️   | **Performance**    | Optimized for efficient processing and transmission of messages, considering factors like package sizes and target output. Performance characteristics are not explicitly mentioned. |
| 🛡️  | **Security**       | Does not appear to have explicit security measures; focus on software development and embedded systems. No information on data protection or access control is available in the provided documentation. |
| 📦  | **Dependencies**   | Dependent on `MsgPack` for message encoding, `Arduino` for platform compatibility, and `PlatformIO` for project management and testing. Utilizes Google Test framework for unit testing. |
| 🚀  | **Scalability**    | Designed to handle increased traffic and load through efficient processing and transmission of messages, leveraging PlatformIO and serial interfaces for testing and deployment. Scalability characteristics are not explicitly mentioned. |

---

##  Repository Structure

```sh
└── ppnet/
    ├── .github
    │   └── workflows
    ├── README.md
    ├── examples
    │   ├── example-01
    │   └── platformio.ini
    ├── include
    │   └── README
    ├── lib
    │   └── README
    ├── library.json
    ├── library.properties
    ├── platformio.ini
    ├── src
    │   ├── PPNet.cpp
    │   ├── PPNet.h
    │   └── pio
    └── test
        ├── README
        ├── fake-serial.hpp
        ├── hexdump.hpp
        └── test-message-encoding.cpp
```

---

##  Modules

<details closed><summary>.</summary>

| File                                                                       | Summary                                                                                                                                                                                                                                                                                                           |
| ---                                                                        | ---                                                                                                                                                                                                                                                                                                               |
| [library.json](https://github.com/PagoPlus/ppnet/blob/master/library.json) | Defines PPNet library configuration for PlatformIO. Specifies name, version, frameworks (Arduino), platforms (*), and dependencies (MsgPack). This setup enables seamless integration with PlatformIOs project structure, facilitating the development and deployment of projects that utilize the PPNet library. |

</details>

<details closed><summary>src</summary>

| File                                                                     | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                         |
| ---                                                                      | ---                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| [PPNet.cpp](https://github.com/PagoPlus/ppnet/blob/master/src/PPNet.cpp) | This file is responsible for processing and encoding messages within the PPNet system, specifically handling the packing and transmission of various message types. It validates write target types, calculates package sizes, and sends packets to the designated output.                                                                                                                                                                      |
| [PPNet.h](https://github.com/PagoPlus/ppnet/blob/master/src/PPNet.h)     | Defining key components for PagoPlus Network Communication.The file establishes a namespace for PPNet messages, including hello and single counter messages with unique IDs, board identifiers, versions, and boot IDs.It also defines a variant type for holding any possible message and an enumeration for different message types. Additionally, it specifies the main class for PPNet, allowing for writing of messages to output targets. |

</details>

<details closed><summary>test</summary>

| File                                                                                                      | Summary                                                                                                                                                                                                                                                                                                 |
| ---                                                                                                       | ---                                                                                                                                                                                                                                                                                                     |
| [fake-serial.hpp](https://github.com/PagoPlus/ppnet/blob/master/test/fake-serial.hpp)                     | Simulates a serial interface for testing purposes by mimicking a real-world serial devices behavior. Allows for reading and writing data as if it were transmitted over the wire, making it an essential tool for ensuring proper message encoding and decoding in the parent repositorys architecture. |
| [hexdump.hpp](https://github.com/PagoPlus/ppnet/blob/master/test/hexdump.hpp)                             | Ostream` operator streamlines hex dump representation with optional ASCII character display, aligning with the repositorys focus on software development for embedded systems.                                                                                                                          |
| [test-message-encoding.cpp](https://github.com/PagoPlus/ppnet/blob/master/test/test-message-encoding.cpp) | Verifying message encoding.The test file encodes and decodes messages from the PPNetwork, ensuring accurate transmission over a serial connection. It validates written messages against expected data sets for specific message types, such as HelloMessage and SingleCounterMessage.                  |

</details>

<details closed><summary>.github.workflows</summary>

| File                                                                             | Summary                                                                                                                                                                                                                                                                                                                                                  |
| ---                                                                              | ---                                                                                                                                                                                                                                                                                                                                                      |
| [ci.yml](https://github.com/PagoPlus/ppnet/blob/master/.github/workflows/ci.yml) | Streamlining builds and tests for the PPNet repository, this CI workflow YAML file automates the process of verifying project integrity by ensuring code compilation and execution within the defined boundaries. Critical features include building the project using PlatformIO, running unit tests, and deploying artifacts to a designated location. |

</details>

<details closed><summary>examples.example-01</summary>

| File                                                                                               | Summary                                                                                                                                                                                                                                                        |
| ---                                                                                                | ---                                                                                                                                                                                                                                                            |
| [example-01.ino](https://github.com/PagoPlus/ppnet/blob/master/examples/example-01/example-01.ino) | Establishes a Suntech device connection through PPNet library and configures WiFi mode for random number generation. Boots up by sending a HELLO message to the server, including unique board ID, system version, boot ID, and other identifying information. |

</details>

<details closed><summary>src.pio</summary>

| File                                                                       | Summary                                                                                                                                                                                                                                                                                                         |
| ---                                                                        | ---                                                                                                                                                                                                                                                                                                             |
| [main.cpp](https://github.com/PagoPlus/ppnet/blob/master/src/pio/main.cpp) | Initializing the PPNet librarys PlatformIO unit testing environment, setting up Google Test framework, and executing tests through an infinite loop, yielding control back to the platform after each test run. This feature enables efficient testing of PPNets functionality within the PlatformIO ecosystem. |

</details>

---

##  Getting Started

**System Requirements:**

* **CPP**: `version x.y.z`

###  Installation

<h4>From <code>source</code></h4>

> 1. Clone the ppnet repository:
>
> ```console
> $ git clone https://github.com/PagoPlus/ppnet
> ```
>
> 2. Change to the project directory:
> ```console
> $ cd ppnet
> ```
>
> 3. Install the dependencies:
> ```console
> $ g++ -o myapp main.cpp
> ```

###  Usage

<h4>From <code>source</code></h4>

> Run ppnet using the command below:
> ```console
> $ ./myapp
> ```

###  Tests

> Run the test suite using the command below:
> ```console
> $ googletest
> ```

---

##  Project Roadmap

- [X] `► INSERT-TASK-1`
- [ ] `► INSERT-TASK-2`
- [ ] `► ...`

---

##  Contributing

Contributions are welcome! Here are several ways you can contribute:

- **[Report Issues](https://github.com/PagoPlus/ppnet/issues)**: Submit bugs found or log feature requests for the `ppnet` project.
- **[Submit Pull Requests](https://github.com/PagoPlus/ppnet/blob/main/CONTRIBUTING.md)**: Review open PRs, and submit your own PRs.
- **[Join the Discussions](https://github.com/PagoPlus/ppnet/discussions)**: Share your insights, provide feedback, or ask questions.

<details closed>
<summary>Contributing Guidelines</summary>

1. **Fork the Repository**: Start by forking the project repository to your github account.
2. **Clone Locally**: Clone the forked repository to your local machine using a git client.
   ```sh
   git clone https://github.com/PagoPlus/ppnet
   ```
3. **Create a New Branch**: Always work on a new branch, giving it a descriptive name.
   ```sh
   git checkout -b new-feature-x
   ```
4. **Make Your Changes**: Develop and test your changes locally.
5. **Commit Your Changes**: Commit with a clear message describing your updates.
   ```sh
   git commit -m 'Implemented new feature x.'
   ```
6. **Push to github**: Push the changes to your forked repository.
   ```sh
   git push origin new-feature-x
   ```
7. **Submit a Pull Request**: Create a PR against the original project repository. Clearly describe the changes and their motivations.
8. **Review**: Once your PR is reviewed and approved, it will be merged into the main branch. Congratulations on your contribution!
</details>

<details closed>
<summary>Contributor Graph</summary>
<br>
<p align="center">
   <a href="https://github.com{/PagoPlus/ppnet/}graphs/contributors">
      <img src="https://contrib.rocks/image?repo=PagoPlus/ppnet">
   </a>
</p>
</details>

---

##  License

This project is protected under the [SELECT-A-LICENSE](https://choosealicense.com/licenses) License. For more details, refer to the [LICENSE](https://choosealicense.com/licenses/) file.

---

##  Acknowledgments

- List any resources, contributors, inspiration, etc. here.

[**Return**](#-overview)

---

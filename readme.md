- Install the dependencies :
    - sudo apt install -y cmake libexpat-dev expat default-jre
    - Clone the CommonAPI Runtime Library Repo (git clone https://github.com/GENIVI/capicxx-core-runtime.git)
    - Clone the CommonAPI SOMEIP Runtime Library Repo (git clone https://github.com/GENIVI/capicxx-someip-runtime.git)
    - Clone the SOMEIP Library Repo (git clone https://github.com/GENIVI/vsomeip.git)
    - For DLT, install the below dependencies :
        - sudo apt-get install cmake zlib1g-dev libdbus-glib-1-dev build-essential
        - sudo apt-get install libjson-c-dev (Optional)
        - Clone the DLT Daemon Repo (git clone https://github.com/COVESA/dlt-daemon.git)
    - For generating the CAPI Core & SOMEIP Bindings, download the below generators from the releases :
        - CAPI Generator : https://github.com/COVESA/capicxx-core-tools/releases
        - SOMEIP Generator : https://github.com/COVESA/capicxx-someip-tools/releases


After downloading, unzip both the generators into separate folders (commonapi_core_generator & commonapi_someip_generator)


Build all the above repos (except the 2 generators as the generators are the direct deliverables)


- For all the repos, please follow the below commands to build :
    - cd /path/to/workspace/{repo}
    - mkdir build
    - cd build
    - cmake ..
    - make
    - sudo make install


-   Run the below commands to generate the CAPI Core & SOMEIP Bindings
    - ./commonapi_core_generator/commonapi-core-generator-linux-x86_64 -sk Attributes.fidl
    - ./commonapi_someip_generator/commonapi-someip-generator-linux-x86_64 Attributes.fdepl

    - The commands generate the binding files in the “src-gen” folder


- Commands to set the environmental variables
    - export VSOMEIP_CONFIGURATION=/etc/vsomeip-local.json
    - export COMMONAPI_CONFIG=/etc/commonapi-someip.ini


Inspired from the below :
- OSS of SOME/IP from COVESA (GENIVI)
- https://medium.com/@aytackahveci93/introduction-to-genivi-commonapi-640472f468e 
(this blog was useful)

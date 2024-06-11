# orgalorg
 - orgalorg was a basic implementation of a trojan,It runs as a daemon process, start a server on port 666, listening on localhost for upcoming conenctions.
 - if the user provides valid passowrd required by the program, It spawns a shell.
 - Passwords verification is implemented in a way that you can generate a finite amount of passowrds.
 - example of a valid input : `p455 IOrg410rgth3harbing3r0fd00m666`
 - the binary has anti debugging checking,strings obfuscation.The binary also check for an environment `variable named OGP`.If found,It daemonize the process and change It name to sleep.

 
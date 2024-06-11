# Snooz
![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/Screenshot%202024-06-10%20050527.png)

In this challenge we got 2 files "snooz.pcapng" and "memdump.mem".
starting by analyzing the network traffic file, first we open it with wireshark:
![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/wireshark_view.png)

after analyzing the traffic we noticed some HTTP get requests, we try to export HTTP objects:
![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/download.dat.png)

download.dat file contain a base64 data, we decode it and then check the type of the resulted file:
![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/download.datfiletype.png)

reversing the .NET executable in decompiler.com:
![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/snoozdecompile.png)

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/encryptionmode.png)

we notice a connection port (1337) and a key (fr33___p4l3571n3), also the encrytion method used to encrypt the tarffic on 1337 port. We go back to wireshark and find the encrypted packets using the filter "tcp.port == 1337":

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/tcp1337.png)

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/tcp1337datapacket.png)

we copy the packet data and we decrypte it in cyberchef:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/packetdatadecrypt.png)

we got a password for a pastecode notes "5n00zm3m3rbr0z", now we should look in the memory image file for the pascode notes. after using volatility3 windows.psscan plugin we notice two note processes notepad.exe and sticky note:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/psscan.png)

now we should recover the notes in sticky note and notepad. we start with sticky note we should dump the process files in order to get the file where the note texts are stored "DataSectionObject.plum.sqlite-wal.dat":

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/dumpfilesstickynote.png))

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/stickynotecontent.png)

now we got the pastecode link, we open the link in the browser, enter the password  then we got another base64 data:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/pastecode.png)

we download the file, decode it to get a zip file protected by a password:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/convertzipfile.png)

now we should find the zip password, first thing we go back to the notepad.exe and use the windows.notepad volatility plugin to recover the notes:
![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/windows.notepad.png)

we got the zip password "Samaqlo@Akasex777", and we got the flag.jpg file :

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/handala.png)

and finally the last step we extract the flag using stegseek with rockyou worldlist then we got the flag:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/Snooz/screenshots/flag.png)

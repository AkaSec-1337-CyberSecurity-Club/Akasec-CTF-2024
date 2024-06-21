![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/saveme/assets/challdesc.png)

after downloading the chall attachement we got a .docm file (fuckmicrosoft.docm) and encrypted png files:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/saveme/assets/unziping.png)

so in order to decrypt the pngs we have to analyse the docm file, first we are going to look at the content of the file:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/saveme/assets/docmcontent.png)

we notice some hex data, now we have to decode it to know the nature of the information holded in the hex data:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/saveme/assets/extracting_exe_form_docm.png)

we got a .exe file (.NET) from the docm file, now we have to analyse the file to see what he did when the doc was openned, we go to https://app.any.run and we start a new task:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/saveme/assets/exeanalysis_on_anyrun.png)

Our friend runs a powershell script to download a file (ransomeware.exe), we download the file:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/saveme/assets/ransomewarefiletype.png)

after getting the ransomeware.exe file, we decompile it:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/saveme/assets/decompiling%20.png)

we can clearly see that the ransomeware encrypt the files with triple DES encrytion, and also we have the key (Lp3jXluuW799rnu4) and the iv is a byte array (0 -> 7). using those informations we can decrypt the pngs to get the flag:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/saveme/assets/144dycrypt.png)

and here is the flag:

![alt text](https://github.com/AkaSec-1337-CyberSecurity-Club/Akasec-CTF-2024/blob/main/DFIR/saveme/assets/flag.png)



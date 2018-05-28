# ENGR101-AVC
Commands for the Raspberry Pi
"raspivid -o" - Camera Command
"ifconfig" - IPConfig, shows usefu info

SSH connection:
"ssh -x pi@10.140.30.148"
Password:"raspberry"

NOTE: IP CHANGES. ADDRESSES BELOW ARE RENDERED USELESS UNLESS WE FIGURE OUT HOW TO SET THE IP AS STATIC.
Raspberry Pi's IP address: 169.254.160.240
Raspberry Pi's IP address: 10.140.30.148
IPv6: FE80::7e3:a72c:63c3:bd73/64

motor[10mm, 12mm, 25.5mm]

sudo ./"filename"

gcc filename.cpp -o filename -le101

motor 1 is Right
motor 2 is Left



USING FILEZILLA:
Launch Filezilla
•
Host:  greta-pt.ecs.vuw.ac.nz
•
Username:  your-ECS-student-username
•
Password:  your-ECS-student-password
•
Port:22
•
Quickconnect


AUTO-RUN SCRIPT
The first is to place the name and location of you executable file in the file /etc/rc.local. To open this file on your RPi type:

sudo nano /etc/rc.local.

This will open the file in the text editor nano and allow you to edit it. All you need to do now is add a line to the bottom of it telling it where your executable file is. Say your file is called rpidrive in the ENGR101 folder of your home directory. Then the line you need to add to the /etc/rc.local file is:

./home/pi/ENGR101/rpidrive &

Then the next time you turn your RPi on this script will run (as root) automatically.
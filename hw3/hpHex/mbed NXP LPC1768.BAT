SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;S:\Python33\;C:\Program Files\Common Files\Microsoft Shared\Windows Live;C:\Program Files (x86)\Common Files\Microsoft Shared\Windows Live;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\CheckPoint\fde;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin;C:\Program Files\IVI Foundation\VISA\Win64\Bin\;C:\Program Files (x86)\GNU\GnuPG\pub;C:\Program Files (x86)\Windows Live\Shared;C:\Program Files (x86)\Bitvise SSH Client;C:\Program Files\Microsoft SQL Server\110\Tools\Binn\
SET CPU_TYPE=LPC1768
SET CPU_VENDOR=NXP
SET UV2_TARGET=mbed NXP LPC1768
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\build\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\build\hpHex.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\build\hpHex.axf" --i32combined --output ".\build\hpHex.hex"
fromelf --bin -o f:\hpHex.bin build\hpHex.axf

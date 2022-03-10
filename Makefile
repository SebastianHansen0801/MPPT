#Main application file name
MAIN_APP = main
#Main hex file path in windows format
MAIN_HEX_PATH = C:\Users\sebas\Desktop\foldert\blink_test\$(MAIN_APP).hex

# Compiler and other Section
CC = C:\wiring-0101-windows\tools\avr\bin\avr-gcc
OBJCOPY = avr-objcopy.exe
AVRDUDE := C:\wiring-0101-windows\tools\avr\bin\avrdude

#Options for avr-gcc
CFLAGS = -g -Os -o

#Linking options for avr-gcc
LFLAGS = -Os -mmcu=atmega2560 -o

#Options for HEX file generation
HFLAGS = -j .text -j .data -O ihex

#Options for avrdude to burn the hex file
#MMCU model here according to avrdude options
DUDEFLAGS = -cwiring
DUDEFLAGS += -pm2560  
DUDEFLAGS += -PCOM9 
DUDEFLAGS += -b115200 
DUDEFLAGS += -D
DUDEFLAGS += -Uflash:w:$(MAIN_HEX_PATH):i

# Sources files needed for building the application 
SRC = $(MAIN_APP).c
SRC += 

# The headers files needed for building the application
INCLUDE = -I. 
INCLUDE += 

# commands Section
Burn : Build
	$(AVRDUDE) $(DUDEFLAGS)

Build : $(MAIN_APP).elf
	$(OBJCOPY) $(HFLAGS) $< $(MAIN_APP).hex

Clean : 
	@$(RM) -r $(MAIN_APP).elf $(MAIN_APP).hex $(MAIN_APP).o
	
$(MAIN_APP).elf: $(MAIN_APP).o
	$(CC) $(SRC) $(INCLUDE) $(LFLAGS) $@
	
$(MAIN_APP).o:$(SRC)
	$(CC) $^ $(INCLUDE) $(CFLAGS) $@
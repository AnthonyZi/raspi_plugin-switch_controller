###################################################################
##Target Device
MCU=atmega8

###################################################################
##Target-Name
TARGET=avrmain

###################################################################
##Which Programmer do you use?
AVR_DUDE_PROGRAMMER=linuxgpio
AVR_DUDE_PORT=usb

###################################################################
##Optimization levels : 0, 1, 2, 3, s ---  "s" for space-saving
OPTIMIZATION=s

###################################################################
##Output format. (can be srec, ihex, binary)
FORMAT=ihex


###################################################################
##List of all source files
SOURCE=$(TARGET).c
#SOURCE+=foo.c


######################
# List Assembler source files here. 
# Make them always end in a capital .S.  Files ending in a lowercase .s 
# will not be considered source files but generated files (assembler 
# output from the compiler), and will be deleted upon "make clean"! 
# Even though the DOS/Win* filesystem matches both .s and .S the same, 
# it will preserve the spelling of the filenames, and gcc itself does 
# care about how the name is spelled on its command-line. 
ASRC =  
 
 
# List any extra directories to look for include files here. 
#     Each directory must be seperated by a space. 
EXTRAINCDIRS =  
#######################





###################################################################
##Compiler Flags
CFLAGS= -g -O${OPTIMIZATION} \
	-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
	-Wall -Wstrict-prototypes \
	-Wa,-adhlns=$(<:.c=.lst) \
	$(patsubst %,-I%,$(EXTRAINCDIRS))

###################################################################
CFLAGS+= -std=gnu99
#CFLAGS += -std=c89
#CFLAGS += -std=gnu89
#CFLAGS += -std=c99


##Assembler Flags
ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs 


###################################################################
##Linker Flags
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref

###################################################################
##Additional libraries
##Minimalistic printf version
#LDFLAGS += -Wl,-u,vfprintf -lprintf_min
##Floating point printf version (requires -lm below)
#LDFLAGS += -Wl,-u,vfprintf -lprintf_flt
##-lm = math library
LDFLAGS += -lm



###################################################################
##AVR_DUDE usage

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep

AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)

##Uncomment the following if you want avrdude's erase cycle counter.
##Note that this counter needs to be initialized first using -Yn,
##see avrdude manual.
#AVRDUDE_ERASE += -y

##Uncomment the following if you do /not/ wish a verification to be
##performed after programming the device.
#AVRDUDE_FLAGS += -V

##Increase verbosity level.  Please use this when submitting bug
##reports about avrdude. See <http://savannah.nongnu.org/projects/avrdude> 
##to submit bug reports.
#AVRDUDE_FLAGS += -v -v

##Run while cable attached or don't
#AVRDUDE_FLAGS += -E reset #keep chip disabled while cable attached
#AVRDUDE_FLAGS += -E noreset

#AVRDUDE_WRITE_FLASH = -U lfuse:w:0x04:m #run with 8 Mhz clock

#AVRDUDE_WRITE_FLASH = -U lfuse:w:0x21:m #run with 1 Mhz clock #default clock mode

#AVRDUDE_WRITE_FLASH = -U lfuse:w:0x01:m #run with 1 Mhz clock no start up time


##########
## Define directories, if needed.
#DIRAVR = c:/winavr
#DIRAVRBIN = $(DIRAVR)/bin
#DIRAVRUTILS = $(DIRAVR)/utils/bin
#DIRINC = .
#DIRLIB = $(DIRAVR)/avr/lib



###################################################################
# Define programs and commands.
SHELL = bash

###################################################################
CC = avr-gcc

###################################################################
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size



###################################################################
##Programming support using avrdude.
AVRDUDE = avrdude


###################################################################
REMOVE = rm -f
COPY = cp

###################################################################
HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
ELFSIZE = $(SIZE) -AC --mcu=$(MCU) $(TARGET).elf



###################################################################
##Define Messages
##English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = Size before: 
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:



###################################################################
##Define all object files.
OBJ = $(SOURCE:.c=.o) $(ASRC:.S=.o) 

##Define all listing files.
LST = $(ASRC:.S=.lst) $(SOURCE:.c=.lst)

###################################################################
##Combine all necessary flags and optional flags.
##Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)



###################################################################
##Default target: make hex!
default: $(TARGET).hex $(TARGET).eep


###################################################################
all: begin gccversion sizebefore $(TARGET).elf $(TARGET).hex $(TARGET).eep $(TARGET).lss $(TARGET).sym sizeafter finished end


###################################################################
#allwriteavr: begin gccversion sizebefore $(TARGET).elf $(TARGET).hex $(TARGET).eep $(TARGET).lss $(TARGET).sym sizeafter finished end
allwriteavr: all
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)

###################################################################
##Eye candy.
##AVR Studio 3.x does not check make's exit code but relies on
##the following magic strings to be generated by the compile job.
begin:
	@echo
	@echo $(MSG_BEGIN)

finished:
	@echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_END)
	@echo


###################################################################
##Display size of file.
sizebefore:
	@if [ -f $(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); echo; fi

sizeafter:
	@if [ -f $(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); echo; fi



###################################################################
##Display compiler version information.
gccversion : 
	@$(CC) --version



###################################################################
##Program the device.  
#writeavr: $(TARGET).hex $(TARGET).eep
writeavr: default
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)


###################################################################
##Target: clean project.
clean: begin clean_list finished end

clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).eep
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).cof
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).a90
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lnk
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(OBJ)
	$(REMOVE) $(LST)
	$(REMOVE) $(SOURCE:.c=.s)
	$(REMOVE) $(SOURCE:.c=.d)
	$(REMOVE) *~





##Convert ELF to COFF for use in debugging / simulating in
##AVR Studio or VMLAB.
#COFFCONVERT=$(OBJCOPY) --debugging \
#	--change-section-address .data-0x800000 \
#	--change-section-address .bss-0x800000 \
#	--change-section-address .noinit-0x800000 \
#	--change-section-address .eeprom-0x810000 
#
#
#coff: $(TARGET).elf
#	@echo
#	@echo $(MSG_COFF) $(TARGET).cof
#	$(COFFCONVERT) -O coff-avr $< $(TARGET).cof
#
#
#extcoff: $(TARGET).elf
#	@echo
#	@echo $(MSG_EXTENDED_COFF) $(TARGET).cof
#	$(COFFCONVERT) -O coff-ext-avr $< $(TARGET).cof




###################################################################
# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

%.eep: %.elf
	@echo
	@echo $(MSG_EEPROM) $@
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
%.lss: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $@
	avr-nm -n $< > $@


###################################################################
# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(ALL_CFLAGS) $(OBJ) --output $@ $(LDFLAGS)


###################################################################
# Compile: create object files from C source files.
%.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(ALL_CFLAGS) $< -o $@


###################################################################
# Compile: create assembler files from C source files.
%.s : %.c
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
%.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(ALL_ASFLAGS) $< -o $@


# Automatically generate C source code dependencies. 
# (Code originally taken from the GNU make user manual and modified 
# (See README.txt Credits).)
#
# Note that this will work with sh (bash) and sed that is shipped with WinAVR
# (see the SHELL variable defined above).
# This may not work with other shells or other seds.
#
%.d: %.c
	set -e; $(CC) -MM $(ALL_CFLAGS) $< \
	| sed 's,\(.*\)\.o[ :]*,\1.o \1.d : ,g' > $@; \
	[ -s $@ ] || rm -f $@


# Remove the '-' if you want to see the dependency files generated.
-include $(SOURCE:.c=.d)



# Listing of phony targets.
.PHONY : all begin finish end sizebefore sizeafter gccversion coff extcoff \
	clean clean_list program

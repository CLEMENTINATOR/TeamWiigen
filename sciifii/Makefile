#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif

include $(DEVKITPPC)/wii_rules

SystemName := $(shell uname)

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	source source/business/common source/business/tools source/business source/ui/text \
							source/ui/text/MenuItems source/ui/Events source/ui/graphic/ source/ui/graphic/MenuItems
DATA		:=	data  
INCLUDES	:=	include headers

#---------------------------------------------------------------------------------
# MS Visual Studio Style Fix
#---------------------------------------------------------------------------------
STYLEFIX	= 2>&1 | sed -e 's/\([a-zA-Z\.]\+\):\([0-9]\+\):\([0-9]\+:\)\?\(.\+\)/\1(\2):\4/' -e 's/undefined/error: undefined/'

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

CFLAGS	= -O2 -Wall $(MACHDEP) $(INCLUDE)
CXXFLAGS	=	$(CFLAGS)

LDFLAGS	=	$(MACHDEP) -Wl,-Map,$(notdir $@).map

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:= -lwui -lwiisys -lTinyXML -lmad -lasnd -lwiiuse -lbte -logc -lm -lpngu -lpng -lfat -lfreetype -lmetaphrasis -lz

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(CURDIR) $(PORTLIBS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) \
					$(sFILES:.s=.o) $(SFILES:.S=.o)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES), -I $(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/$(BUILD) \
					-I$(LIBOGC_INC)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib) \
					-L$(LIBOGC_LIB)

export OUTPUT	:=	$(CURDIR)/$(TARGET)
.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).dol

#---------------------------------------------------------------------------------
run:
	wiiload $(TARGET).dol
	
#---------------------------------------------------------------------------------
prepare:
	@make -C ../libwui prepare
	@make -C ../libwui
	
ifeq ($(SystemName),Linux)
	@rsync -qrc --exclude='_svn/' --exclude='.svn/'  ../libwiisys/headers/  include/
	@rsync -qrc --exclude='_svn/' --exclude='.svn/'  ../libwui/headers/ include/
else
ifeq ($(SystemName),Darwin)
	@rsync -qrc --exclude='_svn/' --exclude='.svn/'  ../libwiisys/headers/ include/
	@rsync -qrc --exclude='_svn/' --exclude='.svn/'  ../libwui/headers/ include/
else
	-@robocopy ../libwiisys/headers include/ //MIR //XD _svn //XD .svn >> rbcp.log
	-@robocopy ../libwui/headers include/ //E //XD _svn //XD .svn >> rbcp.log
	@rm rbcp.log
endif
endif
	@cp ../libwui/libwui.a lib
	@cp ../libwiisys/libwiisys.a lib
	@rm -fr $(OUTPUT).elf $(OUTPUT).dol


#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).dol: $(OUTPUT).elf
$(OUTPUT).elf: $(OFILES)

-include $(DEPENDS)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .* extension
#---------------------------------------------------------------------------------
%.sys.o	:	%.sys
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)
#---------------------------------------------------------------------------------
%.wad.o	:	%.wad
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)
#---------------------------------------------------------------------------------
%.dat.o	:	%.dat
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

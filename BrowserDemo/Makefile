include $(DEVKITPPC)/wii_rules

all:
	@make -C Browser
	@make -C Stub
	@bin2s Browser/Browser.dol > Boot/source/Browser.S
	@bin2s Stub/stub.bin > Boot/source/Stub.S
	@make -C Boot
	@cp Boot/Boot.elf browser.elf
	@cp Boot/Boot.dol browser.dol

clean:
	@make -C Browser clean
	@make -C Stub clean
	@make -C Boot clean
	@rm -f Boot/source/Browser.S
	@rm -f Boot/source/Stub.S
	@rm -f browser.elf
	@rm -f browser.dol
	
prepare:
	@make -C ../libutils
	@robocopy ../libutils/headers include/libutils //MIR //XD _svn //XD .svn
	@cp ../libutils/libutils.a lib
	
#---------------------------------------------------------------------------------
run:
	wiiload browser.elf
	
test:
	wiiload Browser/Browser.dol
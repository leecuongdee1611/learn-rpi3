KDIR = /lib/modules/$(shell uname -r)/build
 
all:
	make -C $(KDIR)  M=$(shell pwd)

clean:
	make -C $(KDIR)  M=$(shell pwd) clean

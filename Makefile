all: mdns-scan-avahi

mdns-scan-avahi: mdns-scan-avahi.c
	gcc mdns-scan-avahi.c -lavahi-common -lavahi-client -D_REENTRANT -o mdns-scan-avahi

clean:
	rm -f mdns-scan-avahi

.PHONY: clean

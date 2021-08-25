install:
	chmod +x scripts/install.sh
	sudo ./scripts/install.sh

update:
	chmod +x scripts/update.sh
	sudo ./scripts/update.sh

compile:
	sudo gcc bpm-main.c -o bpm -lcurl -Wformat-security
	sudo mv bpm /usr/bin
	echo "\033c"

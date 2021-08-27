echo "Installing dependencies..."
sudo apt-get install libcurl4-gnutls-dev
sudo apt-get install pandoc

echo "Compiling..."
sudo gcc bpm-main.c -o bpm -lcurl -Wformat-security
sudo mv bpm /usr/bin

echo "Manpage Adding..."
cd man
pandoc bpm.1.md -s -t man -o bpm.1
sudo mkdir /usr/local/man/man1
sudo cp bpm.1 /usr/local/man/man1
sudo gzip /usr/local/man/man1/bpm.1
sudo mandb
cd ../

printf "\033c"
printf "\033[0;32m"
echo "Enjoy Bear Package Manager!"
echo "'bpm install <package>' should be ran with sudo."
echo "Run 'bpm --help' to view all the commands!"
echo "As of v4.2.1: We have a man page! 'man bpm'"

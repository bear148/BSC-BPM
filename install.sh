echo "Installing dependencies..."
sudo apt-get install libcurl4-gnutls-dev

echo "Compiling..."
sudo gcc bpm-main.c -o bpm -lcurl
sudo mv bpm /usr/bin

printf "\033c"
printf "\033[0;92m"
echo "Enjoy Bear Package Manager!"
echo "'bpm install <package>' should be ran with sudo."
echo "Run 'bpm --help' to view all the commands!"

sudo gcc bpm-main.c -o bpm
sudo mv bpm /usr/bin
echo "Installing dependencies..."

#install github CLI
#curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo gpg --dearmor -o /usr/share/keyrings/githubcli-archive-keyring.gpg
#echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null
#sudo apt update -y
#sudo apt install gh -y

printf "\033c"
printf "\033[0;92m"
echo "Enjoy Bear Package Manager!"
echo "'bpm install <package>' should be ran with sudo."
echo "Run 'bpm --help' to view all the commands!"

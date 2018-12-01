###############################################
####                                       ####
####    NeuralC installation file          ####
####    Lonyelon, 2018                     ####
####                                       ####
###############################################

###############################################
################    Variables    ##############
###############################################

col_red="tput setaf 1"
col_green="tput setaf 2"
col_white="tput setaf 7"

printDone() {
    $col_green
    echo " DONE!"
    $col_white
}

clean() {
    if [ -d "./build" ]; then
        rm -rf ./build
    fi
    if [ -d "./include" ]; then
        rm -rf ./include
    fi
    if [ -f "./libNeuralC.so" ]; then
        rm libNeuralC.so
    fi
    if [ -f "./NeuralC" ]; then
        rm NeuralC
    fi
    exit
}

uninstall() {
    if [ -d "/usr/include/NeuralC" ]; then
        sudo rm -rf /usr/include/NeuralC
    fi
    if [ -f "/lib/libNeuralC.so" ]; then
        sudo rm /lib/libNeuralC.so
    fi
    if [ -f "/bin/NeuralC" ]; then
        sudo rm /bin/NeuralC
    fi
    clean
}

if [ "$1" = "-r" ]; then
    clean
fi

if [ "$1" = "-u" ]; then
    uninstall
fi

###############################################
################    Build Main   ##############
###############################################
if [ ! -d "./build" ]; then
    $col_red
    echo -n "Creating build dir..."
    mkdir ./build/
    printDone
fi
if [ ! -d "./include" ]; then
    $col_red
    echo -n "Creating include dir..."
    mkdir ./include/
    printDone
fi
cp $(find ./src/ | grep .h) ./include
echo -n "Building object files..."
g++ -fpic -c $(find ./src/ | grep .cc)
mv $(ls *.o) ./build/
printDone

###############################################
################    Build Main   ##############
###############################################
if [ -e "libneuralC.so" ]; then
    $col_red
    echo -n "Removing old lib..."
    rm libNeuralC.so
    printDone
fi
echo -n "Linking library..."
g++ -shared -o libNeuralC.so \
    $(find ./build/ | grep .o)
printDone

###############################################
################   Install Lib   ##############
###############################################
echo -n "Installing lib and includes..."
cp $(find ./src/ | grep .h) ./include/
sudo cp libNeuralC.so /usr/lib/
sudo cp -r ./include/ /usr/include/NeuralC/
printDone

###############################################
################    Build Main   ##############
###############################################
echo -n "Building main software..."
g++ --std=c++17 -lm -pthread -lNeuralC \
    Main.cc $(find ./src/ | grep .cc) \
    -o NeuralC
printDone

################################################
################   Install Main  ###############
################################################
if [ "$1" = "-i" ]; then 
    echo -n "Installing main software..."
    sudo cp NeuralC /bin/
    printDone
fi
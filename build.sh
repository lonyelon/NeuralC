#!/bin/sh

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
    [ -d "./build" ] && rm -rf ./build
    [ -d "./include" ] && rm -rf ./include
    [ -f "./libNeuralC.so" ] && rm libNeuralC.so
    [ -f "./NeuralC" ] && rm NeuralC
    exit
}

uninstall() {
    [ -d "/usr/include/NeuralC" ] && sudo rm -rf /usr/include/NeuralC
    [ -f "/lib/libNeuralC.so" ] && sudo rm /lib/libNeuralC.so
    [ -f "/bin/NeuralC" ] && sudo rm /bin/NeuralC
    clean
}

[ "$1" = "-r" ] && clean
[ "$1" = "-u" ] && uninstall

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
g++ -fpic -c $(find ./src/ | grep .cc) -I./src
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
g++ -shared -o libNeuralC.so -I./src \
    $(find ./build/ | grep .o)
printDone

###############################################
################   Install Lib   ##############
###############################################

echo -n "Installing lib and includes..."
cp $(find ./src/ | grep .h) ./include/
sudo cp libNeuralC.so /usr/lib/
sudo cp -r ./include/* /usr/include/NeuralC/
printDone

###############################################
################    Build Main   ##############
###############################################

echo -n "Building main software..."
g++ --std=c++17 -lm -pthread -lNeuralC \
    src/Main.cc \
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

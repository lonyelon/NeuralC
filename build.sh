###############################################
####                                       ####
####    NeuralC installation file          ####
####    Lonyelon, 2018                     ####
####                                       ####
###############################################

###############################################
################ Build objects ################
###############################################
if [ ! -d "./build" ]; then
    echo "Creating build dir..."
    mkdir ./build/
fi
echo "Building object files"
g++ -fpic -c $(find ./src/ | grep .cc)
mv $(ls *.o) ./build/

###############################################
################   Build Lib   ################
###############################################
if [ -e "libneuralC.so"]; then
    echo "Removing old lib..."
    rm libNeuralC.so
fi
echo "Linking library..."
g++ -shared -o libNeuralC.so \
    $(find ./build/ | grep .o)
echo "Installing lib and includes..."
cp $(find ./src/ | grep .h) ./include/
sudo cp libNeuralC.so /usr/lib/
sudo cp -r ./include/ /usr/include/NeuralC/

###############################################
################   Build Main  ################
###############################################
echo "Building main software"
g++ --std=c++17 -lm -pthread -lNeuralC \
    Main.cc $(find ./src/ | grep .cc) \
    -o NeuralC
#################################################
################   Install Main  ################
#################################################
echo "Installing main software"
sudo cp NeuralC /bin/
cd vendor;

cd RakNet && git submodule init && git submodule update && cd ..;
cd libuv && git submodule init && git submodule update && cd ..;
cd squirrel && git submodule init && git submodule update && cd ..;

echo "Done.";

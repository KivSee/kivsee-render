protoc --nanopb_out=. --python_out=. functions.proto effects.proto

mv functions.pb.c ../src
mv effects.pb.c ../src

mv functions.pb.h ../include
mv effects.pb.h ../include

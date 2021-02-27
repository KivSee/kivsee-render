# .\protoc --plugin=protoc-gen-nanopb=C:\nanopb-0.4.4-windows-x86\generator\protoc-gen-nanopb.bat --nanopb_out=. --python_out=. functions.proto effects.proto
# protoc  --plugin=protoc-gen-nanopb=/Users/sapir/nanopb/generator/protoc-gen-nanopb --nanopb_out=. --python_out=. --js_out=import_style=commonjs,binary:. functions.proto effects.proto
protoc --nanopb_out=. --python_out=. functions.proto effects.proto


mv functions.pb.c ../src
mv effects.pb.c ../src

mv functions.pb.h ../include
mv effects.pb.h ../include

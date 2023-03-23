# for mac: brew install nanopb-generator
# .\protoc --plugin=protoc-gen-nanopb=C:\nanopb-0.4.4-windows-x86\generator\protoc-gen-nanopb.bat --nanopb_out=. --python_out=. functions.proto effects.proto
# protoc  --plugin=protoc-gen-nanopb=/Users/sapir/nanopb/generator/protoc-gen-nanopb --nanopb_out=. --python_out=. --js_out=import_style=commonjs,binary:. functions.proto effects.proto
#--nanopb_opt=-L #include "%s"
protoc --plugin=/home/amir/.local/nanopb-nanopb-0.4.5/generator/protoc-gen-nanopb --nanopb_out=. --python_out=. --cpp_out=../test functions.proto effects.proto segments.proto


mv functions.pb.c ../src
mv effects.pb.c ../src
mv segments.pb.c ../src

mv functions.pb.h ../include
mv effects.pb.h ../include
mv segments.pb.h ../include

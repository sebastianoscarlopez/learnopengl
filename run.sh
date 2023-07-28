# Using fswatch allows to run the script every time a file is changed
# fswatch /Users/sebastianlopez/learngl/  | grep --line-buffered 'main\.cpp$' | xargs -n 1 -I {} ./run.sh
# clang++ -std=c++17 -fdiagnostics-color=always -Wall -g -w -Idependencies/include -Ldependencies/library dependencies/library/libglfw.3.3.dylib main.cpp glad.c -o app -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated
rm app
set -e
echo "Compiling..."
/usr/bin/clang++ -w -std=c++17 -fdiagnostics-color=always -Wall -g -I/Users/sebastianlopez/learngl/dependencies/include -I/Users/sebastianlopez/learngl/include -L/Users/sebastianlopez/learngl/dependencies/library -L/Users/sebastianlopez/learngl/lib /Users/sebastianlopez/learngl/dependencies/library/libglfw.3.3.dylib /Users/sebastianlopez/learngl/*.cpp /Users/sebastianlopez/learngl/lib/*.cpp /Users/sebastianlopez/learngl/lib/shapes/*.cpp /Users/sebastianlopez/learngl/glad.c -o /Users/sebastianlopez/learngl/app -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated
echo "Running..."
./app
echo "Done"
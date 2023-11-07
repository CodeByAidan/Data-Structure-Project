for file in *.c
  do
    echo $file
    name=${file%.*}
    gcc -o ${name}-c.$1 $file && mv ${name}-c.$1 artifacts/${name}-c.$1
  done

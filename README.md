# analisis_algoritmos

Para utilizar el codigo basta con visitar la carpeta build y ejecutar el ejecutable en la respectiva carpeta de primer y segundo nivel.

En cada una de estas carpetas se encuentra un archivo de texto llamado genoma.txt.
Al ejecutar el main de cada nivel, pedira el nombre de un archivo, el nombre a ingresar debe ser este genoma.txt

En caso de que se necesite compilar o re compilar basta con hacer cd a la carpeta build y con CMAKE escribir make.
En caso de que lo anterior no funcione se recomienda eliminar la carpeta build, crear el directorio nuevamente, dirigirse al directorio
Y escribir cmake ..
Luego escribir cmake --build .
Y cada vez que termine escribir make.

El programa esta dividido en 3 carpetas: table que contiene headers y definiciones con estructuras utilizadas para el desarrollo de la tabla como
bucket_t que hace referencia a cada bucket de la tabla, mini_list que es la estructura que hace funcion de lista de cada bucket y obviamente la clase pHash que
es la que como elementos privados contiene un arreglo de bucket_t. Cada bucket_t contiene un vector s_i que representa a los objetos que caen en ese bucket,
esto se utiliza para calcular el a_i y b_i de cada lista una por una sin volver a hacer hashing.

Primero se recomienda ejecutar el programa de primer_nivel que se encarga de determinar las variables a y b del primer nivel.
Luego en el archivo de segundo nivel se insertan estos elementos a cada bucket con las variables a y b definidas.
En el mismo archivo de segundo_nivel se determinan los a_i y b_i de cada lista y finalmente se verifica que todos los elementos del set esten en la tabla.


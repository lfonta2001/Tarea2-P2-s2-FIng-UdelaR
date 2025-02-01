#! /usr/bin/env python
import os
import subprocess
import time
import difflib

# Obtener la ruta del directorio del script
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# Directorios correctos
test_dir     = os.path.join(BASE_DIR, "test")  # Aquí están los .in y .out
output_dir   = os.path.join(test_dir, "salidas")
diff_dir     = os.path.join(test_dir, "diffs")
executable   = os.path.join(BASE_DIR, "principal.exe")

# Crear carpetas de salida si no existen
os.makedirs(output_dir, exist_ok=True)
os.makedirs(diff_dir, exist_ok=True)

correctos = 0
erroneos  = 0
timeouts  = 0

# Iterar sobre los archivos de entrada (.in)
for p in sorted(os.listdir(test_dir)):
    if not p.endswith(".in"):
        continue

    base         = os.path.splitext(p)[0]  # Nombre sin extensión
    input_file   = os.path.join(test_dir, p)
    expected_file= os.path.join(test_dir, base + ".out")  # Salida esperada
    output_file  = os.path.join(output_dir, base + ".sal")  # Salida del programa
    diff_file    = os.path.join(diff_dir, base + ".diff")  # Diferencias

    try:
        # Ejecutar el programa con el archivo de entrada
        with open(input_file, "r") as fin, open(output_file, "w") as fout:
            subprocess.run([executable], stdin=fin, stdout=fout, timeout=1, check=True)

        # Leer archivos
        with open(expected_file, "r") as f:
            expected = f.readlines()
        with open(output_file, "r") as f:
            output = f.readlines()

        # Comparar salida generada con la esperada
        if expected == output:
            print(f" -- El caso {base} se resolvió correctamente")
            correctos += 1
        else:
            diff = difflib.unified_diff(expected, output,
                                        fromfile=f"esperado ({expected_file})",
                                        tofile=f"obtenido ({output_file})")
            diff_text = "".join(diff)
            with open(diff_file, "w") as f:
                f.write(diff_text)
            print("**********************************")
            print(f"El caso {base} tiene errores")
            print("**********************************")
            erroneos += 1

    except subprocess.TimeoutExpired:
        print("**********************************")
        print(f"El caso {base} ha agotado el tiempo de ejecución, revise los loops")
        print("**********************************")
        timeouts += 1

print("Correctos:", correctos, "Errores:", erroneos, "Timeouts:", timeouts)

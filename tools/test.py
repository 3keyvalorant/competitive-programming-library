from pathlib import Path
import os
import shutil
import subprocess
import sys

root = Path(__file__).resolve().parents[1]
build = root / ".build"
build.mkdir(exist_ok=True)
cxx = os.environ.get("CXX", "g++")

subprocess.run([sys.executable, str(root / "tools/bundle.py")], check=True)
sources = [root / "tests/compile_all.cpp", root / "tests/random_test.cpp", *sorted((root / "verify").glob("*.cpp"))]
for standard in ("c++17", "c++20", "c++23"):
    for source in sources:
        output = build / f"{source.stem}-{standard.replace('+', 'p')}{'.exe' if os.name == 'nt' else ''}"
        subprocess.run([cxx, f"-std={standard}", "-O2", "-Wall", "-Wextra", "-Wshadow", str(source), "-o", str(output)], cwd=root, check=True)
    subprocess.run([str(build / f"random_test-{standard.replace('+', 'p')}{'.exe' if os.name == 'nt' else ''}")], check=True)
template = build / f"template{'.exe' if os.name == 'nt' else ''}"
subprocess.run([cxx, "-std=c++17", "-O2", "-Wall", "-Wextra", "-Wshadow", str(root / "template.cpp"), "-o", str(template)], cwd=root, check=True)
print(f"ok: {len(sources)} sources under GNU++17/20/23 and template.cpp")


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
subprocess.run([sys.executable, str(root / "tools/bundle.py"), "--entry", "library/convolution/all.hpp", "--output", "convolution_template.cpp"], cwd=root, check=True)
subprocess.run([sys.executable, str(root / "tools/bundle.py"), "--entry", "library/probability/all.hpp", "--output", "probability_template.cpp"], cwd=root, check=True)
checks = sorted((root / "tests").glob("*_test.cpp"))
sources = [root / "tests/compile_all.cpp", *checks, *sorted((root / "verify").glob("*.cpp")), *sorted((root / "examples").glob("*.cpp"))]
for standard in ("c++17", "c++20", "c++23"):
    for source in sources:
        output = build / f"{source.stem}-{standard.replace('+', 'p')}{'.exe' if os.name == 'nt' else ''}"
        subprocess.run([cxx, f"-std={standard}", "-O2", "-Wall", "-Wextra", "-Wshadow", str(source), "-o", str(output)], cwd=root, check=True)
    for source in checks:
        subprocess.run([str(build / f"{source.stem}-{standard.replace('+', 'p')}{'.exe' if os.name == 'nt' else ''}")], check=True)
for name in ("template", "convolution_template", "probability_template"):
    output = build / f"{name}{'.exe' if os.name == 'nt' else ''}"
    subprocess.run([cxx, "-std=c++17", "-O2", "-Wall", "-Wextra", "-Wshadow", str(root / f"{name}.cpp"), "-o", str(output)], cwd=root, check=True)
print(f"ok: {len(sources)} sources under GNU++17/20/23 and all three templates")


from pathlib import Path
import argparse
import re

root = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser()
parser.add_argument("--entry", default="library/all.hpp")
parser.add_argument("--output", default="template.cpp")
args = parser.parse_args()
seen = set()
body = []

def expand(path: Path):
    path = path.resolve()
    if path in seen:
        return
    seen.add(path)
    for line in path.read_text(encoding="utf-8").splitlines():
        match = re.fullmatch(r'#include "(.+)"', line)
        if match:
            expand(path.parent / match.group(1))
        elif line != "#pragma once" and line != "#include <bits/stdc++.h>":
            body.append(line)

expand(root / args.entry)
text = "#include <bits/stdc++.h>\n" + "\n".join(body).strip() + "\n\nint main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    return 0;\n}\n"
(root / args.output).write_text(text, encoding="utf-8", newline="\n")
print(f"generated {args.output}: {text.count(chr(10))} lines, {len(text.encode())} bytes")


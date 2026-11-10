"""Verify numbered data archives and restore their original relative layout."""
import hashlib
import json
from pathlib import Path
import sys
import zipfile

root = Path(__file__).resolve().parent
dest = Path(sys.argv[1] if len(sys.argv) > 1 else "restored").resolve()
manifest = json.loads((root / "DATA_MANIFEST.json").read_text())
archives = [root / "Campaign-source-and-audit.zip"]
for entry in manifest["parts"]:
    path = root / entry["file"]
    assert hashlib.sha256(path.read_bytes()).hexdigest() == entry["sha256"], path
    archives.append(path)
for archive in archives:
    with zipfile.ZipFile(archive) as z:
        assert z.testzip() is None, archive
        for name in z.namelist():
            if not (dest / name).resolve().is_relative_to(dest):
                raise ValueError(name)
        z.extractall(dest)
print(f"Restored {len(archives)} archives into {dest}")

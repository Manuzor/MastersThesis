import shutil
from pathlib import *
from datetime import datetime
import os

#
# Data
#
now = datetime.utcnow()
root = Path(__file__).parent.parent.resolve();
mainFile = root / "Source" / "Main.pdf"
mainFileNewName = "ManuelMaier_MastersThesis_{:%Y%m%d}.pdf".format(now)
shippingDir = root / "Shipping"

#
# Utilities
#
def copy(*, source, dest, force=False):
  assert source.is_file(), "Copy-source must be an existing file."
  assert not dest.exists() or dest.is_file(), "Copy-destination must either not exist or be an existing file (not a directory)."

  destIsUpToDate = dest.exists() and dest.stat().st_mtime >= source.stat().st_mtime

  print("Copy: ", end="")

  try:
    common = Path(os.path.commonpath((str(source), str(dest))))
    print("{}{{ {} => {} }}".format(common, source.relative_to(common), dest.relative_to(common)), end="")
  except:
    print("{} => {}".format(source, dest), end="")

  if force or not destIsUpToDate:
    shutil.copyfile(str(source), str(dest))

  if force and destIsUpToDate:
    print(" (Forced)", end="")
  elif not force and destIsUpToDate:
    print(" (Already up to date)", end="")

  print()

#
# Main
#
def main():
  if not mainFile.exists():
    print("Missing main PDF file: {}".format(mainFile))
    exit(1)

  if not shippingDir.is_dir():
    shippingDir.mkdir(parents=True)

  copy(source=mainFile, dest=shippingDir / mainFileNewName, force=True)

if __name__ == '__main__':
  main()

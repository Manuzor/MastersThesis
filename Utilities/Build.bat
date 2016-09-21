@echo off
setlocal
  pushd "%~dp0../Source"
    latexmk -synctex=1 -interaction=nonstopmode -xelatex %* Main.tex
  popd
endlocal

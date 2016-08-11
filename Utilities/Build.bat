@echo off
pushd "%~dp0../Source"
  latexmk -xelatex Main.tex
popd

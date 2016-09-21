@echo off
setlocal
  pushd "%~dp0../Source"
    del *.pdf *.bbl *.acn *.acr *.alg *.aux *.bcf *.blg *.fdb_latexmk *.fls *.glg *.glo *.gls *.ist *.lof *.log *.lot *.out *.run.xml *.synctex.gz *.toc %*
  popd
endlocal

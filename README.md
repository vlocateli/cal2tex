# Cal2tex

Convert a google calendar file to TeX document.

## How to run:
```bash
$ cmake -b Build
$ cd !$
$ make
$ cal2tex <calendar_file.ics> <texfile_name>
$ pdflatex -synctex=1 -interaction=nonstopmode <texfile_name>.tex 
```
## status: wip

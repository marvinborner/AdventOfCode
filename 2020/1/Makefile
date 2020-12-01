.PHONY: run.cs

run.exe: run.cs
	@mcs $+

clean:
	@rm -f run.exe

run: run.exe
	@mono run.exe

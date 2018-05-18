name tsmi
user triploit
ver 0.0.0.0

func install {
  g++ main.cpp -o tsmi -w -static -std=c++11
  chmod +x tsmi
  sudo mv tsmi /usr/bin/tsmi
}

func update {
  &install
}

func remove {
  sudo rm /usr/bin/tsmi
}

func install_win {
    <[
        @echo off
        IF NOT EXIST "C:\Program Files (x86)\Triploit Software" (
            MKDIR "C:\Program Files (x86)\Triploit Software"
            ECHO Creating Triploit Software directory...
        ) ELSE (
            ECHO Program Directory exists...
        )

        IF NOT EXIST "bin" (
            mkdir bin
        )

        make
        echo Move executable....
        move ".\bin\tsmi.exe" "C:\Program Files (x86)\Triploit Software\"
        rmdir /s .\bin\
    ]>
}

func remove_win {
    <[
        @echo off
        IF NOT EXIST "C:\Program Files (x86)\Triploit Software\tsmi.exe" (
            ECHO Warning: There is nothing to remove.
        ) ELSE (
            ECHO Removing...
            del "C:\Program Files (x86)\Triploit Software\tsmi.exe"
        )
    ]>
}

func update_win {
  &install
}

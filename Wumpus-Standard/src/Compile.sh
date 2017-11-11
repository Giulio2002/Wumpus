g++ A.I.cpp map.cpp cell.cpp Wumpus.cpp -o A.I -lcurses -fpermissive &&
g++ main.cpp map.cpp cell.cpp Wumpus.cpp -o Wumpus -lcurses -fpermissive &&
g++ FileReading.cpp map.cpp cell.cpp Wumpus.cpp -o FileReading -lcurses -fpermissive &&
mv Wumpus ../bin && mv FileReading ../bin && mv A.I ../bin
